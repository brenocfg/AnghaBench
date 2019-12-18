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

/* Variables and functions */
 int /*<<< orphan*/  CAN_PROC_RCVLIST_ALL ; 
 int /*<<< orphan*/  CAN_PROC_RCVLIST_EFF ; 
 int /*<<< orphan*/  CAN_PROC_RCVLIST_ERR ; 
 int /*<<< orphan*/  CAN_PROC_RCVLIST_FIL ; 
 int /*<<< orphan*/  CAN_PROC_RCVLIST_INV ; 
 int /*<<< orphan*/  CAN_PROC_RCVLIST_SFF ; 
 int /*<<< orphan*/  CAN_PROC_RESET_STATS ; 
 int /*<<< orphan*/  CAN_PROC_STATS ; 
 int /*<<< orphan*/  CAN_PROC_VERSION ; 
 scalar_t__ can_dir ; 
 int /*<<< orphan*/  can_remove_proc_readentry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 scalar_t__ pde_rcvlist_all ; 
 scalar_t__ pde_rcvlist_eff ; 
 scalar_t__ pde_rcvlist_err ; 
 scalar_t__ pde_rcvlist_fil ; 
 scalar_t__ pde_rcvlist_inv ; 
 scalar_t__ pde_rcvlist_sff ; 
 scalar_t__ pde_reset_stats ; 
 scalar_t__ pde_stats ; 
 scalar_t__ pde_version ; 
 int /*<<< orphan*/  proc_net_remove (int /*<<< orphan*/ *,char*) ; 

void can_remove_proc(void)
{
	if (pde_version)
		can_remove_proc_readentry(CAN_PROC_VERSION);

	if (pde_stats)
		can_remove_proc_readentry(CAN_PROC_STATS);

	if (pde_reset_stats)
		can_remove_proc_readentry(CAN_PROC_RESET_STATS);

	if (pde_rcvlist_err)
		can_remove_proc_readentry(CAN_PROC_RCVLIST_ERR);

	if (pde_rcvlist_all)
		can_remove_proc_readentry(CAN_PROC_RCVLIST_ALL);

	if (pde_rcvlist_fil)
		can_remove_proc_readentry(CAN_PROC_RCVLIST_FIL);

	if (pde_rcvlist_inv)
		can_remove_proc_readentry(CAN_PROC_RCVLIST_INV);

	if (pde_rcvlist_eff)
		can_remove_proc_readentry(CAN_PROC_RCVLIST_EFF);

	if (pde_rcvlist_sff)
		can_remove_proc_readentry(CAN_PROC_RCVLIST_SFF);

	if (can_dir)
		proc_net_remove(&init_net, "can");
}