#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  splay_tree_foreach_fn ;
typedef  TYPE_1__* splay_tree ;
struct TYPE_4__ {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int splay_tree_foreach_helper (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

int
splay_tree_foreach (splay_tree sp, splay_tree_foreach_fn fn, void *data)
{
  return splay_tree_foreach_helper (sp, sp->root, fn, data);
}