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
struct sk_buff {int dummy; } ;
struct nf_conn {int dummy; } ;
typedef  enum sdp_header_types { ____Placeholder_sdp_header_types } sdp_header_types ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ ct_sip_get_sdp_header (struct nf_conn*,char const*,unsigned int,unsigned int,int,int,unsigned int*,unsigned int*) ; 
 scalar_t__ mangle_packet (struct sk_buff*,char const**,unsigned int*,unsigned int,unsigned int,char*,int) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 

__attribute__((used)) static int mangle_sdp_packet(struct sk_buff *skb, const char **dptr,
			     unsigned int dataoff, unsigned int *datalen,
			     enum sdp_header_types type,
			     enum sdp_header_types term,
			     char *buffer, int buflen)
{
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	unsigned int matchlen, matchoff;

	if (ct_sip_get_sdp_header(ct, *dptr, dataoff, *datalen, type, term,
				  &matchoff, &matchlen) <= 0)
		return -ENOENT;
	return mangle_packet(skb, dptr, datalen, matchoff, matchlen,
			     buffer, buflen) ? 0 : -EINVAL;
}