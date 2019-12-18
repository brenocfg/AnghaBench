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
typedef  TYPE_1__* splay_tree_node ;
typedef  int /*<<< orphan*/  splay_tree_key ;
typedef  TYPE_2__* splay_tree ;
struct TYPE_7__ {scalar_t__ (* comp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__* root; } ;
struct TYPE_6__ {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  splay_tree_splay (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

splay_tree_node
splay_tree_lookup (splay_tree sp, splay_tree_key key)
{
  splay_tree_splay (sp, key);

  if (sp->root && (*sp->comp)(sp->root->key, key) == 0)
    return sp->root;
  else
    return 0;
}