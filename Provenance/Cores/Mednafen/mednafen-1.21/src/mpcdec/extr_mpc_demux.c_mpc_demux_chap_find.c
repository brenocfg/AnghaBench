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
typedef  int /*<<< orphan*/  mpc_status ;
typedef  int /*<<< orphan*/  mpc_demux ;

/* Variables and functions */
 scalar_t__ MPC_IS_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc_demux_chap_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpc_demux_chap_find_inner (int /*<<< orphan*/ *) ; 

__attribute__((used)) static mpc_status mpc_demux_chap_find(mpc_demux * d) {
	mpc_status s = mpc_demux_chap_find_inner(d);
	if (MPC_IS_FAILURE(s))
		mpc_demux_chap_empty(d);
	return s;
}