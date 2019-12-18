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
struct splay_tree_s {int dummy; } ;
typedef  int /*<<< orphan*/  splay_tree_delete_value_fn ;
typedef  int /*<<< orphan*/  splay_tree_delete_key_fn ;
typedef  int /*<<< orphan*/  splay_tree_deallocate_fn ;
typedef  int /*<<< orphan*/  splay_tree_compare_fn ;
typedef  int /*<<< orphan*/  (* splay_tree_allocate_fn ) (int,void*) ;
typedef  TYPE_1__* splay_tree ;
struct TYPE_3__ {void* allocate_data; int /*<<< orphan*/  deallocate; int /*<<< orphan*/  (* allocate ) (int,void*) ;int /*<<< orphan*/  delete_value; int /*<<< orphan*/  delete_key; int /*<<< orphan*/  comp; scalar_t__ root; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int,void*) ; 

splay_tree 
splay_tree_new_with_allocator (splay_tree_compare_fn compare_fn,
                               splay_tree_delete_key_fn delete_key_fn,
                               splay_tree_delete_value_fn delete_value_fn,
                               splay_tree_allocate_fn allocate_fn,
                               splay_tree_deallocate_fn deallocate_fn,
                               void *allocate_data)
{
  splay_tree sp = (splay_tree) (*allocate_fn) (sizeof (struct splay_tree_s),
                                               allocate_data);
  sp->root = 0;
  sp->comp = compare_fn;
  sp->delete_key = delete_key_fn;
  sp->delete_value = delete_value_fn;
  sp->allocate = allocate_fn;
  sp->deallocate = deallocate_fn;
  sp->allocate_data = allocate_data;

  return sp;
}