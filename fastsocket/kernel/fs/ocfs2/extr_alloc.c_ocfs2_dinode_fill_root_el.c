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
struct ocfs2_extent_tree {int /*<<< orphan*/ * et_root_el; struct ocfs2_dinode* et_object; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_list; } ;
struct ocfs2_dinode {TYPE_1__ id2; } ;

/* Variables and functions */

__attribute__((used)) static void ocfs2_dinode_fill_root_el(struct ocfs2_extent_tree *et)
{
	struct ocfs2_dinode *di = et->et_object;

	et->et_root_el = &di->id2.i_list;
}