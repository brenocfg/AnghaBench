#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  badvaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_gdbarch ; 
 TYPE_1__* mips_regnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_expect (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_expect_prompt (char*,int) ; 
 int /*<<< orphan*/  monitor_printf (char*) ; 
 int /*<<< orphan*/  monitor_supply_register (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
fetch_bad_vaddr (void)
{
  char buf[20];

  monitor_printf ("xB\r");
  monitor_expect ("BadV=", NULL, 0);
  monitor_expect_prompt (buf, sizeof (buf));
  monitor_supply_register (mips_regnum (current_gdbarch)->badvaddr, buf);
}