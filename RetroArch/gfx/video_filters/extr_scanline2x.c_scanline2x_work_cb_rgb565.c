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
typedef  int uint16_t ;
struct softfilter_thread_data {int in_pitch; int out_pitch; unsigned int height; unsigned int width; scalar_t__ out_data; scalar_t__ in_data; } ;
typedef  int /*<<< orphan*/  scanline_color_buf ;
typedef  int /*<<< orphan*/  color_buf ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static void scanline2x_work_cb_rgb565(void *data, void *thread_data)
{
   struct softfilter_thread_data *thr = (struct softfilter_thread_data*)thread_data;
   const uint16_t *input = (const uint16_t*)thr->in_data;
   uint16_t *output = (uint16_t*)thr->out_data;
   unsigned in_stride = (unsigned)(thr->in_pitch >> 1);
   unsigned out_stride = (unsigned)(thr->out_pitch >> 1);
   unsigned x, y;

   for (y = 0; y < thr->height; ++y)
   {
      uint16_t *out_ptr = output;
      for (x = 0; x < thr->width; ++x)
      {
         uint16_t color          = *(input + x);
         uint8_t  r              = (color >> 11 & 0x1F);
         uint8_t  g              = (color >>  6 & 0x1F);
         uint8_t  b              = (color       & 0x1F);
         uint16_t scanline_color =
               (((r >> 1) + (r >> 2)) << 11) |
               (((g >> 1) + (g >> 2)) <<  6) |
               (((b >> 1) + (b >> 2))      );
         uint16_t color_buf[2];
         uint16_t scanline_color_buf[2];

         color_buf[0] = color;
         color_buf[1] = color;

         scanline_color_buf[0] = scanline_color;
         scanline_color_buf[1] = scanline_color;

         memcpy(out_ptr,              color_buf,          sizeof(color_buf));
         memcpy(out_ptr + out_stride, scanline_color_buf, sizeof(scanline_color_buf));

         out_ptr += 2;
      }

      input  += in_stride;
      output += out_stride << 1;
   }
}