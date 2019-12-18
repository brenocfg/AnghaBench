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

/* Variables and functions */
 int count_avail_process_cpus () ; 
 int gomp_nthreads_var ; 

unsigned
gomp_dynamic_max_threads (void)
{
  int n_onln = count_avail_process_cpus ();
  return n_onln > gomp_nthreads_var ? gomp_nthreads_var : n_onln;
}