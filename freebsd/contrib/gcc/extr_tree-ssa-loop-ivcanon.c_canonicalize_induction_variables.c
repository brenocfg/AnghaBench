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
 unsigned int TODO_cleanup_cfg ; 
 int /*<<< orphan*/  UL_SINGLE_ITER ; 
 int canonicalize_loop_induction_variables (struct loops*,struct loop*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scev_reset () ; 

unsigned int
canonicalize_induction_variables (struct loops *loops)
{
  unsigned i;
  struct loop *loop;
  bool changed = false;
  
  for (i = 1; i < loops->num; i++)
    {
      loop = loops->parray[i];

      if (loop)
	changed |= canonicalize_loop_induction_variables (loops, loop,
							  true, UL_SINGLE_ITER,
							  true);
    }

  /* Clean up the information about numbers of iterations, since brute force
     evaluation could reveal new information.  */
  scev_reset ();

  if (changed)
    return TODO_cleanup_cfg;
  return 0;
}