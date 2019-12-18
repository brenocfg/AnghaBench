#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ menu_is_alive; } ;
typedef  TYPE_1__ video_frame_info_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  gfx_ctx_mode_t ;
struct TYPE_7__ {unsigned int* framebuffer; } ;
typedef  TYPE_2__ fpga_t ;

/* Variables and functions */
 unsigned int FB_HEIGHT ; 
 unsigned int FB_WIDTH ; 
 int /*<<< orphan*/  font_driver_render_msg (TYPE_1__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 unsigned int fpga_menu_bits ; 
 void const* fpga_menu_frame ; 
 unsigned int fpga_menu_height ; 
 unsigned int fpga_menu_pitch ; 
 unsigned int fpga_menu_width ; 
 unsigned int fpga_video_bits ; 
 unsigned int fpga_video_height ; 
 unsigned int fpga_video_pitch ; 
 unsigned int fpga_video_width ; 
 int /*<<< orphan*/  menu_driver_frame (TYPE_1__*) ; 
 int /*<<< orphan*/  video_context_driver_get_video_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool fpga_gfx_frame(void *data, const void *frame,
      unsigned frame_width, unsigned frame_height, uint64_t frame_count,
      unsigned pitch, const char *msg, video_frame_info_t *video_info)
{
   gfx_ctx_mode_t mode;
   const void *frame_to_copy = frame;
   unsigned width            = 0;
   unsigned height           = 0;
   unsigned bits             = fpga_video_bits;
   bool draw                 = true;
   fpga_t *fpga                = (fpga_t*)data;

   if (!frame || !frame_width || !frame_height)
      return true;

#ifdef HAVE_MENU
   menu_driver_frame(video_info);
#endif

   if (fpga_video_width != frame_width || fpga_video_height != frame_height || fpga_video_pitch != pitch)
   {
      if (frame_width > 4 && frame_height > 4)
      {
         fpga_video_width = frame_width;
         fpga_video_height = frame_height;
         fpga_video_pitch = pitch;
      }
   }

   if (fpga_menu_frame && video_info->menu_is_alive)
   {
      frame_to_copy = fpga_menu_frame;
      width         = fpga_menu_width;
      height        = fpga_menu_height;
      pitch         = fpga_menu_pitch;
      bits          = fpga_menu_bits;
   }
   else
   {
      width         = fpga_video_width;
      height        = fpga_video_height;
      pitch         = fpga_video_pitch;

      if (frame_width == 4 && frame_height == 4 && (frame_width < width && frame_height < height))
         draw = false;

      if (video_info->menu_is_alive)
         draw = false;
   }

   video_context_driver_get_video_size(&mode);

   if (draw)
   {
      if (bits == 16)
      {
         if (frame_to_copy == fpga_menu_frame)
         {
            /* RGBX4444 color bits for RGUI */
            unsigned x, y;

            for (y = 0; y < FB_HEIGHT; y++)
            {
               for (x = 0; x < FB_WIDTH; x++)
               {
                  /* scale incoming frame to fit the screen */
                  unsigned scaled_x    = (width * x) / FB_WIDTH;
                  unsigned scaled_y    = (height * y) / FB_HEIGHT;
                  unsigned short pixel = ((unsigned short*)frame_to_copy)[width * scaled_y + scaled_x];

                  /* convert RGBX444 to XRGB8888 */
                  unsigned r = ((pixel & 0xF000) >> 12);
                  unsigned g = ((pixel & 0x0F00) >> 8);
                  unsigned b = ((pixel & 0x00F0) >> 4);

                  fpga->framebuffer[FB_WIDTH * y + x] = (r << 20) | (b << 12) | (g << 4);
               }
            }
         }
         else
         {
            /* RGB565 color bits for core */
            unsigned x, y;

            for (y = 0; y < FB_HEIGHT; y++)
            {
               for (x = 0; x < FB_WIDTH; x++)
               {
                  /* scale incoming frame to fit the screen */
                  unsigned scaled_x    = (width * x) / FB_WIDTH;
                  unsigned scaled_y    = (height * y) / FB_HEIGHT;
                  unsigned short pixel = ((unsigned short*)frame_to_copy)[width * scaled_y + scaled_x];

                  /* convert RGB565 to XRBG8888 */
                  unsigned r = ((pixel & 0xF800) >> 11);
                  unsigned g = ((pixel & 0x07E0) >> 5);
                  unsigned b = ((pixel & 0x001F) >> 0);

                  fpga->framebuffer[FB_WIDTH * y + x] = (r << 19) | (b << 11) | (g << 2);
               }
            }
         }
      }
      else
      {
         /* TODO/FIXME: handle 32-bit core output */
      }
   }

   if (msg)
      font_driver_render_msg(video_info, NULL, msg, NULL);

   return true;
}