#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cleanup {int dummy; } ;

/* Variables and functions */
 scalar_t__ MON_IDT ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mips_exit_cleanups ; 
 int mips_exiting ; 
 int /*<<< orphan*/  mips_expect (char*) ; 
 scalar_t__ mips_monitor ; 
 char* mips_monitor_prompt ; 
 scalar_t__ mips_need_reply ; 
 int /*<<< orphan*/  mips_receive_wait ; 
 int /*<<< orphan*/  mips_request (char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mips_exit_debug (void)
{
  int err;
  struct cleanup *old_cleanups = make_cleanup (mips_exit_cleanups, NULL);

  mips_exiting = 1;

  if (mips_monitor != MON_IDT)
    {
      /* The DDB (NEC) and MiniRISC (LSI) versions of PMON exit immediately,
         so we do not get a reply to this command: */
      mips_request ('x', 0, 0, NULL, mips_receive_wait, NULL);
      mips_need_reply = 0;
      if (!mips_expect (" break!"))
	return -1;
    }
  else
    mips_request ('x', 0, 0, &err, mips_receive_wait, NULL);

  if (!mips_expect (mips_monitor_prompt))
    return -1;

  do_cleanups (old_cleanups);

  return 0;
}