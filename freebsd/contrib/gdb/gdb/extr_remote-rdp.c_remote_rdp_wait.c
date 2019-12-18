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
struct TYPE_3__ {int /*<<< orphan*/  sig; int /*<<< orphan*/  integer; } ;
struct target_waitstatus {TYPE_1__ value; int /*<<< orphan*/  kind; } ;
typedef  int /*<<< orphan*/  ptid_t ;
struct TYPE_4__ {int rdi_stopped_status; } ;

/* Variables and functions */
#define  RDP_RES_AT_BREAKPOINT 131 
#define  RDP_RES_RESET 130 
#define  RDP_RES_SWI 129 
 int /*<<< orphan*/  TARGET_SIGNAL_TRAP ; 
 int /*<<< orphan*/  TARGET_WAITKIND_EXITED ; 
 int /*<<< orphan*/  TARGET_WAITKIND_SIGNALLED ; 
 int /*<<< orphan*/  TARGET_WAITKIND_STOPPED ; 
 TYPE_2__ ds ; 
 int /*<<< orphan*/  inferior_ptid ; 
#define  rdp_signalled 128 
 int /*<<< orphan*/  read_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigrc ; 
 int /*<<< orphan*/  target_signal_from_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ptid_t
remote_rdp_wait (ptid_t ptid, struct target_waitstatus *status)
{
  switch (ds.rdi_stopped_status)
    {
    default:
    case RDP_RES_RESET:
    case RDP_RES_SWI:
      status->kind = TARGET_WAITKIND_EXITED;
      status->value.integer = read_register (0);
      break;
    case RDP_RES_AT_BREAKPOINT:
      status->kind = TARGET_WAITKIND_STOPPED;
      /* The signal in sigrc is a host signal.  That probably
         should be fixed.  */
      status->value.sig = TARGET_SIGNAL_TRAP;
      break;
#if 0
    case rdp_signalled:
      status->kind = TARGET_WAITKIND_SIGNALLED;
      /* The signal in sigrc is a host signal.  That probably
         should be fixed.  */
      status->value.sig = target_signal_from_host (sigrc);
      break;
#endif
    }

  return inferior_ptid;
}