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
 int /*<<< orphan*/  trap_CIN_DrawCinematic (int) ; 
 int /*<<< orphan*/  trap_CIN_SetExtents (int,float,float,float,float) ; 

__attribute__((used)) static void UI_DrawCinematic(int handle, float x, float y, float w, float h) {
	trap_CIN_SetExtents(handle, x, y, w, h);
  trap_CIN_DrawCinematic(handle);
}