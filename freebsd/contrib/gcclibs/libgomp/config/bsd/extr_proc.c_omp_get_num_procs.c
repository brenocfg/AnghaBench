#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int nthreads_var; } ;

/* Variables and functions */
 int get_num_procs () ; 
 TYPE_1__* gomp_icv (int) ; 

int
omp_get_num_procs (void)
{
  int ncpus = get_num_procs ();
  if (ncpus <= 0)
    ncpus = gomp_icv (false)->nthreads_var;
  return ncpus;
}