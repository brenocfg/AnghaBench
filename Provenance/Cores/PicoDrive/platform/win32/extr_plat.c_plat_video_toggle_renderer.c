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
 int /*<<< orphan*/  PicoDrawSetOutFormat (int /*<<< orphan*/ ,int) ; 

void plat_video_toggle_renderer(int change, int is_menu)
{
	// this will auto-select SMS/32X renderers
	PicoDrawSetOutFormat(PDF_RGB555, 1);
}