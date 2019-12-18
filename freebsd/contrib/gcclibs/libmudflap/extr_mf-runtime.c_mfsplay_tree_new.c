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
struct mfsplay_tree_s {int dummy; } ;
typedef  TYPE_1__* mfsplay_tree ;
struct TYPE_4__ {scalar_t__ num_keys; scalar_t__ last_splayed_key_p; int /*<<< orphan*/ * root; } ;

/* Variables and functions */
 TYPE_1__* mfsplay_tree_xmalloc (int) ; 

__attribute__((used)) static mfsplay_tree
mfsplay_tree_new ()
{
  mfsplay_tree sp = mfsplay_tree_xmalloc (sizeof (struct mfsplay_tree_s));
  sp->root = NULL;
  sp->last_splayed_key_p = 0;
  sp->num_keys = 0;

  return sp;
}