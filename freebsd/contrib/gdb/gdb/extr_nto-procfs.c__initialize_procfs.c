#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  trace; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 TYPE_2__* SYSPAGE_ENTRY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_info (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpuinfo ; 
 int /*<<< orphan*/  init_procfs_ops () ; 
 int /*<<< orphan*/  notice_signals () ; 
 int /*<<< orphan*/  nto_cpuinfo_flags ; 
 int nto_cpuinfo_valid ; 
 int /*<<< orphan*/  procfs_meminfo ; 
 int /*<<< orphan*/  procfs_ops ; 
 int /*<<< orphan*/  procfs_pidlist ; 
 TYPE_1__ run ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
_initialize_procfs (void)
{
  sigset_t set;

  init_procfs_ops ();
  add_target (&procfs_ops);

  /* We use SIGUSR1 to gain control after we block waiting for a process.
     We use sigwaitevent to wait.  */
  sigemptyset (&set);
  sigaddset (&set, SIGUSR1);
  sigprocmask (SIG_BLOCK, &set, NULL);

  /* Set up trace and fault sets, as gdb expects them.  */
  sigemptyset (&run.trace);
  notice_signals ();

  /* Stuff some information.  */
  nto_cpuinfo_flags = SYSPAGE_ENTRY (cpuinfo)->flags;
  nto_cpuinfo_valid = 1;

  add_info ("pidlist", procfs_pidlist, "pidlist");
  add_info ("meminfo", procfs_meminfo, "memory information");
}