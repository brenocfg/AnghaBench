#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/ * sk_send_head; } ;
struct dccp_sock {int /*<<< orphan*/  dccps_featneg; int /*<<< orphan*/ * dccps_hc_tx_ccid; int /*<<< orphan*/  dccps_hc_rx_ccid; int /*<<< orphan*/ * dccps_hc_rx_ackvec; int /*<<< orphan*/ * dccps_service_list; } ;
struct TYPE_2__ {int /*<<< orphan*/ * icsk_bind_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccid_hc_rx_delete (int /*<<< orphan*/ ,struct sock*) ; 
 int /*<<< orphan*/  ccid_hc_tx_delete (int /*<<< orphan*/ *,struct sock*) ; 
 int /*<<< orphan*/  dccp_ackvec_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dccp_feat_list_purge (int /*<<< orphan*/ *) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 TYPE_1__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_put_port (struct sock*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 

void dccp_destroy_sock(struct sock *sk)
{
	struct dccp_sock *dp = dccp_sk(sk);

	/*
	 * DCCP doesn't use sk_write_queue, just sk_send_head
	 * for retransmissions
	 */
	if (sk->sk_send_head != NULL) {
		kfree_skb(sk->sk_send_head);
		sk->sk_send_head = NULL;
	}

	/* Clean up a referenced DCCP bind bucket. */
	if (inet_csk(sk)->icsk_bind_hash != NULL)
		inet_put_port(sk);

	kfree(dp->dccps_service_list);
	dp->dccps_service_list = NULL;

	if (dp->dccps_hc_rx_ackvec != NULL) {
		dccp_ackvec_free(dp->dccps_hc_rx_ackvec);
		dp->dccps_hc_rx_ackvec = NULL;
	}
	ccid_hc_rx_delete(dp->dccps_hc_rx_ccid, sk);
	ccid_hc_tx_delete(dp->dccps_hc_tx_ccid, sk);
	dp->dccps_hc_rx_ccid = dp->dccps_hc_tx_ccid = NULL;

	/* clean up feature negotiation state */
	dccp_feat_list_purge(&dp->dccps_featneg);
}