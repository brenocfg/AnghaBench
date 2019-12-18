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
struct TYPE_2__ {int /*<<< orphan*/  sig; } ;
struct target_waitstatus {TYPE_1__ value; int /*<<< orphan*/  kind; } ;
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int /*<<< orphan*/  TARGET_SIGNAL_INT ; 
 int /*<<< orphan*/  TARGET_SIGNAL_TRAP ; 
 int /*<<< orphan*/  TARGET_WAITKIND_STOPPED ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  inferior_ptid ; 
 unsigned long ocd_read_bdm_register (int) ; 
 int ocd_wait () ; 

__attribute__((used)) static ptid_t
bdm_ppc_wait (ptid_t ptid, struct target_waitstatus *target_status)
{
  int stop_reason;

  target_status->kind = TARGET_WAITKIND_STOPPED;

  stop_reason = ocd_wait ();

  if (stop_reason)
    {
      target_status->value.sig = TARGET_SIGNAL_INT;
      return inferior_ptid;
    }

  target_status->value.sig = TARGET_SIGNAL_TRAP;	/* XXX for now */

#if 0
  {
    unsigned long ecr, der;

    ecr = ocd_read_bdm_register (148);	/* Read the exception cause register */
    der = ocd_read_bdm_register (149);	/* Read the debug enables register */
    fprintf_unfiltered (gdb_stdout, "ecr = 0x%x, der = 0x%x\n", ecr, der);
  }
#endif

  return inferior_ptid;
}