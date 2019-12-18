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
typedef  int /*<<< orphan*/  cpuset ;
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 int cpuset_popcount (int /*<<< orphan*/ *) ; 
 int gomp_nthreads_var ; 
 scalar_t__ pthread_getaffinity_np (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int sysconf (int /*<<< orphan*/ ) ; 

void
gomp_init_num_threads (void)
{
#ifdef HAVE_PTHREAD_AFFINITY_NP
  cpu_set_t cpuset;

  if (pthread_getaffinity_np (pthread_self (), sizeof (cpuset), &cpuset) == 0)
    {
      /* Count only the CPUs this process can use.  */
      gomp_nthreads_var = cpuset_popcount (&cpuset);
      if (gomp_nthreads_var == 0)
	gomp_nthreads_var = 1;
      return;
    }
#endif
#ifdef _SC_NPROCESSORS_ONLN
  gomp_nthreads_var = sysconf (_SC_NPROCESSORS_ONLN);
#endif
}