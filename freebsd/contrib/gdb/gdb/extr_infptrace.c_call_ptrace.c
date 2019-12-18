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
typedef  int PTRACE_ARG3_TYPE ;

/* Variables and functions */
 int PT_CONTIN1 ; 
 int PT_CONTINUE ; 
 int PT_SETTRC ; 
 int PT_SINGLE1 ; 
 int PT_STEP ; 
 int errno ; 
 int parent_attach_all (int,int,int) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int ptrace (int,int,int,int,...) ; 

int
call_ptrace (int request, int pid, PTRACE_ARG3_TYPE addr, int data)
{
  int pt_status = 0;

#if 0
  int saved_errno;

  printf ("call_ptrace(request=%d, pid=%d, addr=0x%x, data=0x%x)",
	  request, pid, addr, data);
#endif
#if defined(PT_SETTRC)
  /* If the parent can be told to attach to us, try to do it.  */
  if (request == PT_SETTRC)
    {
      errno = 0;
#if !defined (FIVE_ARG_PTRACE)
      pt_status = ptrace (PT_SETTRC, pid, addr, data);
#else
      /* Deal with HPUX 8.0 braindamage.  We never use the
         calls which require the fifth argument.  */
      pt_status = ptrace (PT_SETTRC, pid, addr, data, 0);
#endif
      if (errno)
	perror_with_name ("ptrace");
#if 0
      printf (" = %d\n", pt_status);
#endif
      if (pt_status < 0)
	return pt_status;
      else
	return parent_attach_all (pid, addr, data);
    }
#endif

#if defined(PT_CONTIN1)
  /* On HPUX, PT_CONTIN1 is a form of continue that preserves pending
     signals.  If it's available, use it.  */
  if (request == PT_CONTINUE)
    request = PT_CONTIN1;
#endif

#if defined(PT_SINGLE1)
  /* On HPUX, PT_SINGLE1 is a form of step that preserves pending
     signals.  If it's available, use it.  */
  if (request == PT_STEP)
    request = PT_SINGLE1;
#endif

#if 0
  saved_errno = errno;
  errno = 0;
#endif
#if !defined (FIVE_ARG_PTRACE)
  pt_status = ptrace (request, pid, addr, data);
#else
  /* Deal with HPUX 8.0 braindamage.  We never use the
     calls which require the fifth argument.  */
  pt_status = ptrace (request, pid, addr, data, 0);
#endif

#if 0
  if (errno)
    printf (" [errno = %d]", errno);

  errno = saved_errno;
  printf (" = 0x%x\n", pt_status);
#endif
  return pt_status;
}