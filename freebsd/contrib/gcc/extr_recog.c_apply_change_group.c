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
 int /*<<< orphan*/  cancel_changes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  confirm_change_group () ; 
 scalar_t__ verify_changes (int /*<<< orphan*/ ) ; 

int
apply_change_group (void)
{
  if (verify_changes (0))
    {
      confirm_change_group ();
      return 1;
    }
  else
    {
      cancel_changes (0);
      return 0;
    }
}