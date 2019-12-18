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
struct jffs2_inode_info {scalar_t__ usercompr; scalar_t__ flags; int /*<<< orphan*/ * target; int /*<<< orphan*/ * dents; int /*<<< orphan*/ * metadata; int /*<<< orphan*/  fragtree; scalar_t__ highest_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_ROOT ; 

__attribute__((used)) static inline void jffs2_init_inode_info(struct jffs2_inode_info *f)
{
	f->highest_version = 0;
	f->fragtree = RB_ROOT;
	f->metadata = NULL;
	f->dents = NULL;
	f->target = NULL;
	f->flags = 0;
	f->usercompr = 0;
}