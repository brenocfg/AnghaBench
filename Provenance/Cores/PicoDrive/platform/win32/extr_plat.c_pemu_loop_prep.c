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
 int /*<<< orphan*/  PDF_RGB555 ; 
 int /*<<< orphan*/  PicoDrawSetOutBuf (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PicoDrawSetOutFormat (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_screen_ptr ; 
 int g_screen_width ; 
 int /*<<< orphan*/  pemu_sound_start () ; 

void pemu_loop_prep(void)
{
	PicoDrawSetOutFormat(PDF_RGB555, 1);
	PicoDrawSetOutBuf(g_screen_ptr, g_screen_width * 2);
	pemu_sound_start();
}