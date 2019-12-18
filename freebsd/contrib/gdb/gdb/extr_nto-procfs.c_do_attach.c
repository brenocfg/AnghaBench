#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * sival_ptr; } ;
struct sigevent {int sigev_priority; int flags; TYPE_1__ sigev_value; scalar_t__ sigev_code; int /*<<< orphan*/  sigev_signo; int /*<<< orphan*/  sigev_notify; } ;
typedef  int /*<<< orphan*/  status ;
typedef  int /*<<< orphan*/  ptid_t ;
typedef  struct sigevent procfs_status ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int /*<<< orphan*/  DCMD_PROC_EVENT ; 
 int /*<<< orphan*/  DCMD_PROC_STATUS ; 
 int /*<<< orphan*/  DCMD_PROC_STOP ; 
 scalar_t__ EOK ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PATH_MAX ; 
 int PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  SIGEV_SIGNAL_THREAD ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SignalKill (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _DEBUG_FLAG_STOPPED ; 
 int attach_flag ; 
 int ctl_fd ; 
 scalar_t__ devctl (int,int /*<<< orphan*/ ,struct sigevent*,int,int /*<<< orphan*/ ) ; 
 char* errno ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  nto_init_solib_absolute_prefix () ; 
 int /*<<< orphan*/  nto_node () ; 
 char* nto_procfs_path ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_strerror (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 

__attribute__((used)) static ptid_t
do_attach (ptid_t ptid)
{
  procfs_status status;
  struct sigevent event;
  char path[PATH_MAX];

  snprintf (path, PATH_MAX - 1, "%s/%d/as", nto_procfs_path, PIDGET (ptid));
  ctl_fd = open (path, O_RDWR);
  if (ctl_fd == -1)
    error ("Couldn't open proc file %s, error %d (%s)", path, errno,
	   safe_strerror (errno));
  if (devctl (ctl_fd, DCMD_PROC_STOP, &status, sizeof (status), 0) != EOK)
    error ("Couldn't stop process");

  /* Define a sigevent for process stopped notification.  */
  event.sigev_notify = SIGEV_SIGNAL_THREAD;
  event.sigev_signo = SIGUSR1;
  event.sigev_code = 0;
  event.sigev_value.sival_ptr = NULL;
  event.sigev_priority = -1;
  devctl (ctl_fd, DCMD_PROC_EVENT, &event, sizeof (event), 0);

  if (devctl (ctl_fd, DCMD_PROC_STATUS, &status, sizeof (status), 0) == EOK
      && status.flags & _DEBUG_FLAG_STOPPED)
    SignalKill (nto_node(), PIDGET (ptid), 0, SIGCONT, 0, 0);
  attach_flag = 1;
  nto_init_solib_absolute_prefix ();
  return ptid;
}