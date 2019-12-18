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
struct sock {int dummy; } ;
struct dccp_sock {scalar_t__ dccps_timestamp_echo; int /*<<< orphan*/ * dccps_hc_rx_ackvec; } ;

/* Variables and functions */
 scalar_t__ dccp_ackvec_pending (int /*<<< orphan*/ *) ; 
 struct dccp_sock* dccp_sk (struct sock const*) ; 
 scalar_t__ inet_csk_ack_scheduled (struct sock const*) ; 

__attribute__((used)) static inline int dccp_ack_pending(const struct sock *sk)
{
	const struct dccp_sock *dp = dccp_sk(sk);
	return dp->dccps_timestamp_echo != 0 ||
	       (dp->dccps_hc_rx_ackvec != NULL &&
		dccp_ackvec_pending(dp->dccps_hc_rx_ackvec)) ||
	       inet_csk_ack_scheduled(sk);
}