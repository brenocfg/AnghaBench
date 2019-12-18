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
struct loop {struct loop* outer; struct loop* inner; struct loop* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  establish_preds (struct loop*) ; 

void
flow_loop_tree_node_add (struct loop *father, struct loop *loop)
{
  loop->next = father->inner;
  father->inner = loop;
  loop->outer = father;

  establish_preds (loop);
}