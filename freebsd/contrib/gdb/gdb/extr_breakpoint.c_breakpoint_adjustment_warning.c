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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  local_hex_string_custom (unsigned long,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,...) ; 

__attribute__((used)) static void
breakpoint_adjustment_warning (CORE_ADDR from_addr, CORE_ADDR to_addr,
                               int bnum, int have_bnum)
{
  char astr1[40];
  char astr2[40];

  strcpy (astr1, local_hex_string_custom ((unsigned long) from_addr, "08l"));
  strcpy (astr2, local_hex_string_custom ((unsigned long) to_addr, "08l"));
  if (have_bnum)
    warning ("Breakpoint %d address previously adjusted from %s to %s.",
             bnum, astr1, astr2);
  else
    warning ("Breakpoint address adjusted from %s to %s.", astr1, astr2);
}