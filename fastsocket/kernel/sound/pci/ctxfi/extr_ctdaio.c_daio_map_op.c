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
struct rsc_mgr {int /*<<< orphan*/  ctrl_blk; struct hw* hw; } ;
struct imapper {int /*<<< orphan*/  addr; int /*<<< orphan*/  next; int /*<<< orphan*/  slot; } ;
struct hw {int /*<<< orphan*/  (* daio_mgr_commit_write ) (struct hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* daio_mgr_set_imapaddr ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* daio_mgr_set_imapnxt ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* daio_mgr_set_imaparc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct daio_mgr {struct rsc_mgr mgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int daio_map_op(void *data, struct imapper *entry)
{
	struct rsc_mgr *mgr = &((struct daio_mgr *)data)->mgr;
	struct hw *hw = mgr->hw;

	hw->daio_mgr_set_imaparc(mgr->ctrl_blk, entry->slot);
	hw->daio_mgr_set_imapnxt(mgr->ctrl_blk, entry->next);
	hw->daio_mgr_set_imapaddr(mgr->ctrl_blk, entry->addr);
	hw->daio_mgr_commit_write(mgr->hw, mgr->ctrl_blk);

	return 0;
}