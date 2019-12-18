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
typedef  int /*<<< orphan*/  ttstate_t ;
typedef  int ttreq_t ;
typedef  int lwpid_t ;
typedef  int TTRACE_ARG_TYPE ;

/* Variables and functions */
 int ESRCH ; 
 int PIDGET (int /*<<< orphan*/ ) ; 
 int TT_LWP_RUREGS ; 
 int /*<<< orphan*/  TT_OK (int,int) ; 
 int TT_PROC_SETTRC ; 
 int /*<<< orphan*/  any_thread_records () ; 
 int call_real_ttrace (int,int,int,int,int,int) ; 
 scalar_t__ debug_on ; 
 int errno ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int get_pid_for (int) ; 
 char* get_printable_name_of_ttrace_request (int) ; 
 scalar_t__ is_process_ttrace_request (int) ; 
 int make_process_version (int) ; 
 int map_from_gdb_tid (int) ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saved_real_ptid ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static int
call_ttrace (ttreq_t request, int gdb_tid, TTRACE_ARG_TYPE addr,
	     TTRACE_ARG_TYPE data, TTRACE_ARG_TYPE addr2)
{
  lwpid_t real_tid;
  int real_pid;
  ttreq_t new_request;
  int tt_status;
  char reason_for_failure[100];	/* Arbitrary size, should be big enough. */

#ifdef THREAD_DEBUG
  int is_interesting = 0;

  if (TT_LWP_RUREGS == request)
    {
      is_interesting = 1;	/* Adjust code here as desired */
    }

  if (is_interesting && 0 && debug_on)
    {
      if (!is_process_ttrace_request (request))
	{
	  printf ("TT: Thread request, tid is %d", gdb_tid);
	  printf ("== SINGLE at %x", addr);
	}
      else
	{
	  printf ("TT: Process request, tid is %d\n", gdb_tid);
	  printf ("==! SINGLE at %x", addr);
	}
    }
#endif

  /* The initial SETTRC and SET_EVENT_MASK calls (and all others
   * which happen before any threads get set up) should go
   * directly to "call_real_ttrace", so they don't happen here.
   *
   * But hardware watchpoints do a SET_EVENT_MASK, so we can't
   * rule them out....
   */
#ifdef THREAD_DEBUG
  if (request == TT_PROC_SETTRC && debug_on)
    printf ("Unexpected call for TT_PROC_SETTRC\n");
#endif

  /* Sometimes we get called with a bogus tid (e.g., if a
   * thread has terminated, we return 0; inftarg later asks
   * whether the thread has exited/forked/vforked).
   */
  if (gdb_tid == 0)
    {
      errno = ESRCH;		/* ttrace's response would probably be "No such process". */
      return -1;
    }

  /* All other cases should be able to expect that there are
   * thread records.
   */
  if (!any_thread_records ())
    {
#ifdef THREAD_DEBUG
      if (debug_on)
	warning ("No thread records for ttrace call");
#endif
      errno = ESRCH;		/* ttrace's response would be "No such process". */
      return -1;
    }

  /* OK, now the task is to translate the incoming tid into
   * a pid/tid pair.
   */
  real_tid = map_from_gdb_tid (gdb_tid);
  real_pid = get_pid_for (real_tid);

  /* Now check the result.  "Real_pid" is NULL if our list
   * didn't find it.  We have some tricks we can play to fix
   * this, however.
   */
  if (0 == real_pid)
    {
      ttstate_t thread_state;

#ifdef THREAD_DEBUG
      if (debug_on)
	printf ("No saved pid for tid %d\n", gdb_tid);
#endif

      if (is_process_ttrace_request (request))
	{

	  /* Ok, we couldn't get a tid.  Try to translate to
	   * the equivalent process operation.  We expect this
	   * NOT to happen, so this is a desparation-type
	   * move.  It can happen if there is an internal
	   * error and so no "wait()" call is ever done.
	   */
	  new_request = make_process_version (request);
	  if (new_request == -1)
	    {

#ifdef THREAD_DEBUG
	      if (debug_on)
		printf ("...and couldn't make process version of thread operation\n");
#endif

	      /* Use hacky saved pid, which won't always be correct
	       * in the multi-process future.  Use tid as thread,
	       * probably dooming this to failure.  FIX!
	       */
	      if (! ptid_equal (saved_real_ptid, null_ptid))
		{
#ifdef THREAD_DEBUG
		  if (debug_on)
		    printf ("...using saved pid %d\n",
		            PIDGET (saved_real_ptid));
#endif

		  real_pid = PIDGET (saved_real_ptid);
		  real_tid = gdb_tid;
		}

	      else
		error ("Unable to perform thread operation");
	    }

	  else
	    {
	      /* Sucessfully translated this to a process request,
	       * which needs no thread value.
	       */
	      real_pid = gdb_tid;
	      real_tid = 0;
	      request = new_request;

#ifdef THREAD_DEBUG
	      if (debug_on)
		{
		  printf ("Translated thread request to process request\n");
		  if (ptid_equal (saved_real_ptid, null_ptid))
		    printf ("...but there's no saved pid\n");

		  else
		    {
		      if (gdb_tid != PIDGET (saved_real_ptid))
			printf ("...but have the wrong pid (%d rather than %d)\n",
				gdb_tid, PIDGET (saved_real_ptid));
		    }
		}
#endif
	    }			/* Translated to a process request */
	}			/* Is a process request */

      else
	{
	  /* We have to have a thread.  Ooops.
	   */
	  error ("Thread request with no threads (%s)",
		 get_printable_name_of_ttrace_request (request));
	}
    }

  /* Ttrace doesn't like to see tid values on process requests,
   * even if we have the right one.
   */
  if (is_process_ttrace_request (request))
    {
      real_tid = 0;
    }

#ifdef THREAD_DEBUG
  if (is_interesting && 0 && debug_on)
    {
      printf ("    now tid %d, pid %d\n", real_tid, real_pid);
      printf ("    request is %s\n", get_printable_name_of_ttrace_request (request));
    }
#endif

  /* Finally, the (almost) real call.
   */
  tt_status = call_real_ttrace (request, real_pid, real_tid, addr, data, addr2);

#ifdef THREAD_DEBUG
  if (is_interesting && debug_on)
    {
      if (!TT_OK (tt_status, errno)
	  && !(tt_status == 0 & errno == 0))
	printf (" got error (errno==%d, status==%d)\n", errno, tt_status);
    }
#endif

  return tt_status;
}