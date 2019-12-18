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
typedef  int uint16_t ;
struct softfilter_thread_data {unsigned int width; unsigned int height; int in_pitch; int out_pitch; scalar_t__ out_data; scalar_t__ in_data; } ;

/* Variables and functions */

__attribute__((used)) static void darken_work_cb_rgb565(void *data, void *thread_data)
{
   struct softfilter_thread_data *thr =
      (struct softfilter_thread_data*)thread_data;
   const uint16_t *input = (const uint16_t*)thr->in_data;
   uint16_t *output = (uint16_t*)thr->out_data;
   unsigned width = thr->width;
   unsigned height = thr->height;

   unsigned x, y;
   for (y = 0; y < height;
         y++, input += thr->in_pitch >> 1, output += thr->out_pitch >> 1)
      for (x = 0; x < width; x++)
         output[x] = (input[x] >> 2) & ((0x7 << 0) | (0xf << 5) | (0x7 << 11));
}