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
typedef  int /*<<< orphan*/  uint ;
struct qtree_mem_dqinfo {int dummy; } ;
struct dquot {int /*<<< orphan*/  dq_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  QT_TREEOFF ; 
 int remove_tree (struct qtree_mem_dqinfo*,struct dquot*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int qtree_delete_dquot(struct qtree_mem_dqinfo *info, struct dquot *dquot)
{
	uint tmp = QT_TREEOFF;

	if (!dquot->dq_off)	/* Even not allocated? */
		return 0;
	return remove_tree(info, dquot, &tmp, 0);
}