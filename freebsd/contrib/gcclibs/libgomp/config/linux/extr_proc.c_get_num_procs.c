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
 int /*<<< orphan*/  CPU_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 int cpuset_popcount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gomp_cpu_affinity ; 
 size_t gomp_cpu_affinity_len ; 
 int gomp_nthreads_var ; 
 scalar_t__ pthread_getaffinity_np (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_num_procs (void)
{
#ifdef HAVE_PTHREAD_AFFINITY_NP
  cpu_set_t cpuset;

  if (gomp_cpu_affinity == NULL)
    {
      /* Count only the CPUs this process can use.  */
      if (pthread_getaffinity_np (pthread_self (), sizeof (cpuset),
				  &cpuset) == 0)
	{
	  int ret = cpuset_popcount (&cpuset);
	  return ret != 0 ? ret : 1;
	}
    }
  else
    {
      size_t idx;
      static int affinity_cpus;

      /* We can't use pthread_getaffinity_np in this case
	 (we have changed it ourselves, it binds to just one CPU).
	 Count instead the number of different CPUs we are
	 using.  */
      CPU_ZERO (&cpuset);
      if (affinity_cpus == 0)
	{
	  int cpus = 0;
	  for (idx = 0; idx < gomp_cpu_affinity_len; idx++)
	    if (! CPU_ISSET (gomp_cpu_affinity[idx], &cpuset))
	      {
		cpus++;
		CPU_SET (gomp_cpu_affinity[idx], &cpuset);
	      }
	  affinity_cpus = cpus;
	}
      return affinity_cpus;
    }
#endif
#ifdef _SC_NPROCESSORS_ONLN
  return sysconf (_SC_NPROCESSORS_ONLN);
#else
  return gomp_nthreads_var;
#endif
}