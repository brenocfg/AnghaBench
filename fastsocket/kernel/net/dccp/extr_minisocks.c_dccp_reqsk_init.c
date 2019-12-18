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
struct request_sock {int dummy; } ;
struct dccp_sock {int /*<<< orphan*/  dccps_featneg; } ;
struct dccp_request_sock {int /*<<< orphan*/  dreq_featneg; scalar_t__ dreq_timestamp_echo; } ;
struct TYPE_4__ {int /*<<< orphan*/  dccph_dport; int /*<<< orphan*/  dccph_sport; } ;
struct TYPE_3__ {scalar_t__ acked; int /*<<< orphan*/  loc_port; int /*<<< orphan*/  rmt_port; } ;

/* Variables and functions */
 int dccp_feat_clone_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* dccp_hdr (struct sk_buff const*) ; 
 struct dccp_request_sock* dccp_rsk (struct request_sock*) ; 
 TYPE_1__* inet_rsk (struct request_sock*) ; 

int dccp_reqsk_init(struct request_sock *req,
		    struct dccp_sock const *dp, struct sk_buff const *skb)
{
	struct dccp_request_sock *dreq = dccp_rsk(req);

	inet_rsk(req)->rmt_port	  = dccp_hdr(skb)->dccph_sport;
	inet_rsk(req)->loc_port	  = dccp_hdr(skb)->dccph_dport;
	inet_rsk(req)->acked	  = 0;
	dreq->dreq_timestamp_echo = 0;

	/* inherit feature negotiation options from listening socket */
	return dccp_feat_clone_list(&dp->dccps_featneg, &dreq->dreq_featneg);
}