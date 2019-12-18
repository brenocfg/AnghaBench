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
typedef  TYPE_1__* fibnode_t ;
typedef  TYPE_2__* fibheap_t ;
struct TYPE_7__ {int /*<<< orphan*/ * root; } ;
struct TYPE_6__ {struct TYPE_6__* left; } ;

/* Variables and functions */
 int /*<<< orphan*/ * fibnode_remove (TYPE_1__*) ; 

__attribute__((used)) static void
fibheap_rem_root (fibheap_t heap, fibnode_t node)
{
  if (node->left == node)
    heap->root = NULL;
  else
    heap->root = fibnode_remove (node);
}