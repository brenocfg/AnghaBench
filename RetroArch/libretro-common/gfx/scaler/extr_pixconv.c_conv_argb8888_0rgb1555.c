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

void conv_argb8888_0rgb1555(void *output_, const void *input_,
      int width, int height,
      int out_stride, int in_stride)
{
   int h, w;
   const uint32_t *input = (const uint32_t*)input_;
   uint16_t *output      = (uint16_t*)output_;

   for (h = 0; h < height;
         h++, output += out_stride >> 1, input += in_stride >> 2)
   {
      for (w = 0; w < width; w++)
      {
         uint32_t col = input[w];
         uint16_t r   = (col >> 19) & 0x1f;
         uint16_t g   = (col >> 11) & 0x1f;
         uint16_t b   = (col >>  3) & 0x1f;
         output[w]    = (r << 10) | (g << 5) | (b << 0);
      }
   }
}