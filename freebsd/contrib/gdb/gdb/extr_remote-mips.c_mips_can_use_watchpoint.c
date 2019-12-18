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
 int MAX_LSI_BREAKPOINTS ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  target_shortname ; 

int
mips_can_use_watchpoint (int type, int cnt, int othertype)
{
  return cnt < MAX_LSI_BREAKPOINTS && strcmp (target_shortname, "lsi") == 0;
}