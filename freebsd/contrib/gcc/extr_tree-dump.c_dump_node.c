#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct dump_info {int flags; int /*<<< orphan*/  nodes; TYPE_1__* free_list; scalar_t__ queue; int /*<<< orphan*/  node; scalar_t__ queue_end; scalar_t__ column; scalar_t__ index; int /*<<< orphan*/ * stream; } ;
typedef  int /*<<< orphan*/  splay_tree_delete_value_fn ;
typedef  TYPE_1__* dump_queue_p ;
struct TYPE_3__ {struct TYPE_3__* next; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_NONE ; 
 int /*<<< orphan*/  dequeue_and_dump (struct dump_info*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  queue (struct dump_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  splay_tree_compare_pointers ; 
 int /*<<< orphan*/  splay_tree_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  splay_tree_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dump_node (tree t, int flags, FILE *stream)
{
  struct dump_info di;
  dump_queue_p dq;
  dump_queue_p next_dq;

  /* Initialize the dump-information structure.  */
  di.stream = stream;
  di.index = 0;
  di.column = 0;
  di.queue = 0;
  di.queue_end = 0;
  di.free_list = 0;
  di.flags = flags;
  di.node = t;
  di.nodes = splay_tree_new (splay_tree_compare_pointers, 0,
			     (splay_tree_delete_value_fn) &free);

  /* Queue up the first node.  */
  queue (&di, t, DUMP_NONE);

  /* Until the queue is empty, keep dumping nodes.  */
  while (di.queue)
    dequeue_and_dump (&di);

  /* Now, clean up.  */
  for (dq = di.free_list; dq; dq = next_dq)
    {
      next_dq = dq->next;
      free (dq);
    }
  splay_tree_delete (di.nodes);
}