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
typedef  int pid_t ;
typedef  int lwpid_t ;
typedef  int /*<<< orphan*/  TTRACE_ARG_TYPE ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ EPROTO ; 
 int /*<<< orphan*/  TT_LWP_WUREGS ; 
 scalar_t__ TT_PROC_GET_FIRST_LWP_STATE ; 
 scalar_t__ debug_on ; 
 scalar_t__ errno ; 
 int get_pid_for (int) ; 
 char* get_printable_name_of_ttrace_request (int /*<<< orphan*/ ) ; 
 int map_from_gdb_tid (int) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int) ; 
 scalar_t__ request ; 
 int ttrace (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
ttrace_write_reg_64 (int gdb_tid, CORE_ADDR dest_addr, CORE_ADDR src_addr)
{
  pid_t 	pid;
  lwpid_t 	tid;
  int  		tt_status;

  tid = map_from_gdb_tid (gdb_tid);
  pid = get_pid_for (tid);

  errno = 0;
  tt_status = ttrace (TT_LWP_WUREGS, 
		      pid, 
		      tid, 
		      (TTRACE_ARG_TYPE) dest_addr, 
		      8, 
		      (TTRACE_ARG_TYPE) src_addr );

#ifdef THREAD_DEBUG
  if (errno)
    {
      /* Don't bother for a known benign error: if you ask for the
         first thread state, but there is only one thread and it's
         not stopped, ttrace complains.
        
         We have this inside the #ifdef because our caller will do
         this check for real.  */
      if( request != TT_PROC_GET_FIRST_LWP_STATE
          ||  errno   != EPROTO )
        {
          if( debug_on )
            printf( "TT fail for %s, with pid %d, tid %d, status %d \n",
                    get_printable_name_of_ttrace_request (TT_LWP_WUREGS),
                    pid, tid, tt_status );
        }
    }
#endif

  return tt_status;
}