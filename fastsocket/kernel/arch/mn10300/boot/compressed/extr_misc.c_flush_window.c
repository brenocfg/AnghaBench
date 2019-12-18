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
 int /*<<< orphan*/  flush_window_high () ; 
 int /*<<< orphan*/  flush_window_low () ; 
 scalar_t__ high_loaded ; 

__attribute__((used)) static void flush_window(void)
{
	if (high_loaded)
		flush_window_high();
	else
		flush_window_low();
}