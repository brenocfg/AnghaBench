#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mfsplay_tree_node ;
typedef  scalar_t__ mfsplay_tree_key ;
typedef  TYPE_2__* mfsplay_tree ;
struct TYPE_7__ {TYPE_1__* root; } ;
struct TYPE_6__ {scalar_t__ key; } ;

/* Variables and functions */
 int /*<<< orphan*/  mfsplay_tree_splay (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static mfsplay_tree_node
mfsplay_tree_lookup (mfsplay_tree sp, mfsplay_tree_key key)
{
  mfsplay_tree_splay (sp, key);
  if (sp->root && (sp->root->key == key))
    return sp->root;
  else
    return 0;
}