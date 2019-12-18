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
struct whc {TYPE_1__* dbg; } ;
struct TYPE_2__ {int /*<<< orphan*/  di_f; int /*<<< orphan*/  asl_f; int /*<<< orphan*/  pzl_f; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

void whc_dbg_clean_up(struct whc *whc)
{
	if (whc->dbg) {
		debugfs_remove(whc->dbg->pzl_f);
		debugfs_remove(whc->dbg->asl_f);
		debugfs_remove(whc->dbg->di_f);
		kfree(whc->dbg);
	}
}