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
typedef  int /*<<< orphan*/  u8 ;
struct sock {int sk_state; } ;
struct list_head {int dummy; } ;
struct dccp_sock {struct list_head dccps_featneg; } ;
struct dccp_request_sock {struct list_head dreq_featneg; } ;

/* Variables and functions */
#define  DCCPO_CHANGE_L 133 
#define  DCCPO_CHANGE_R 132 
#define  DCCPO_CONFIRM_L 131 
#define  DCCPO_CONFIRM_R 130 
#define  DCCP_LISTEN 129 
#define  DCCP_REQUESTING 128 
 int dccp_feat_change_recv (struct list_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int dccp_feat_confirm_recv (struct list_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 

int dccp_feat_parse_options(struct sock *sk, struct dccp_request_sock *dreq,
			    u8 mandatory, u8 opt, u8 feat, u8 *val, u8 len)
{
	struct dccp_sock *dp = dccp_sk(sk);
	struct list_head *fn = dreq ? &dreq->dreq_featneg : &dp->dccps_featneg;
	bool server = false;

	switch (sk->sk_state) {
	/*
	 *	Negotiation during connection setup
	 */
	case DCCP_LISTEN:
		server = true;			/* fall through */
	case DCCP_REQUESTING:
		switch (opt) {
		case DCCPO_CHANGE_L:
		case DCCPO_CHANGE_R:
			return dccp_feat_change_recv(fn, mandatory, opt, feat,
						     val, len, server);
		case DCCPO_CONFIRM_R:
		case DCCPO_CONFIRM_L:
			return dccp_feat_confirm_recv(fn, mandatory, opt, feat,
						      val, len, server);
		}
	}
	return 0;	/* ignore FN options in all other states */
}