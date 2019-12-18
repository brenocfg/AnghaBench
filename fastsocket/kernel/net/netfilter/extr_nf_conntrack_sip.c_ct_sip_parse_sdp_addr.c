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
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
struct nf_conn {int dummy; } ;
typedef  enum sdp_header_types { ____Placeholder_sdp_header_types } sdp_header_types ;

/* Variables and functions */
 int ct_sip_get_sdp_header (struct nf_conn const*,char const*,unsigned int,unsigned int,int,int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  parse_addr (struct nf_conn const*,char const*,int /*<<< orphan*/ *,union nf_inet_addr*,char const*) ; 

__attribute__((used)) static int ct_sip_parse_sdp_addr(const struct nf_conn *ct, const char *dptr,
				 unsigned int dataoff, unsigned int datalen,
				 enum sdp_header_types type,
				 enum sdp_header_types term,
				 unsigned int *matchoff, unsigned int *matchlen,
				 union nf_inet_addr *addr)
{
	int ret;

	ret = ct_sip_get_sdp_header(ct, dptr, dataoff, datalen, type, term,
				    matchoff, matchlen);
	if (ret <= 0)
		return ret;

	if (!parse_addr(ct, dptr + *matchoff, NULL, addr,
			dptr + *matchoff + *matchlen))
		return -1;
	return 1;
}