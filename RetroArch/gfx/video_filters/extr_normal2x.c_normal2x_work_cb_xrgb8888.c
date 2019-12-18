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
struct softfilter_thread_data {int in_pitch; int out_pitch; unsigned int height; unsigned int width; scalar_t__ out_data; scalar_t__ in_data; } ;
typedef  int /*<<< orphan*/  color_buf ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void normal2x_work_cb_xrgb8888(void *data, void *thread_data)
{
   struct softfilter_thread_data *thr = (struct softfilter_thread_data*)thread_data;
   const uint32_t *input = (const uint32_t*)thr->in_data;
   uint32_t *output = (uint32_t*)thr->out_data;
   unsigned in_stride = (unsigned)(thr->in_pitch >> 2);
   unsigned out_stride = (unsigned)(thr->out_pitch >> 2);
   unsigned x, y;

   for (y = 0; y < thr->height; ++y)
   {
      uint32_t *out_ptr = output;
      for (x = 0; x < thr->width; ++x)
      {
         uint32_t color = *(input + x);
         uint32_t color_buf[2];

         color_buf[0] = color;
         color_buf[1] = color;

         memcpy(out_ptr,              color_buf, sizeof(color_buf));
         memcpy(out_ptr + out_stride, color_buf, sizeof(color_buf));

         out_ptr += 2;
      }

      input  += in_stride;
      output += out_stride << 1;
   }
}