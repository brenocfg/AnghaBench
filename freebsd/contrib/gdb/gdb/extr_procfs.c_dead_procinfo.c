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
struct TYPE_4__ {char* pathname; int pid; } ;
typedef  TYPE_1__ procinfo ;

/* Variables and functions */
 int KILL ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  destroy_procinfo (TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_sys_errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void
dead_procinfo (procinfo *pi, char *msg, int kill_p)
{
  char procfile[80];

  if (pi->pathname)
    {
      print_sys_errmsg (pi->pathname, errno);
    }
  else
    {
      sprintf (procfile, "process %d", pi->pid);
      print_sys_errmsg (procfile, errno);
    }
  if (kill_p == KILL)
    kill (pi->pid, SIGKILL);

  destroy_procinfo (pi);
  error (msg);
}