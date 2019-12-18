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
typedef  int col ;

/* Variables and functions */

void conv_argb8888_rgba4444(void *output_, const void *input_,
      int width, int height,
      int out_stride, int in_stride)
{
   int h, w;
   const uint32_t *input = (const uint32_t*)input_;
   uint16_t *output      = (uint16_t*)output_;

   for (h = 0; h < height;
         h++, output += out_stride >> 2, input += in_stride >> 1)
   {
      for (w = 0; w < width; w++)
      {
         uint32_t col = input[w];
         uint32_t r   = (col >> 16) & 0xf;
         uint32_t g   = (col >>  8) & 0xf;
         uint32_t b   = (col) & 0xf;
         uint32_t a   = (col >>  24) & 0xf;
         r            = (r >> 4) | r;
         g            = (g >> 4) | g;
         b            = (b >> 4) | b;
         a            = (a >> 4) | a;

         output[w]    = (r << 12) | (g << 8) | (b << 4) | a;
      }
   }
}