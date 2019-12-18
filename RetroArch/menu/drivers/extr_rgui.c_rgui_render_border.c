#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  shadow_color; int /*<<< orphan*/  border_light_color; int /*<<< orphan*/  border_dark_color; } ;
struct TYPE_5__ {int border_thickness; TYPE_1__ colors; scalar_t__ shadow_enable; } ;
typedef  TYPE_2__ rgui_t ;

/* Variables and functions */
 int /*<<< orphan*/  rgui_color_rect (int /*<<< orphan*/ *,unsigned int,unsigned int,int,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgui_fill_rect (int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int,int,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rgui_render_border(rgui_t *rgui, uint16_t *data,
      unsigned fb_width, unsigned fb_height)
{
   uint16_t dark_color;
   uint16_t light_color;
   bool thickness;
   
   /* Sanity check */
   if (!rgui || !data)
      return;
   
   dark_color   = rgui->colors.border_dark_color;
   light_color  = rgui->colors.border_light_color;
   thickness    = rgui->border_thickness;
   
   /* Draw border */
   rgui_fill_rect(data, fb_width, fb_height,
         5, 5, fb_width - 10, 5,
         dark_color, light_color, thickness);
   rgui_fill_rect(data, fb_width, fb_height,
         5, fb_height - 10, fb_width - 10, 5,
         dark_color, light_color, thickness);
   rgui_fill_rect(data, fb_width, fb_height,
         5, 5, 5, fb_height - 10,
         dark_color, light_color, thickness);
   rgui_fill_rect(data, fb_width, fb_height,
         fb_width - 10, 5, 5, fb_height - 10,
         dark_color, light_color, thickness);
   
   /* Draw drop shadow, if required */
   if (rgui->shadow_enable)
   {
      uint16_t shadow_color = rgui->colors.shadow_color;
      
      rgui_color_rect(data, fb_width, fb_height,
            10, 10, 1, fb_height - 20, shadow_color);
      rgui_color_rect(data, fb_width, fb_height,
            10, 10, fb_width - 20, 1, shadow_color);
      rgui_color_rect(data, fb_width, fb_height,
            fb_width - 5, 6, 1, fb_height - 10, shadow_color);
      rgui_color_rect(data, fb_width, fb_height,
            6, fb_height - 5, fb_width - 10, 1, shadow_color);
   }
}