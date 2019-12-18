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
struct loops {int dummy; } ;

/* Variables and functions */
 int LOOPS_HAVE_MARKED_SINGLE_EXITS ; 
 int LOOPS_NORMAL ; 
 int /*<<< orphan*/  TODO_update_ssa ; 
 struct loops* loop_optimizer_init (int) ; 
 int /*<<< orphan*/  rewrite_into_loop_closed_ssa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct loops *
tree_loop_optimizer_init (void)
{
  struct loops *loops;
 
  loops = loop_optimizer_init (LOOPS_NORMAL
			       | LOOPS_HAVE_MARKED_SINGLE_EXITS);

  if (!loops)
    return NULL;

  rewrite_into_loop_closed_ssa (NULL, TODO_update_ssa);

  return loops;
}