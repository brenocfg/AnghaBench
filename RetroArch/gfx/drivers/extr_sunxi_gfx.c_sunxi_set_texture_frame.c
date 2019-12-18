#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct sunxi_video {TYPE_2__* sunxi_disp; TYPE_1__* pages; scalar_t__ menu_active; } ;
struct TYPE_4__ {int xres; int /*<<< orphan*/  bits_per_pixel; } ;
struct TYPE_3__ {int /*<<< orphan*/  offset; scalar_t__ address; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  sunxi_layer_set_rgb_input_buffer (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void sunxi_set_texture_frame(void *data, const void *frame, bool rgb32,
      unsigned width, unsigned height, float alpha)
{
   struct sunxi_video *_dispvars = (struct sunxi_video*)data;

   if (_dispvars->menu_active)
   {
      unsigned int i, j;

      /* We have to go on a pixel format conversion adventure for now, until we can
       * convince RGUI to output in an 8888 format. */
      unsigned int src_pitch        = width * 2;
      unsigned int dst_pitch        = _dispvars->sunxi_disp->xres * 4;
      unsigned int dst_width        = _dispvars->sunxi_disp->xres;
      uint32_t line[dst_width];

      /* Remember, memcpy() works with 8bits pointers for increments. */
      char *dst_base_addr           = (char*)(_dispvars->pages[0].address);

      for (i = 0; i < height; i++)
      {
         for (j = 0; j < src_pitch / 2; j++)
         {
            uint16_t src_pix = *((uint16_t*)frame + (src_pitch / 2 * i) + j);
            /* The hex AND is for keeping only the part we need for each component. */
            uint32_t R = (src_pix << 8) & 0x00FF0000;
            uint32_t G = (src_pix << 4) & 0x0000FF00;
            uint32_t B = (src_pix << 0) & 0x000000FF;
            line[j] = (0 | R | G | B);
         }
         memcpy(dst_base_addr + (dst_pitch * i), (char*)line, dst_pitch);
      }

      /* Issue pageflip. Will flip on next vsync. */
      sunxi_layer_set_rgb_input_buffer(_dispvars->sunxi_disp,
            _dispvars->sunxi_disp->bits_per_pixel,
            _dispvars->pages[0].offset, width, height, _dispvars->sunxi_disp->xres);
   }
}