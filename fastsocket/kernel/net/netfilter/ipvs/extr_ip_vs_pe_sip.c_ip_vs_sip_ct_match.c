#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ip_vs_conn_param {scalar_t__ af; scalar_t__ protocol; scalar_t__ vport; scalar_t__ pe_data_len; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  pe_data; int /*<<< orphan*/  caddr; } ;
struct ip_vs_conn {scalar_t__ af; scalar_t__ vport; int flags; scalar_t__ protocol; scalar_t__ pe_data_len; scalar_t__ pe_data; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  caddr; } ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 scalar_t__ IPPROTO_IP ; 
 int IP_VS_CONN_F_TEMPLATE ; 
 int /*<<< orphan*/  IP_VS_DBG_ADDR (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP_VS_DBG_BUF (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IP_VS_DEBUG_CALLID (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ip_vs_addr_equal (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_vs_proto_name (scalar_t__) ; 
 int /*<<< orphan*/  memcmp (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 

__attribute__((used)) static bool ip_vs_sip_ct_match(const struct ip_vs_conn_param *p,
				  struct ip_vs_conn *ct)

{
	bool ret = 0;

	if (ct->af == p->af &&
	    ip_vs_addr_equal(p->af, p->caddr, &ct->caddr) &&
	    /* protocol should only be IPPROTO_IP if
	     * d_addr is a fwmark */
	    ip_vs_addr_equal(p->protocol == IPPROTO_IP ? AF_UNSPEC : p->af,
			     p->vaddr, &ct->vaddr) &&
	    ct->vport == p->vport &&
	    ct->flags & IP_VS_CONN_F_TEMPLATE &&
	    ct->protocol == p->protocol &&
	    ct->pe_data && ct->pe_data_len == p->pe_data_len &&
	    !memcmp(ct->pe_data, p->pe_data, p->pe_data_len))
		ret = 1;

	IP_VS_DBG_BUF(9, "SIP template match %s %s->%s:%d %s\n",
		      ip_vs_proto_name(p->protocol),
		      IP_VS_DEBUG_CALLID(p->pe_data, p->pe_data_len),
		      IP_VS_DBG_ADDR(p->af, p->vaddr), ntohs(p->vport),
		      ret ? "hit" : "not hit");

	return ret;
}