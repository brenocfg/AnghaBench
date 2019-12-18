#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dirent {char* d_name; } ;
struct TYPE_5__ {scalar_t__ num_threads; char* path; int tid; } ;
typedef  TYPE_1__ procfs_status ;
typedef  TYPE_1__ procfs_info ;
typedef  TYPE_1__ procfs_debuginfo ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  DCMD_PROC_INFO ; 
 int /*<<< orphan*/  DCMD_PROC_MAPDEBUG_BASE ; 
 int /*<<< orphan*/  DCMD_PROC_TIDSTATUS ; 
 scalar_t__ EOK ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ devctl (int,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 char* nto_procfs_path ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  printf_filtered (char*,char*,scalar_t__,scalar_t__) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewinddir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  safe_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

void
procfs_pidlist (char *args, int from_tty)
{
  DIR *dp = NULL;
  struct dirent *dirp = NULL;
  int fd = -1;
  char buf[512];
  procfs_info *pidinfo = NULL;
  procfs_debuginfo *info = NULL;
  procfs_status *status = NULL;
  pid_t num_threads = 0;
  pid_t pid;
  char name[512];

  dp = opendir (nto_procfs_path);
  if (dp == NULL)
    {
      fprintf_unfiltered (gdb_stderr, "failed to opendir \"%s\" - %d (%s)",
	      nto_procfs_path, errno, safe_strerror (errno));
      return;
    }

  /* Start scan at first pid.  */
  rewinddir (dp);

  do
    {
      /* Get the right pid and procfs path for the pid.  */
      do
	{
	  dirp = readdir (dp);
	  if (dirp == NULL)
	    {
	      closedir (dp);
	      return;
	    }
	  snprintf (buf, 511, "%s/%s/as", nto_procfs_path, dirp->d_name);
	  pid = atoi (dirp->d_name);
	}
      while (pid == 0);

      /* Open the procfs path. */
      fd = open (buf, O_RDONLY);
      if (fd == -1)
	{
	  fprintf_unfiltered (gdb_stderr, "failed to open %s - %d (%s)\n",
		  buf, errno, safe_strerror (errno));
	  closedir (dp);
	  return;
	}

      pidinfo = (procfs_info *) buf;
      if (devctl (fd, DCMD_PROC_INFO, pidinfo, sizeof (buf), 0) != EOK)
	{
	  fprintf_unfiltered (gdb_stderr,
		  "devctl DCMD_PROC_INFO failed - %d (%s)\n", errno,
		  safe_strerror (errno));
	  break;
	}
      num_threads = pidinfo->num_threads;

      info = (procfs_debuginfo *) buf;
      if (devctl (fd, DCMD_PROC_MAPDEBUG_BASE, info, sizeof (buf), 0) != EOK)
	strcpy (name, "unavailable");
      else
	strcpy (name, info->path);

      /* Collect state info on all the threads.  */
      status = (procfs_status *) buf;
      for (status->tid = 1; status->tid <= num_threads; status->tid++)
	{
	  if (devctl (fd, DCMD_PROC_TIDSTATUS, status, sizeof (buf), 0) != EOK
	      && status->tid != 0)
	    break;
	  if (status->tid != 0)
	    printf_filtered ("%s - %d/%d\n", name, pid, status->tid);
	}
      close (fd);
    }
  while (dirp != NULL);

  close (fd);
  closedir (dp);
  return;
}