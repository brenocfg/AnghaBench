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
struct leh_tf_state {int goto_queue_active; void** top_p; struct goto_queue_node* goto_queue; int /*<<< orphan*/ * eh_label; scalar_t__ may_throw; } ;
struct leh_state {int dummy; } ;
struct goto_queue_node {scalar_t__ index; } ;

/* Variables and functions */
 int /*<<< orphan*/  LABEL_EXPR ; 
 void* TREE_OPERAND (void*,int) ; 
 int /*<<< orphan*/  append_to_statement_list (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_artificial_label () ; 
 int /*<<< orphan*/  do_goto_redirection (struct goto_queue_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_return_redirection (struct goto_queue_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lower_eh_constructs_1 (struct leh_state*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  replace_goto_queue (struct leh_tf_state*) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
lower_try_finally_nofallthru (struct leh_state *state, struct leh_tf_state *tf)
{
  tree x, finally, lab, return_val;
  struct goto_queue_node *q, *qe;

  if (tf->may_throw)
    lab = tf->eh_label;
  else
    lab = create_artificial_label ();

  finally = TREE_OPERAND (*tf->top_p, 1);
  *tf->top_p = TREE_OPERAND (*tf->top_p, 0);

  x = build1 (LABEL_EXPR, void_type_node, lab);
  append_to_statement_list (x, tf->top_p);

  return_val = NULL;
  q = tf->goto_queue;
  qe = q + tf->goto_queue_active;
  for (; q < qe; ++q)
    if (q->index < 0)
      do_return_redirection (q, lab, NULL, &return_val);
    else
      do_goto_redirection (q, lab, NULL);

  replace_goto_queue (tf);

  lower_eh_constructs_1 (state, &finally);
  append_to_statement_list (finally, tf->top_p);
}