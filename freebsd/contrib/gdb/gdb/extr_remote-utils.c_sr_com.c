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
 int /*<<< orphan*/  gr_expect_prompt () ; 
 int /*<<< orphan*/  registers_changed () ; 
 int /*<<< orphan*/  sr_check_open () ; 
 int /*<<< orphan*/  sr_write (char*,int) ; 
 int /*<<< orphan*/  sr_write_cr (char*) ; 

__attribute__((used)) static void
sr_com (char *args, int fromtty)
{
  sr_check_open ();

  if (!args)
    return;

  /* Clear all input so only command relative output is displayed */

  sr_write_cr (args);
  sr_write ("\030", 1);
  registers_changed ();
  gr_expect_prompt ();
}