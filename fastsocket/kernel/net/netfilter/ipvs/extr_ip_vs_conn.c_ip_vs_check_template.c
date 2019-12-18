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
struct ip_vs_dest {int flags; int /*<<< orphan*/  weight; } ;
struct ip_vs_conn {scalar_t__ cport; scalar_t__ vport; scalar_t__ dport; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  daddr; int /*<<< orphan*/  af; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  caddr; int /*<<< orphan*/  protocol; struct ip_vs_dest* dest; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_VS_DBG_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IP_VS_DBG_BUF (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IP_VS_DEST_F_AVAILABLE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ htons (int) ; 
 int /*<<< orphan*/  ip_vs_conn_hash (struct ip_vs_conn*) ; 
 scalar_t__ ip_vs_conn_unhash (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  ip_vs_proto_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 
 scalar_t__ sysctl_ip_vs_expire_quiescent_template ; 

int ip_vs_check_template(struct ip_vs_conn *ct)
{
	struct ip_vs_dest *dest = ct->dest;

	/*
	 * Checking the dest server status.
	 */
	if ((dest == NULL) ||
	    !(dest->flags & IP_VS_DEST_F_AVAILABLE) ||
	    (sysctl_ip_vs_expire_quiescent_template &&
	     (atomic_read(&dest->weight) == 0))) {
		IP_VS_DBG_BUF(9, "check_template: dest not available for "
			      "protocol %s s:%s:%d v:%s:%d "
			      "-> d:%s:%d\n",
			      ip_vs_proto_name(ct->protocol),
			      IP_VS_DBG_ADDR(ct->af, &ct->caddr),
			      ntohs(ct->cport),
			      IP_VS_DBG_ADDR(ct->af, &ct->vaddr),
			      ntohs(ct->vport),
			      IP_VS_DBG_ADDR(ct->af, &ct->daddr),
			      ntohs(ct->dport));

		/*
		 * Invalidate the connection template
		 */
		if (ct->vport != htons(0xffff)) {
			if (ip_vs_conn_unhash(ct)) {
				ct->dport = htons(0xffff);
				ct->vport = htons(0xffff);
				ct->cport = 0;
				ip_vs_conn_hash(ct);
			}
		}

		/*
		 * Simply decrease the refcnt of the template,
		 * don't restart its timer.
		 */
		atomic_dec(&ct->refcnt);
		return 0;
	}
	return 1;
}