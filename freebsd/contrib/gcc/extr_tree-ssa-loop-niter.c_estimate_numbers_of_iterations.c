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
struct loops {unsigned int num; struct loop** parray; } ;
struct loop {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  estimate_numbers_of_iterations_loop (struct loop*) ; 
 int /*<<< orphan*/  fold_defer_overflow_warnings () ; 
 int /*<<< orphan*/  fold_undefer_and_ignore_overflow_warnings () ; 

void
estimate_numbers_of_iterations (struct loops *loops)
{
  unsigned i;
  struct loop *loop;

  /* We don't want to issue signed overflow warnings while getting
     loop iteration estimates.  */
  fold_defer_overflow_warnings ();

  for (i = 1; i < loops->num; i++)
    {
      loop = loops->parray[i];
      if (loop)
	estimate_numbers_of_iterations_loop (loop);
    }

  fold_undefer_and_ignore_overflow_warnings ();
}