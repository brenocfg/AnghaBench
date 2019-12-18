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
typedef  int /*<<< orphan*/  splay_tree_delete_value_fn ;
typedef  int /*<<< orphan*/  splay_tree_delete_key_fn ;
typedef  int /*<<< orphan*/  splay_tree_compare_fn ;
typedef  int /*<<< orphan*/  splay_tree ;

/* Variables and functions */
 int /*<<< orphan*/  splay_tree_new_with_allocator (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  splay_tree_xmalloc_allocate ; 
 int /*<<< orphan*/  splay_tree_xmalloc_deallocate ; 

splay_tree 
splay_tree_new (splay_tree_compare_fn compare_fn,
                splay_tree_delete_key_fn delete_key_fn,
                splay_tree_delete_value_fn delete_value_fn)
{
  return (splay_tree_new_with_allocator
          (compare_fn, delete_key_fn, delete_value_fn,
           splay_tree_xmalloc_allocate, splay_tree_xmalloc_deallocate, 0));
}