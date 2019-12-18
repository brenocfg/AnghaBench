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
 int /*<<< orphan*/  gc_reset_vt100 () ; 
 scalar_t__ gc_x ; 
 scalar_t__ gc_y ; 

__attribute__((used)) static void
gc_reset_screen(void)
{
	gc_reset_vt100();
	gc_x = gc_y = 0;
}