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
struct TYPE_2__ {char* name; int /*<<< orphan*/  tst; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_simple_test () ; 
 int /*<<< orphan*/  kgdb_breakpoint () ; 
 int /*<<< orphan*/  sys_open_test ; 
 TYPE_1__ ts ; 

__attribute__((used)) static void run_sys_open_test(void)
{
	init_simple_test();
	ts.tst = sys_open_test;
	ts.name = "sys_open_test";
	/* Activate test with initial breakpoint */
	kgdb_breakpoint();
}