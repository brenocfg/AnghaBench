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
struct nb_iter_bound {struct nb_iter_bound* next; } ;
struct loop {struct nb_iter_bound* bounds; int /*<<< orphan*/ * estimated_nb_iterations; int /*<<< orphan*/ * nb_iterations; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct nb_iter_bound*) ; 

void
free_numbers_of_iterations_estimates_loop (struct loop *loop)
{
  struct nb_iter_bound *bound, *next;

  loop->nb_iterations = NULL;
  loop->estimated_nb_iterations = NULL;
  for (bound = loop->bounds; bound; bound = next)
    {
      next = bound->next;
      free (bound);
    }

  loop->bounds = NULL;
}