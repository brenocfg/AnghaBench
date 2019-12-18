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
typedef  int /*<<< orphan*/  tree_stmt_iterator ;
typedef  int /*<<< orphan*/  tree ;
struct leh_tf_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  replace_goto_queue_1 (int /*<<< orphan*/ ,struct leh_tf_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
replace_goto_queue_stmt_list (tree t, struct leh_tf_state *tf)
{
  tree_stmt_iterator i = tsi_start (t);
  while (!tsi_end_p (i))
    replace_goto_queue_1 (tsi_stmt (i), tf, &i);
}