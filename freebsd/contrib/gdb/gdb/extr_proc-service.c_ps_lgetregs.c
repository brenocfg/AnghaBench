#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  ps_err_e ;
typedef  scalar_t__ prgregset_t ;
typedef  int /*<<< orphan*/  lwpid_t ;
typedef  TYPE_1__* gdb_ps_prochandle_t ;
typedef  int /*<<< orphan*/  gdb_gregset_t ;
struct TYPE_3__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_LWP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PS_OK ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  fill_gregset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 struct cleanup* save_inferior_ptid () ; 
 int /*<<< orphan*/  target_fetch_registers (int) ; 

ps_err_e
ps_lgetregs (gdb_ps_prochandle_t ph, lwpid_t lwpid, prgregset_t gregset)
{
  struct cleanup *old_chain = save_inferior_ptid ();

  inferior_ptid = BUILD_LWP (lwpid, ph->pid);

  target_fetch_registers (-1);
  fill_gregset ((gdb_gregset_t *) gregset, -1);

  do_cleanups (old_chain);
  return PS_OK;
}