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
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ FD_ISSET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,void (*) (int)) ; 
 scalar_t__ stub1 () ; 
 scalar_t__ target_activity_fd ; 
 scalar_t__ target_activity_function () ; 

__attribute__((used)) static void
handle_sigio (int signo)
{
  int numfds;
  fd_set readfds;

  signal (SIGIO, handle_sigio);

  FD_ZERO (&readfds);
  FD_SET (target_activity_fd, &readfds);
  numfds = select (target_activity_fd + 1, &readfds, NULL, NULL, NULL);
  if (numfds >= 0 && FD_ISSET (target_activity_fd, &readfds))
    {
#ifndef _WIN32
      if ((*target_activity_function) ())
	kill (PIDGET (inferior_ptid), SIGINT);
#endif
    }
}