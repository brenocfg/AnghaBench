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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_extent_tree {TYPE_1__* et_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* eo_get_last_eb_blk ) (struct ocfs2_extent_tree*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ocfs2_extent_tree*) ; 

__attribute__((used)) static inline u64 ocfs2_et_get_last_eb_blk(struct ocfs2_extent_tree *et)
{
	return et->et_ops->eo_get_last_eb_blk(et);
}