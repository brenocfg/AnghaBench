#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* fibnode_t ;
typedef  int /*<<< orphan*/  fibheap_t ;
struct TYPE_6__ {scalar_t__ mark; int /*<<< orphan*/ * parent; int /*<<< orphan*/  degree; } ;

/* Variables and functions */
 int /*<<< orphan*/  fibheap_ins_root (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  fibnode_remove (TYPE_1__*) ; 

__attribute__((used)) static void
fibheap_cut (fibheap_t heap, fibnode_t node, fibnode_t parent)
{
  fibnode_remove (node);
  parent->degree--;
  fibheap_ins_root (heap, node);
  node->parent = NULL;
  node->mark = 0;
}