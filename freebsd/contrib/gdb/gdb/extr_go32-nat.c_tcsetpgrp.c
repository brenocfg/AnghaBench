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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  ENOTTY ; 
 scalar_t__ SOME_PID ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ isatty (int) ; 

int
tcsetpgrp (int fd, pid_t pgid)
{
  if (isatty (fd) && pgid == SOME_PID)
    return 0;
  errno = pgid == SOME_PID ? ENOTTY : ENOSYS;
  return -1;
}