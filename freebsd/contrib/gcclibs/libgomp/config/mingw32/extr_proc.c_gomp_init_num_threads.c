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
 int /*<<< orphan*/  count_avail_process_cpus () ; 
 int /*<<< orphan*/  gomp_nthreads_var ; 

void
gomp_init_num_threads (void)
{
  gomp_nthreads_var = count_avail_process_cpus ();
}