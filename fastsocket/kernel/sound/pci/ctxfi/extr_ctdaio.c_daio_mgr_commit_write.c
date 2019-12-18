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
struct hw {int /*<<< orphan*/  (* daio_mgr_commit_write ) (struct hw*,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl_blk; struct hw* hw; } ;
struct daio_mgr {TYPE_1__ mgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int daio_mgr_commit_write(struct daio_mgr *mgr)
{
	struct hw *hw = mgr->mgr.hw;

	hw->daio_mgr_commit_write(hw, mgr->mgr.ctrl_blk);
	return 0;
}