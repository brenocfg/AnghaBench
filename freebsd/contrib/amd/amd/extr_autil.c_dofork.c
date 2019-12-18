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
 int /*<<< orphan*/  NumChildren ; 
 int /*<<< orphan*/  am_set_mypid () ; 
 scalar_t__ foreground ; 
 int fork () ; 
 int /*<<< orphan*/  sleep (int) ; 

__attribute__((used)) static int
dofork(void)
{
  int pid;

top:
  pid = fork();

  if (pid < 0) {		/* fork error, retry in 1 second */
    sleep(1);
    goto top;
  }
  if (pid == 0) {		/* child process (foreground==false) */
    am_set_mypid();
    foreground = 0;
  } else {			/* parent process, has one more child */
    NumChildren++;
  }

  return pid;
}