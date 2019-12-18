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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct texture_image {int width; int height; int /*<<< orphan*/ * pixels; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEXTURE_FILTER_NEAREST ; 
 scalar_t__ menu_display_white_texture ; 
 int /*<<< orphan*/  video_driver_texture_load (struct texture_image*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  video_driver_texture_unload (scalar_t__*) ; 

void menu_display_allocate_white_texture(void)
{
   struct texture_image ti;
   static const uint8_t white_data[] = { 0xff, 0xff, 0xff, 0xff };

   ti.width  = 1;
   ti.height = 1;
   ti.pixels = (uint32_t*)&white_data;

   if (menu_display_white_texture)
      video_driver_texture_unload(&menu_display_white_texture);

   video_driver_texture_load(&ti,
         TEXTURE_FILTER_NEAREST, &menu_display_white_texture);
}