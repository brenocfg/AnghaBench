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
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */

void conv_rgba4444_rgb565(void *output_, const void *input_,
      int width, int height,
      int out_stride, int in_stride)
{
   int h, w;
   const uint16_t *input = (const uint16_t*)input_;
   uint16_t *output      = (uint16_t*)output_;

   for (h = 0; h < height;
         h++, output += out_stride >> 1, input += in_stride >> 1)
   {
      for (w = 0; w < width; w++)
      {
         uint32_t col = input[w];
         uint32_t r   = (col >> 12) & 0xf;
         uint32_t g   = (col >>  8) & 0xf;
         uint32_t b   = (col >>  4) & 0xf;

         output[w]    = (r << 12) | (g << 7) | (b << 1);
      }
   }
}