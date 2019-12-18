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
struct TYPE_5__ {scalar_t__ ctl_fd; scalar_t__ gregs_valid; } ;
typedef  TYPE_1__ procinfo ;
typedef  int /*<<< orphan*/  procfs_ctl_t ;
typedef  int /*<<< orphan*/  gdb_gregset_t ;
typedef  int /*<<< orphan*/  arg ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CTL ; 
 int /*<<< orphan*/  PCSREG ; 
 int /*<<< orphan*/  PIOCSREG ; 
 scalar_t__ ioctl (scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (char**,char*,int) ; 
 scalar_t__ open_procinfo_files (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * proc_get_gregs (TYPE_1__*) ; 
 int write (scalar_t__,void*,int) ; 

int
proc_set_gregs (procinfo *pi)
{
  gdb_gregset_t *gregs;
  int win;

  if ((gregs = proc_get_gregs (pi)) == NULL)
    return 0;	/* get_regs has already warned */

  if (pi->ctl_fd == 0 &&
      open_procinfo_files (pi, FD_CTL) == 0)
    {
      return 0;
    }
  else
    {
#ifdef NEW_PROC_API
      struct {
	procfs_ctl_t cmd;
	/* Use char array to avoid alignment issues.  */
	char gregs[sizeof (gdb_gregset_t)];
      } arg;

      arg.cmd   = PCSREG;
      memcpy (&arg.gregs, gregs, sizeof (arg.gregs));
      win = (write (pi->ctl_fd, (void *) &arg, sizeof (arg)) == sizeof (arg));
#else
      win = (ioctl (pi->ctl_fd, PIOCSREG, gregs) >= 0);
#endif
    }

  /* Policy: writing the regs invalidates our cache. */
  pi->gregs_valid = 0;
  return win;
}