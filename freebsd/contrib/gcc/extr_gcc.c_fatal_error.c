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

/* Variables and functions */
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  delete_failure_queue () ; 
 int /*<<< orphan*/  delete_temp_files () ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fatal_error (int signum)
{
  signal (signum, SIG_DFL);
  delete_failure_queue ();
  delete_temp_files ();
  /* Get the same signal again, this time not handled,
     so its normal effect occurs.  */
  kill (getpid (), signum);
}