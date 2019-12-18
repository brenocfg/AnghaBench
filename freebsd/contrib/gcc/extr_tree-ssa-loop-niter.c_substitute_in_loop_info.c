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
typedef  int /*<<< orphan*/  tree ;
struct loop {void* estimated_nb_iterations; void* nb_iterations; } ;

/* Variables and functions */
 void* simplify_replace_tree (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
substitute_in_loop_info (struct loop *loop, tree name, tree val)
{
  loop->nb_iterations = simplify_replace_tree (loop->nb_iterations, name, val);
  loop->estimated_nb_iterations
	  = simplify_replace_tree (loop->estimated_nb_iterations, name, val);
}