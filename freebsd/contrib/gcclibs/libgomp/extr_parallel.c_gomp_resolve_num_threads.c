#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ team; } ;
struct TYPE_4__ {TYPE_1__ ts; } ;

/* Variables and functions */
 scalar_t__ gomp_dyn_var ; 
 unsigned int gomp_dynamic_max_threads () ; 
 int /*<<< orphan*/  gomp_nest_var ; 
 unsigned int gomp_nthreads_var ; 
 TYPE_2__* gomp_thread () ; 

unsigned
gomp_resolve_num_threads (unsigned specified)
{
  /* Early exit for false IF condition or degenerate NUM_THREADS.  */
  if (specified == 1)
    return 1;

  /* If this is a nested region, and nested regions are disabled, force
     this team to use only one thread.  */
  if (gomp_thread()->ts.team && !gomp_nest_var)
    return 1;

  /* If NUM_THREADS not specified, use nthreads_var.  */
  if (specified == 0)
    specified = gomp_nthreads_var;

  /* If dynamic threads are enabled, bound the number of threads
     that we launch.  */
  if (gomp_dyn_var)
    {
      unsigned dyn = gomp_dynamic_max_threads ();
      if (dyn < specified)
	return dyn;
    }

  return specified;
}