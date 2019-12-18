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
typedef  int /*<<< orphan*/ * tree ;
struct leh_tf_state {int /*<<< orphan*/  goto_queue_active; int /*<<< orphan*/  goto_queue; } ;
struct goto_queue_node {int /*<<< orphan*/ * repl_stmt; int /*<<< orphan*/ * stmt; } ;

/* Variables and functions */
 scalar_t__ bsearch (struct goto_queue_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  goto_queue_cmp ; 

__attribute__((used)) static tree
find_goto_replacement (struct leh_tf_state *tf, tree stmt)
{
  struct goto_queue_node tmp, *ret;
  tmp.stmt = stmt;
  ret = (struct goto_queue_node *)
     bsearch (&tmp, tf->goto_queue, tf->goto_queue_active,
		 sizeof (struct goto_queue_node), goto_queue_cmp);
  return (ret ? ret->repl_stmt : NULL);
}