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
typedef  int /*<<< orphan*/  u64 ;
struct sock {int dummy; } ;
struct dccp_sock {int dccps_r_seq_win; int /*<<< orphan*/  dccps_gsr; int /*<<< orphan*/  dccps_swh; int /*<<< orphan*/  dccps_swl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD48 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SUB48 (int /*<<< orphan*/ ,int) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 

__attribute__((used)) static inline void dccp_update_gsr(struct sock *sk, u64 seq)
{
	struct dccp_sock *dp = dccp_sk(sk);

	dp->dccps_gsr = seq;
	/* Sequence validity window depends on remote Sequence Window (7.5.1) */
	dp->dccps_swl = SUB48(ADD48(dp->dccps_gsr, 1), dp->dccps_r_seq_win / 4);
	dp->dccps_swh = ADD48(dp->dccps_gsr, (3 * dp->dccps_r_seq_win) / 4);
}