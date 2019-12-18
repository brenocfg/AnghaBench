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
struct TYPE_4__ {scalar_t__ pid; scalar_t__ status_valid; int /*<<< orphan*/  ctl_fd; } ;
typedef  TYPE_1__ procinfo ;
typedef  long procfs_ctl_t ;
typedef  int /*<<< orphan*/  arg ;

/* Variables and functions */
 long FLAG_RESET ; 
 long FLAG_SET ; 
 long GDBRESET ; 
 long PCSET ; 
 int /*<<< orphan*/  PIOCRESET ; 
 int /*<<< orphan*/  PIOCRFORK ; 
 int /*<<< orphan*/  PIOCRRLC ; 
 int /*<<< orphan*/  PIOCSET ; 
 int /*<<< orphan*/  PIOCSFORK ; 
 int /*<<< orphan*/  PIOCSRLC ; 
 long PR_ASYNC ; 
#define  PR_FORK 129 
 long PR_KLC ; 
#define  PR_RLC 128 
 TYPE_1__* find_procinfo_or_die (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  warning (char*,char*,char*) ; 
 int write (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int
proc_modify_flag (procinfo *pi, long flag, long mode)
{
  long win = 0;		/* default to fail */

  /*
   * These operations affect the process as a whole, and applying
   * them to an individual LWP has the same meaning as applying them
   * to the main process.  Therefore, if we're ever called with a
   * pointer to an LWP's procinfo, let's substitute the process's
   * procinfo and avoid opening the LWP's file descriptor
   * unnecessarily.
   */

  if (pi->pid != 0)
    pi = find_procinfo_or_die (pi->pid, 0);

#ifdef NEW_PROC_API	/* Newest method: UnixWare and newer Solarii */
  /* First normalize the PCUNSET/PCRESET command opcode
     (which for no obvious reason has a different definition
     from one operating system to the next...)  */
#ifdef  PCUNSET
#define GDBRESET PCUNSET
#else
#ifdef  PCRESET
#define GDBRESET PCRESET
#endif
#endif
  {
    procfs_ctl_t arg[2];

    if (mode == FLAG_SET)	/* Set the flag (RLC, FORK, or ASYNC) */
      arg[0] = PCSET;
    else			/* Reset the flag */
      arg[0] = GDBRESET;

    arg[1] = flag;
    win = (write (pi->ctl_fd, (void *) &arg, sizeof (arg)) == sizeof (arg));
  }
#else
#ifdef PIOCSET		/* Irix/Sol5 method */
  if (mode == FLAG_SET)	/* Set the flag (hopefully RLC, FORK, or ASYNC) */
    {
      win = (ioctl (pi->ctl_fd, PIOCSET, &flag)   >= 0);
    }
  else			/* Reset the flag */
    {
      win = (ioctl (pi->ctl_fd, PIOCRESET, &flag) >= 0);
    }

#else
#ifdef PIOCSRLC		/* Oldest method: OSF */
  switch (flag) {
  case PR_RLC:
    if (mode == FLAG_SET)	/* Set run-on-last-close */
      {
	win = (ioctl (pi->ctl_fd, PIOCSRLC, NULL) >= 0);
      }
    else			/* Clear run-on-last-close */
      {
	win = (ioctl (pi->ctl_fd, PIOCRRLC, NULL) >= 0);
      }
    break;
  case PR_FORK:
    if (mode == FLAG_SET)	/* Set inherit-on-fork */
      {
	win = (ioctl (pi->ctl_fd, PIOCSFORK, NULL) >= 0);
      }
    else			/* Clear inherit-on-fork */
      {
	win = (ioctl (pi->ctl_fd, PIOCRFORK, NULL) >= 0);
      }
    break;
  default:
    win = 0;		/* fail -- unknown flag (can't do PR_ASYNC) */
    break;
  }
#endif
#endif
#endif
#undef GDBRESET
  /* The above operation renders the procinfo's cached pstatus obsolete. */
  pi->status_valid = 0;

  if (!win)
    warning ("procfs: modify_flag failed to turn %s %s",
	     flag == PR_FORK  ? "PR_FORK"  :
	     flag == PR_RLC   ? "PR_RLC"   :
#ifdef PR_ASYNC
	     flag == PR_ASYNC ? "PR_ASYNC" :
#endif
#ifdef PR_KLC
	     flag == PR_KLC   ? "PR_KLC"   :
#endif
	     "<unknown flag>",
	     mode == FLAG_RESET ? "off" : "on");

  return win;
}