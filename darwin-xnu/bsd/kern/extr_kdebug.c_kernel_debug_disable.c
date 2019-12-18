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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  kdbg_set_tracing_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kdebug_enable ; 

void
kernel_debug_disable(void)
{
	if (kdebug_enable) {
		kdbg_set_tracing_enabled(FALSE, 0);
	}
}