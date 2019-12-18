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
 int EINVAL ; 
 int /*<<< orphan*/  PTHREAD_CREATE_DETACHED ; 
 unsigned long PTHREAD_STACK_MIN ; 
 int /*<<< orphan*/  gomp_dyn_var ; 
 int /*<<< orphan*/  gomp_error (char*,...) ; 
 int /*<<< orphan*/  gomp_init_affinity () ; 
 int /*<<< orphan*/  gomp_init_num_threads () ; 
 int /*<<< orphan*/  gomp_nest_var ; 
 unsigned long gomp_nthreads_var ; 
 int /*<<< orphan*/  gomp_thread_attr ; 
 int /*<<< orphan*/  omp_check_defines () ; 
 scalar_t__ parse_affinity () ; 
 int /*<<< orphan*/  parse_boolean (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_schedule () ; 
 scalar_t__ parse_unsigned_long (char*,unsigned long*) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pthread_attr_setstacksize (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long strerror (int) ; 

__attribute__((used)) static void __attribute__((constructor))
initialize_env (void)
{
  unsigned long stacksize;

  /* Do a compile time check that mkomp_h.pl did good job.  */
  omp_check_defines ();

  parse_schedule ();
  parse_boolean ("OMP_DYNAMIC", &gomp_dyn_var);
  parse_boolean ("OMP_NESTED", &gomp_nest_var);
  if (!parse_unsigned_long ("OMP_NUM_THREADS", &gomp_nthreads_var))
    gomp_init_num_threads ();
  if (parse_affinity ())
    gomp_init_affinity ();

  /* Not strictly environment related, but ordering constructors is tricky.  */
  pthread_attr_init (&gomp_thread_attr);
  pthread_attr_setdetachstate (&gomp_thread_attr, PTHREAD_CREATE_DETACHED);

  if (parse_unsigned_long ("GOMP_STACKSIZE", &stacksize))
    {
      int err;

      stacksize *= 1024;
      err = pthread_attr_setstacksize (&gomp_thread_attr, stacksize);

#ifdef PTHREAD_STACK_MIN
      if (err == EINVAL)
	{
	  if (stacksize < PTHREAD_STACK_MIN)
	    gomp_error ("Stack size less than minimum of %luk",
			PTHREAD_STACK_MIN / 1024ul
			+ (PTHREAD_STACK_MIN % 1024 != 0));
	  else
	    gomp_error ("Stack size larger than system limit");
	}
      else
#endif
      if (err != 0)
	gomp_error ("Stack size change failed: %s", strerror (err));
    }
}