#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ width; scalar_t__ height; scalar_t__ rgb32; int /*<<< orphan*/ * texture; int /*<<< orphan*/  tex_filter; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ vita_video_t ;
struct retro_framebuffer {scalar_t__ width; scalar_t__ height; scalar_t__ memory_flags; int /*<<< orphan*/  format; int /*<<< orphan*/  pitch; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  RETRO_PIXEL_FORMAT_RGB565 ; 
 int /*<<< orphan*/  RETRO_PIXEL_FORMAT_XRGB8888 ; 
 int /*<<< orphan*/ * vita2d_create_empty_texture_format (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vita2d_free_texture (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vita2d_texture_get_datap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vita2d_texture_get_stride (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vita2d_texture_set_filters (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vita2d_wait_rendering_done () ; 

__attribute__((used)) static bool vita_get_current_sw_framebuffer(void *data,
      struct retro_framebuffer *framebuffer)
{
   vita_video_t *vita = (vita_video_t*)data;

   if (!vita->texture || vita->width != framebuffer->width ||
         vita->height != framebuffer->height)
   {
      if(vita->texture)
      {
         vita2d_wait_rendering_done();
         vita2d_free_texture(vita->texture);
         vita->texture = NULL;
      }

      vita->width = framebuffer->width;
      vita->height = framebuffer->height;
      vita->texture = vita2d_create_empty_texture_format(
            vita->width, vita->height, vita->format);
      vita2d_texture_set_filters(vita->texture,
            vita->tex_filter,vita->tex_filter);
   }

   framebuffer->data         = vita2d_texture_get_datap(vita->texture);
   framebuffer->pitch        = vita2d_texture_get_stride(vita->texture);
   framebuffer->format       = vita->rgb32
      ? RETRO_PIXEL_FORMAT_XRGB8888 : RETRO_PIXEL_FORMAT_RGB565;
   framebuffer->memory_flags = 0;

   return true;
}