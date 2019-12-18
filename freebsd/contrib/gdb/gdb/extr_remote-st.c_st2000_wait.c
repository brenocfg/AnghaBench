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
struct TYPE_2__ {int /*<<< orphan*/  sig; scalar_t__ integer; } ;
struct target_waitstatus {TYPE_1__ value; int /*<<< orphan*/  kind; } ;
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int /*<<< orphan*/  TARGET_SIGNAL_TRAP ; 
 int /*<<< orphan*/  TARGET_WAITKIND_EXITED ; 
 int /*<<< orphan*/  TARGET_WAITKIND_STOPPED ; 
 int /*<<< orphan*/  expect_prompt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int timeout ; 

__attribute__((used)) static ptid_t
st2000_wait (ptid_t ptid, struct target_waitstatus *status)
{
  int old_timeout = timeout;

  status->kind = TARGET_WAITKIND_EXITED;
  status->value.integer = 0;

  timeout = 0;			/* Don't time out -- user program is running. */

  expect_prompt (0);		/* Wait for prompt, outputting extraneous text */

  status->kind = TARGET_WAITKIND_STOPPED;
  status->value.sig = TARGET_SIGNAL_TRAP;

  timeout = old_timeout;

  return inferior_ptid;
}