#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  splay_tree_value ;
typedef  int /*<<< orphan*/  splay_tree_key ;
struct TYPE_3__ {int /*<<< orphan*/  decl_map; } ;
typedef  TYPE_1__ copy_body_data ;

/* Variables and functions */
 int /*<<< orphan*/  splay_tree_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
insert_decl_map (copy_body_data *id, tree key, tree value)
{
  splay_tree_insert (id->decl_map, (splay_tree_key) key,
		     (splay_tree_value) value);

  /* Always insert an identity map as well.  If we see this same new
     node again, we won't want to duplicate it a second time.  */
  if (key != value)
    splay_tree_insert (id->decl_map, (splay_tree_key) value,
		       (splay_tree_value) value);
}