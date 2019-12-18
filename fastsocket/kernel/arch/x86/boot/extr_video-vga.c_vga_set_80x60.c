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
 int /*<<< orphan*/  vga_set_480_scanlines () ; 
 int /*<<< orphan*/  vga_set_8font () ; 
 int /*<<< orphan*/  vga_set_vertical_end (int) ; 

__attribute__((used)) static void vga_set_80x60(void)
{
	vga_set_480_scanlines();
	vga_set_8font();
	vga_set_vertical_end(60*8);
}