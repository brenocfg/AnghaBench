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
typedef  scalar_t__ ttreq_t ;
typedef  int pid_t ;
typedef  int lwpid_t ;
typedef  int /*<<< orphan*/  TTRACE_ARG_TYPE ;

/* Variables and functions */
 scalar_t__ EPROTO ; 
 scalar_t__ TT_PROC_GET_FIRST_LWP_STATE ; 
 scalar_t__ debug_on ; 
 scalar_t__ errno ; 
 char* get_printable_name_of_ttrace_request (scalar_t__) ; 
 int /*<<< orphan*/  perror_with_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  reason_for_failure ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int ttrace (scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
call_real_ttrace (ttreq_t request, pid_t pid, lwpid_t tid, TTRACE_ARG_TYPE addr,
		  TTRACE_ARG_TYPE data, TTRACE_ARG_TYPE addr2)
{
  int tt_status;

  errno = 0;
  tt_status = ttrace (request, pid, tid, addr, data, addr2);

#ifdef THREAD_DEBUG
  if (errno)
    {
      /* Don't bother for a known benign error: if you ask for the
       * first thread state, but there is only one thread and it's
       * not stopped, ttrace complains.
       *
       * We have this inside the #ifdef because our caller will do
       * this check for real.
       */
      if (request != TT_PROC_GET_FIRST_LWP_STATE
	  || errno != EPROTO)
	{
	  if (debug_on)
	    printf ("TT fail for %s, with pid %d, tid %d, status %d \n",
		    get_printable_name_of_ttrace_request (request),
		    pid, tid, tt_status);
	}
    }
#endif

#if 0
  /* ??rehrauer: It would probably be most robust to catch and report
   * failed requests here.  However, some clients of this interface
   * seem to expect to catch & deal with them, so we'd best not.
   */
  if (errno)
    {
      strcpy (reason_for_failure, "ttrace (");
      strcat (reason_for_failure, get_printable_name_of_ttrace_request (request));
      strcat (reason_for_failure, ")");
      printf ("ttrace error, errno = %d\n", errno);
      perror_with_name (reason_for_failure);
    }
#endif

  return tt_status;
}