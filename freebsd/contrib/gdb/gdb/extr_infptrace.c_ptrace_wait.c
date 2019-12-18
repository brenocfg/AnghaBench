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
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  target_post_wait (int /*<<< orphan*/ ,int) ; 
 int wait (int*) ; 

int
ptrace_wait (ptid_t ptid, int *status)
{
  int wstate;

  wstate = wait (status);
  target_post_wait (pid_to_ptid (wstate), *status);
  return wstate;
}