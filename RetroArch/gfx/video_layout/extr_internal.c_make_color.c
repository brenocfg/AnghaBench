#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {float r; float g; float b; float a; } ;
typedef  TYPE_1__ video_layout_color_t ;

/* Variables and functions */

video_layout_color_t make_color(void)
{
   video_layout_color_t color;
   color.r = 0.0f;
   color.g = 0.0f;
   color.b = 0.0f;
   color.a = 0.0f;
   return color;
}