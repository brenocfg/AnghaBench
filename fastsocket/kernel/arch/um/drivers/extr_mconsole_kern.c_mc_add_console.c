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
 int /*<<< orphan*/  mc_console ; 
 int /*<<< orphan*/  register_console (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mc_add_console(void)
{
	register_console(&mc_console);
	return 0;
}