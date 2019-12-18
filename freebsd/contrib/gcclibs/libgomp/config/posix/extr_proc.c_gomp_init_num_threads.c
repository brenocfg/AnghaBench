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
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 int /*<<< orphan*/  gomp_nthreads_var ; 
 int /*<<< orphan*/  sysconf (int /*<<< orphan*/ ) ; 

void
gomp_init_num_threads (void)
{
#ifdef _SC_NPROCESSORS_ONLN
  gomp_nthreads_var = sysconf (_SC_NPROCESSORS_ONLN);
#endif
}