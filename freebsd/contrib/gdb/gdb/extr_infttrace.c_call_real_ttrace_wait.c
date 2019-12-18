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
typedef  int /*<<< orphan*/  ttwopt_t ;
typedef  int /*<<< orphan*/  ttstate_t ;
typedef  int /*<<< orphan*/  thread_info ;
typedef  int lwpid_t ;

/* Variables and functions */
 scalar_t__ debug_on ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int ttrace_wait (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
call_real_ttrace_wait (int pid, lwpid_t tid, ttwopt_t option, ttstate_t *tsp,
		       size_t tsp_size)
{
  int ttw_status;
  thread_info *tinfo = NULL;

  errno = 0;
  ttw_status = ttrace_wait (pid, tid, option, tsp, tsp_size);

  if (errno)
    {
#ifdef THREAD_DEBUG
      if (debug_on)
	printf ("TW fail with pid %d, tid %d \n", pid, tid);
#endif

      perror_with_name ("ttrace wait");
    }

  return ttw_status;
}