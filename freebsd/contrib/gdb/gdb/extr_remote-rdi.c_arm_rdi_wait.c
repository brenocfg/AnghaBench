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
 scalar_t__ RDIError_NoError ; 
 int /*<<< orphan*/  TARGET_WAITKIND_EXITED ; 
 int /*<<< orphan*/  TARGET_WAITKIND_STOPPED ; 
 scalar_t__ execute_status ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  rdi_error_signal (scalar_t__) ; 

__attribute__((used)) static ptid_t
arm_rdi_wait (ptid_t ptid, struct target_waitstatus *status)
{
  status->kind = (execute_status == RDIError_NoError ?
		  TARGET_WAITKIND_EXITED : TARGET_WAITKIND_STOPPED);

  /* convert stopped code from target into right signal */
  status->value.sig = rdi_error_signal (execute_status);

  return inferior_ptid;
}