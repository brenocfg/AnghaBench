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
 scalar_t__ kill_kludge ; 
 int /*<<< orphan*/  target_mourn_inferior () ; 

void
ocd_kill (void)
{
  /* For some mysterious reason, wait_for_inferior calls kill instead of
     mourn after it gets TARGET_WAITKIND_SIGNALLED.  Work around it.  */
  if (kill_kludge)
    {
      kill_kludge = 0;
      target_mourn_inferior ();
      return;
    }

  /* Don't wait for it to die.  I'm not really sure it matters whether
     we do or not.  */
  target_mourn_inferior ();
}