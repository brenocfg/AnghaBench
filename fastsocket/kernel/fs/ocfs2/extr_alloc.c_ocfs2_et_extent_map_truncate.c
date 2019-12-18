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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_extent_tree {TYPE_1__* et_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* eo_extent_map_truncate ) (struct ocfs2_extent_tree*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ocfs2_extent_tree*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ocfs2_et_extent_map_truncate(struct ocfs2_extent_tree *et,
						u32 clusters)
{
	if (et->et_ops->eo_extent_map_truncate)
		et->et_ops->eo_extent_map_truncate(et, clusters);
}