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
struct TYPE_4__ {TYPE_1__* descr; } ;
struct TYPE_3__ {int nr_raw_registers; } ;

/* Variables and functions */
 int /*<<< orphan*/  alloca (int /*<<< orphan*/ ) ; 
 TYPE_2__* current_regcache ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  registers_changed_hook () ; 
 int /*<<< orphan*/  registers_ptid ; 
 int /*<<< orphan*/  set_register_cached (int,int /*<<< orphan*/ ) ; 

void
registers_changed (void)
{
  int i;

  registers_ptid = pid_to_ptid (-1);

  /* Force cleanup of any alloca areas if using C alloca instead of
     a builtin alloca.  This particular call is used to clean up
     areas allocated by low level target code which may build up
     during lengthy interactions between gdb and the target before
     gdb gives control to the user (ie watchpoints).  */
  alloca (0);

  for (i = 0; i < current_regcache->descr->nr_raw_registers; i++)
    set_register_cached (i, 0);

  if (registers_changed_hook)
    registers_changed_hook ();
}