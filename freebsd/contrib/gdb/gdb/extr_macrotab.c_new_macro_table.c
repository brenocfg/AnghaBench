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
struct obstack {int dummy; } ;
struct macro_table {int /*<<< orphan*/  definitions; int /*<<< orphan*/ * main_source; struct bcache* bcache; struct obstack* obstack; } ;
struct bcache {int dummy; } ;
typedef  int /*<<< orphan*/  splay_tree_delete_value_fn ;
typedef  int /*<<< orphan*/  splay_tree_delete_key_fn ;
typedef  int /*<<< orphan*/  splay_tree_deallocate_fn ;
typedef  int /*<<< orphan*/  splay_tree_allocate_fn ;

/* Variables and functions */
 scalar_t__ macro_alloc ; 
 scalar_t__ macro_free ; 
 int /*<<< orphan*/  macro_tree_compare ; 
 scalar_t__ macro_tree_delete_key ; 
 scalar_t__ macro_tree_delete_value ; 
 int /*<<< orphan*/  memset (struct macro_table*,int /*<<< orphan*/ ,int) ; 
 struct macro_table* obstack_alloc (struct obstack*,int) ; 
 int /*<<< orphan*/  splay_tree_new_with_allocator (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct macro_table*) ; 
 struct macro_table* xmalloc (int) ; 

struct macro_table *
new_macro_table (struct obstack *obstack,
                 struct bcache *b)
{
  struct macro_table *t;

  /* First, get storage for the `struct macro_table' itself.  */
  if (obstack)
    t = obstack_alloc (obstack, sizeof (*t));
  else
    t = xmalloc (sizeof (*t));

  memset (t, 0, sizeof (*t));
  t->obstack = obstack;
  t->bcache = b;
  t->main_source = NULL;
  t->definitions = (splay_tree_new_with_allocator
                    (macro_tree_compare,
                     ((splay_tree_delete_key_fn) macro_tree_delete_key),
                     ((splay_tree_delete_value_fn) macro_tree_delete_value),
                     ((splay_tree_allocate_fn) macro_alloc),
                     ((splay_tree_deallocate_fn) macro_free),
                     t));
  
  return t;
}