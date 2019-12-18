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
struct softfilter_work_packet {struct softfilter_thread_data* thread_data; int /*<<< orphan*/  work; } ;
struct softfilter_thread_data {size_t out_pitch; size_t in_pitch; unsigned int width; unsigned int height; unsigned int first; int last; int /*<<< orphan*/  const* in_data; int /*<<< orphan*/ * out_data; } ;
struct filter_data {unsigned int threads; scalar_t__ in_fmt; int /*<<< orphan*/ * workers; } ;

/* Variables and functions */
 scalar_t__ SOFTFILTER_FMT_RGB565 ; 
 scalar_t__ SOFTFILTER_FMT_XRGB8888 ; 
 unsigned int SUPERTWOXSAI_SCALE ; 
 int /*<<< orphan*/  supertwoxsai_work_cb_rgb565 ; 
 int /*<<< orphan*/  supertwoxsai_work_cb_xrgb8888 ; 

__attribute__((used)) static void supertwoxsai_generic_packets(void *data,
      struct softfilter_work_packet *packets,
      void *output, size_t output_stride,
      const void *input, unsigned width, unsigned height, size_t input_stride)
{
   unsigned i;
   struct filter_data *filt = (struct filter_data*)data;

   for (i = 0; i < filt->threads; i++)
   {
      struct softfilter_thread_data *thr = (struct softfilter_thread_data*)&filt->workers[i];

      unsigned y_start = (height * i) / filt->threads;
      unsigned y_end = (height * (i + 1)) / filt->threads;
      thr->out_data = (uint8_t*)output + y_start * SUPERTWOXSAI_SCALE * output_stride;
      thr->in_data = (const uint8_t*)input + y_start * input_stride;
      thr->out_pitch = output_stride;
      thr->in_pitch = input_stride;
      thr->width = width;
      thr->height = y_end - y_start;

      // Workers need to know if they can access pixels outside their given buffer.
      thr->first = y_start;
      thr->last = y_end == height;

      if (filt->in_fmt == SOFTFILTER_FMT_RGB565)
         packets[i].work = supertwoxsai_work_cb_rgb565;
      else if (filt->in_fmt == SOFTFILTER_FMT_XRGB8888)
         packets[i].work = supertwoxsai_work_cb_xrgb8888;
      packets[i].thread_data = thr;
   }
}