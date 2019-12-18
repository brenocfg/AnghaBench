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
 int /*<<< orphan*/  SIGINT ; 
 scalar_t__ attach_flag ; 
 scalar_t__ inferior_thisrun_terminal ; 
 int /*<<< orphan*/  osig ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
clear_sigint_trap (void)
{
  if (attach_flag || inferior_thisrun_terminal)
    {
      signal (SIGINT, osig);
    }
}