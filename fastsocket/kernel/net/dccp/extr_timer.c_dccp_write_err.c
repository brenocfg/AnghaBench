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
struct sock {int /*<<< orphan*/  (* sk_error_report ) (struct sock*) ;scalar_t__ sk_err_soft; int /*<<< orphan*/  sk_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_INC_STATS_BH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCCP_MIB_ABORTONTIMEOUT ; 
 int /*<<< orphan*/  DCCP_RESET_CODE_ABORTED ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  dccp_done (struct sock*) ; 
 int /*<<< orphan*/  dccp_send_reset (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void dccp_write_err(struct sock *sk)
{
	sk->sk_err = sk->sk_err_soft ? : ETIMEDOUT;
	sk->sk_error_report(sk);

	dccp_send_reset(sk, DCCP_RESET_CODE_ABORTED);
	dccp_done(sk);
	DCCP_INC_STATS_BH(DCCP_MIB_ABORTONTIMEOUT);
}