#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mfsplay_tree_key ;
typedef  TYPE_1__* mfsplay_tree ;
struct TYPE_5__ {scalar_t__ root; int last_splayed_key_p; scalar_t__ last_splayed_key; int max_depth; scalar_t__ rebalance_p; scalar_t__ depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  mfsplay_tree_rebalance (TYPE_1__*) ; 
 int /*<<< orphan*/  mfsplay_tree_splay_helper (TYPE_1__*,scalar_t__,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mfsplay_tree_splay (mfsplay_tree sp, mfsplay_tree_key key)
{
  if (sp->root == 0)
    return;

  /* If we just splayed the tree with the same key, do nothing.  */
  if (sp->last_splayed_key_p &&
      (sp->last_splayed_key == key))
    return;

  /* Compute a maximum recursion depth for a splay tree with NUM nodes.
     The idea is to limit excessive stack usage if we're facing
     degenerate access patterns.  Unfortunately such patterns can occur
     e.g. during static initialization, where many static objects might
     be registered in increasing address sequence, or during a case where
     large tree-like heap data structures are allocated quickly.

     On x86, this corresponds to roughly 200K of stack usage.
     XXX: For libmudflapth, this could be a function of __mf_opts.thread_stack.  */
  sp->max_depth = 2500;
  sp->rebalance_p = sp->depth = 0;

  mfsplay_tree_splay_helper (sp, key, &sp->root, NULL, NULL);
  if (sp->rebalance_p)
    {
      mfsplay_tree_rebalance (sp);

      sp->rebalance_p = sp->depth = 0;
      mfsplay_tree_splay_helper (sp, key, &sp->root, NULL, NULL);

      if (sp->rebalance_p)
        abort ();
    }


  /* Cache this splay key. */
  sp->last_splayed_key = key;
  sp->last_splayed_key_p = 1;
}