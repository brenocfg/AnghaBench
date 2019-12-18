#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* pathname; int tid; int ctl_fd; int as_fd; int status_fd; int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__ procinfo ;

/* Variables and functions */
#define  FD_AS 130 
#define  FD_CTL 129 
#define  FD_STATUS 128 
 int MAX_PROC_NAME_SIZE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  PIOCOPENLWP ; 
 TYPE_1__* find_procinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int open_with_retry (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int
open_procinfo_files (procinfo *pi, int which)
{
#ifdef NEW_PROC_API
  char tmp[MAX_PROC_NAME_SIZE];
#endif
  int  fd;

  /*
   * This function is getting ALMOST long enough to break up into several.
   * Here is some rationale:
   *
   * NEW_PROC_API (Solaris 2.6, Solaris 2.7, Unixware):
   *   There are several file descriptors that may need to be open
   *   for any given process or LWP.  The ones we're intereted in are:
   *     - control	 (ctl)	  write-only	change the state
   *     - status	 (status) read-only	query the state
   *     - address space (as)     read/write	access memory
   *     - map           (map)    read-only     virtual addr map
   *   Most of these are opened lazily as they are needed.
   *   The pathnames for the 'files' for an LWP look slightly
   *   different from those of a first-class process:
   *     Pathnames for a process (<proc-id>):
   *       /proc/<proc-id>/ctl
   *       /proc/<proc-id>/status
   *       /proc/<proc-id>/as
   *       /proc/<proc-id>/map
   *     Pathnames for an LWP (lwp-id):
   *       /proc/<proc-id>/lwp/<lwp-id>/lwpctl
   *       /proc/<proc-id>/lwp/<lwp-id>/lwpstatus
   *   An LWP has no map or address space file descriptor, since
   *   the memory map and address space are shared by all LWPs.
   *
   * Everyone else (Solaris 2.5, Irix, OSF)
   *   There is only one file descriptor for each process or LWP.
   *   For convenience, we copy the same file descriptor into all
   *   three fields of the procinfo struct (ctl_fd, status_fd, and
   *   as_fd, see NEW_PROC_API above) so that code that uses them
   *   doesn't need any #ifdef's.
   *     Pathname for all:
   *       /proc/<proc-id>
   *
   *   Solaris 2.5 LWP's:
   *     Each LWP has an independent file descriptor, but these
   *     are not obtained via the 'open' system call like the rest:
   *     instead, they're obtained thru an ioctl call (PIOCOPENLWP)
   *     to the file descriptor of the parent process.
   *
   *   OSF threads:
   *     These do not even have their own independent file descriptor.
   *     All operations are carried out on the file descriptor of the
   *     parent process.  Therefore we just call open again for each
   *     thread, getting a new handle for the same 'file'.
   */

#ifdef NEW_PROC_API
  /*
   * In this case, there are several different file descriptors that
   * we might be asked to open.  The control file descriptor will be
   * opened early, but the others will be opened lazily as they are
   * needed.
   */

  strcpy (tmp, pi->pathname);
  switch (which) {	/* which file descriptor to open? */
  case FD_CTL:
    if (pi->tid)
      strcat (tmp, "/lwpctl");
    else
      strcat (tmp, "/ctl");
    fd = open_with_retry (tmp, O_WRONLY);
    if (fd <= 0)
      return 0;		/* fail */
    pi->ctl_fd = fd;
    break;
  case FD_AS:
    if (pi->tid)
      return 0;		/* there is no 'as' file descriptor for an lwp */
    strcat (tmp, "/as");
    fd = open_with_retry (tmp, O_RDWR);
    if (fd <= 0)
      return 0;		/* fail */
    pi->as_fd = fd;
    break;
  case FD_STATUS:
    if (pi->tid)
      strcat (tmp, "/lwpstatus");
    else
      strcat (tmp, "/status");
    fd = open_with_retry (tmp, O_RDONLY);
    if (fd <= 0)
      return 0;		/* fail */
    pi->status_fd = fd;
    break;
  default:
    return 0;		/* unknown file descriptor */
  }
#else  /* not NEW_PROC_API */
  /*
   * In this case, there is only one file descriptor for each procinfo
   * (ie. each process or LWP).  In fact, only the file descriptor for
   * the process can actually be opened by an 'open' system call.
   * The ones for the LWPs have to be obtained thru an IOCTL call
   * on the process's file descriptor.
   *
   * For convenience, we copy each procinfo's single file descriptor
   * into all of the fields occupied by the several file descriptors
   * of the NEW_PROC_API implementation.  That way, the code that uses
   * them can be written without ifdefs.
   */


#ifdef PIOCTSTATUS	/* OSF */
  /* Only one FD; just open it. */
  if ((fd = open_with_retry (pi->pathname, O_RDWR)) == 0)
    return 0;
#else			/* Sol 2.5, Irix, other? */
  if (pi->tid == 0)	/* Master procinfo for the process */
    {
      fd = open_with_retry (pi->pathname, O_RDWR);
      if (fd <= 0)
	return 0;	/* fail */
    }
  else			/* LWP thread procinfo */
    {
#ifdef PIOCOPENLWP	/* Sol 2.5, thread/LWP */
      procinfo *process;
      int lwpid = pi->tid;

      /* Find the procinfo for the entire process. */
      if ((process = find_procinfo (pi->pid, 0)) == NULL)
	return 0;	/* fail */

      /* Now obtain the file descriptor for the LWP. */
      if ((fd = ioctl (process->ctl_fd, PIOCOPENLWP, &lwpid)) <= 0)
	return 0;	/* fail */
#else			/* Irix, other? */
      return 0;		/* Don't know how to open threads */
#endif	/* Sol 2.5 PIOCOPENLWP */
    }
#endif	/* OSF     PIOCTSTATUS */
  pi->ctl_fd = pi->as_fd = pi->status_fd = fd;
#endif	/* NEW_PROC_API */

  return 1;		/* success */
}