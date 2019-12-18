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
typedef  void* u64 ;
struct sock {int dummy; } ;
struct dccp_sock {int /*<<< orphan*/  dccps_gss; void* dccps_l_seq_win; int /*<<< orphan*/  dccps_gsr; void* dccps_r_seq_win; } ;

/* Variables and functions */
 struct dccp_sock* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  dccp_update_gsr (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dccp_update_gss (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dccp_hdlr_seq_win(struct sock *sk, u64 seq_win, bool rx)
{
	struct dccp_sock *dp = dccp_sk(sk);

	if (rx) {
		dp->dccps_r_seq_win = seq_win;
		/* propagate changes to update SWL/SWH */
		dccp_update_gsr(sk, dp->dccps_gsr);
	} else {
		dp->dccps_l_seq_win = seq_win;
		/* propagate changes to update AWL */
		dccp_update_gss(sk, dp->dccps_gss);
	}
	return 0;
}