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
 int /*<<< orphan*/  iterate_over_lwps (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill_callback ; 
 int /*<<< orphan*/  kill_wait_callback ; 
 int /*<<< orphan*/  target_mourn_inferior () ; 

__attribute__((used)) static void
lin_lwp_kill (void)
{
  /* Kill all LWP's ...  */
  iterate_over_lwps (kill_callback, NULL);

  /* ... and wait until we've flushed all events.  */
  iterate_over_lwps (kill_wait_callback, NULL);

  target_mourn_inferior ();
}