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
struct texture_image {unsigned int width; unsigned int height; int /*<<< orphan*/  supports_rgba; int /*<<< orphan*/ * pixels; } ;
typedef  enum texture_filter_type { ____Placeholder_texture_filter_type } texture_filter_type ;
typedef  enum image_type_enum { ____Placeholder_image_type_enum } image_type_enum ;

/* Variables and functions */
 int /*<<< orphan*/  image_texture_free (struct texture_image*) ; 
 int /*<<< orphan*/  image_texture_load_buffer (struct texture_image*,int,void*,unsigned int) ; 
 int /*<<< orphan*/  video_driver_supports_rgba () ; 
 int /*<<< orphan*/  video_driver_texture_load (struct texture_image*,int,uintptr_t*) ; 

bool menu_display_reset_textures_list_buffer(
        uintptr_t *item, enum texture_filter_type filter_type,
        void* buffer, unsigned buffer_len, enum image_type_enum image_type,
        unsigned *width, unsigned *height)
{
   struct texture_image ti;

   ti.width                      = 0;
   ti.height                     = 0;
   ti.pixels                     = NULL;
   ti.supports_rgba              = video_driver_supports_rgba();

   if (!image_texture_load_buffer(&ti, image_type, buffer, buffer_len))
      return false;

   if (width)
      *width = ti.width;

   if (height)
      *height = ti.height;

   /* if the poke interface doesn't support texture load then return false */  
   if (!video_driver_texture_load(&ti, filter_type, item))
       return false;
   image_texture_free(&ti);
   return true;
}