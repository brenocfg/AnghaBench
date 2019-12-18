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
typedef  int /*<<< orphan*/  ptid_t ;
typedef  int pid_t ;
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int ULONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  I386_EFLAGS_REGNUM ; 
 int PT_CONTINUE ; 
 int PT_STEP ; 
 int /*<<< orphan*/  current_regcache ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int ptid_get_pid (int /*<<< orphan*/ ) ; 
 int ptrace (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_cooked_read_unsigned (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regcache_cooked_write_unsigned (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  target_signal_to_host (int) ; 

void
child_resume (ptid_t ptid, int step, enum target_signal signal)
{
  pid_t pid = ptid_get_pid (ptid);
  int request = PT_STEP;

  if (pid == -1)
    /* Resume all threads.  This only gets used in the non-threaded
       case, where "resume all threads" and "resume inferior_ptid" are
       the same.  */
    pid = ptid_get_pid (inferior_ptid);

  if (!step)
    {
      ULONGEST eflags;

      /* Workaround for a bug in FreeBSD.  Make sure that the trace
 	 flag is off when doing a continue.  There is a code path
 	 through the kernel which leaves the flag set when it should
 	 have been cleared.  If a process has a signal pending (such
 	 as SIGALRM) and we do a PT_STEP, the process never really has
 	 a chance to run because the kernel needs to notify the
 	 debugger that a signal is being sent.  Therefore, the process
 	 never goes through the kernel's trap() function which would
 	 normally clear it.  */

      regcache_cooked_read_unsigned (current_regcache, I386_EFLAGS_REGNUM,
				     &eflags);
      if (eflags & 0x0100)
	regcache_cooked_write_unsigned (current_regcache, I386_EFLAGS_REGNUM,
					eflags & ~0x0100);

      request = PT_CONTINUE;
    }

  /* An addres of (caddr_t) 1 tells ptrace to continue from where it
     was.  (If GDB wanted it to start some other way, we have already
     written a new PC value to the child.)  */
  if (ptrace (request, pid, (caddr_t) 1,
	      target_signal_to_host (signal)) == -1)
    perror_with_name ("ptrace");
}