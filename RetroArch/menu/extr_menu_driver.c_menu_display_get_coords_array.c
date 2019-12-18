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
typedef  int /*<<< orphan*/  video_coord_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  menu_disp_ca ; 

video_coord_array_t *menu_display_get_coords_array(void)
{
   return &menu_disp_ca;
}