#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct extent_state {int dummy; } ;
struct extent_io_tree {TYPE_2__* mapping; TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  host; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* split_extent_hook ) (int /*<<< orphan*/ ,struct extent_state*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct extent_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void split_cb(struct extent_io_tree *tree, struct extent_state *orig,
		     u64 split)
{
	if (tree->ops && tree->ops->split_extent_hook)
		tree->ops->split_extent_hook(tree->mapping->host, orig, split);
}