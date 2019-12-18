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
typedef  enum image_type_enum { ____Placeholder_image_type_enum } image_type_enum ;

/* Variables and functions */
 int /*<<< orphan*/  TEXTURE_FILTER_MIPMAP_LINEAR ; 
 int /*<<< orphan*/  ai_service_overlay_height ; 
 int ai_service_overlay_state ; 
 int /*<<< orphan*/  ai_service_overlay_texture ; 
 int /*<<< orphan*/  ai_service_overlay_width ; 
 int menu_display_reset_textures_list_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,unsigned int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool menu_widgets_ai_service_overlay_load(
        char* buffer, unsigned buffer_len, enum image_type_enum image_type)
{
   if (ai_service_overlay_state == 0)
   {
      bool res;
      res = menu_display_reset_textures_list_buffer(
               &ai_service_overlay_texture, 
               TEXTURE_FILTER_MIPMAP_LINEAR, 
               (void *) buffer, buffer_len, image_type,
               &ai_service_overlay_width, &ai_service_overlay_height);
      if (res)
         ai_service_overlay_state = 1;
      return res;
   }
   return true;
}