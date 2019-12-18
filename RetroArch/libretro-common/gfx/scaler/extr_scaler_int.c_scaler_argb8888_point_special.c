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
typedef  int /*<<< orphan*/  uint32_t ;
struct scaler_ctx {int dummy; } ;

/* Variables and functions */

void scaler_argb8888_point_special(const struct scaler_ctx *ctx,
      void *output_, const void *input_,
      int out_width, int out_height,
      int in_width, int in_height,
      int out_stride, int in_stride)
{
   int h, w;
   int x_pos             = (1 << 15) * in_width / out_width - (1 << 15);
   int x_step            = (1 << 16) * in_width / out_width;
   int y_pos             = (1 << 15) * in_height / out_height - (1 << 15);
   int y_step            = (1 << 16) * in_height / out_height;
   const uint32_t *input = (const uint32_t*)input_;
   uint32_t *output      = (uint32_t*)output_;

   if (x_pos < 0)
      x_pos = 0;
   if (y_pos < 0)
      y_pos = 0;

   for (h = 0; h < out_height; h++, y_pos += y_step, output += out_stride >> 2)
   {
      int               x = x_pos;
      const uint32_t *inp = input + (y_pos >> 16) * (in_stride >> 2);

      for (w = 0; w < out_width; w++, x += x_step)
         output[w] = inp[x >> 16];
   }
}