#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_4__ {unsigned int invite_cseq; } ;
struct TYPE_3__ {TYPE_2__ ct_sip_info; } ;
struct nf_conn_help {TYPE_1__ help; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int NF_ACCEPT ; 
 int /*<<< orphan*/  flush_expectations (struct nf_conn*,int) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 struct nf_conn_help* nfct_help (struct nf_conn*) ; 
 int process_sdp (struct sk_buff*,char const**,unsigned int*,unsigned int) ; 

__attribute__((used)) static int process_prack_response(struct sk_buff *skb,
				  const char **dptr, unsigned int *datalen,
				  unsigned int cseq, unsigned int code)
{
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	struct nf_conn_help *help = nfct_help(ct);

	if ((code >= 100 && code <= 199) ||
	    (code >= 200 && code <= 299))
		return process_sdp(skb, dptr, datalen, cseq);
	else if (help->help.ct_sip_info.invite_cseq == cseq)
		flush_expectations(ct, true);
	return NF_ACCEPT;
}