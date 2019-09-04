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
 int /*<<< orphan*/  paniclog_append_noflush (char*) ; 

__attribute__((noreturn))
void
panic_spin_forever()
{
	paniclog_append_noflush("\nPlease go to https://panic.apple.com to report this panic\n");

	for (;;) { }
}