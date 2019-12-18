#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  normal_color; } ;
struct TYPE_6__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_8__ {TYPE_2__ colors; TYPE_1__ pointer; } ;
typedef  TYPE_3__ rgui_t ;
struct TYPE_9__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  menu_display_get_fb_size (unsigned int*,unsigned int*,size_t*) ; 
 int /*<<< orphan*/  rgui_color_rect (scalar_t__,unsigned int,unsigned int,scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 TYPE_4__ rgui_frame_buf ; 

__attribute__((used)) static void rgui_blit_cursor(rgui_t *rgui)
{
   size_t fb_pitch;
   unsigned fb_width, fb_height;

   menu_display_get_fb_size(&fb_width, &fb_height,
         &fb_pitch);

   if (rgui_frame_buf.data)
   {
      rgui_color_rect(rgui_frame_buf.data, fb_width, fb_height, rgui->pointer.x, rgui->pointer.y - 5, 1, 11, rgui->colors.normal_color);
      rgui_color_rect(rgui_frame_buf.data, fb_width, fb_height, rgui->pointer.x - 5, rgui->pointer.y, 11, 1, rgui->colors.normal_color);
   }
}