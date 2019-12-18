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
struct leh_tf_state {scalar_t__ goto_queue_active; int /*<<< orphan*/ * top_p; } ;

/* Variables and functions */
 int /*<<< orphan*/  replace_goto_queue_stmt_list (int /*<<< orphan*/ ,struct leh_tf_state*) ; 

__attribute__((used)) static void
replace_goto_queue (struct leh_tf_state *tf)
{
  if (tf->goto_queue_active == 0)
    return;
  replace_goto_queue_stmt_list (*tf->top_p, tf);
}