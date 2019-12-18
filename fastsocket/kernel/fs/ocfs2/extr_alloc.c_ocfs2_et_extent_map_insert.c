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
struct ocfs2_extent_tree {TYPE_1__* et_ops; } ;
struct ocfs2_extent_rec {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* eo_extent_map_insert ) (struct ocfs2_extent_tree*,struct ocfs2_extent_rec*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ocfs2_extent_tree*,struct ocfs2_extent_rec*) ; 

__attribute__((used)) static inline void ocfs2_et_extent_map_insert(struct ocfs2_extent_tree *et,
					      struct ocfs2_extent_rec *rec)
{
	if (et->et_ops->eo_extent_map_insert)
		et->et_ops->eo_extent_map_insert(et, rec);
}