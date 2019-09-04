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

__attribute__((used)) static void main_checkfds(void)
{
#ifdef HAVE_PIPE
  int fd[2] = { STDIN_FILENO, STDIN_FILENO };
  while(fd[0] == STDIN_FILENO ||
        fd[0] == STDOUT_FILENO ||
        fd[0] == STDERR_FILENO ||
        fd[1] == STDIN_FILENO ||
        fd[1] == STDOUT_FILENO ||
        fd[1] == STDERR_FILENO)
    if(pipe(fd) < 0)
      return;   /* Out of handles. This isn't really a big problem now, but
                   will be when we try to create a socket later. */
  close(fd[0]);
  close(fd[1]);
#endif
}