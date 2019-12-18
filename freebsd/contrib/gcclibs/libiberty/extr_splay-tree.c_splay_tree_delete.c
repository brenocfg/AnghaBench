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
typedef  TYPE_1__* splay_tree ;
struct TYPE_4__ {int /*<<< orphan*/  allocate_data; int /*<<< orphan*/  (* deallocate ) (char*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  splay_tree_delete_helper (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ ) ; 

void 
splay_tree_delete (splay_tree sp)
{
  splay_tree_delete_helper (sp, sp->root);
  (*sp->deallocate) ((char*) sp, sp->allocate_data);
}