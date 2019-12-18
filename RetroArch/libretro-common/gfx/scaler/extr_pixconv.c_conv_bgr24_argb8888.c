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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */

void conv_bgr24_argb8888(void *output_, const void *input_,
      int width, int height,
      int out_stride, int in_stride)
{
   int h, w;
   const uint8_t *input = (const uint8_t*)input_;
   uint32_t *output     = (uint32_t*)output_;

   for (h = 0; h < height;
         h++, output += out_stride >> 2, input += in_stride)
   {
      const uint8_t *inp = input;
      for (w = 0; w < width; w++)
      {
         uint32_t b = *inp++;
         uint32_t g = *inp++;
         uint32_t r = *inp++;
         output[w]  = (0xffu << 24) | (r << 16) | (g << 8) | (b << 0);
      }
   }
}