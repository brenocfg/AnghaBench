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
 int /*<<< orphan*/  EXIT_TROUBLE ; 
 int /*<<< orphan*/  cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int) ; 
 int signal_received ; 
 int /*<<< orphan*/  untrapsig (int) ; 

__attribute__((used)) static void
checksigs (void)
{
  int s = signal_received;
  if (s)
    {
      cleanup (0);

      /* Yield an exit status indicating that a signal was received.  */
      untrapsig (s);
      kill (getpid (), s);

      /* That didn't work, so exit with error status.  */
      exit (EXIT_TROUBLE);
    }
}