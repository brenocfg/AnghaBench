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
struct console {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CON_ENABLED ; 
 int /*<<< orphan*/  acquire_console_sem () ; 
 int /*<<< orphan*/  release_console_sem () ; 

void console_start(struct console *console)
{
	acquire_console_sem();
	console->flags |= CON_ENABLED;
	release_console_sem();
}