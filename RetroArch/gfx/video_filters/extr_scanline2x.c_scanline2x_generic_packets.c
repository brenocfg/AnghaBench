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
struct softfilter_thread_data {size_t out_pitch; size_t in_pitch; unsigned int width; unsigned int height; int /*<<< orphan*/  const* in_data; int /*<<< orphan*/ * out_data; } ;
struct filter_data {scalar_t__ in_fmt; int /*<<< orphan*/ * workers; } ;

/* Variables and functions */
 scalar_t__ SOFTFILTER_FMT_RGB565 ; 
 scalar_t__ SOFTFILTER_FMT_XRGB8888 ; 
 int /*<<< orphan*/  scanline2x_work_cb_rgb565 ; 
 int /*<<< orphan*/  scanline2x_work_cb_xrgb8888 ; 

__attribute__((used)) static void scanline2x_generic_packets(void *data,
      struct softfilter_work_packet *packets,
      void *output, size_t output_stride,
      const void *input, unsigned width, unsigned height, size_t input_stride)
{
   /* We are guaranteed single threaded operation
    * (filt->threads = 1) so we don't need to loop
    * over threads and can cull some code. This only
    * makes the tiniest performance difference, but
    * every little helps when running on an o3DS... */
   struct filter_data *filt = (struct filter_data*)data;
   struct softfilter_thread_data *thr = (struct softfilter_thread_data*)&filt->workers[0];

   thr->out_data = (uint8_t*)output;
   thr->in_data = (const uint8_t*)input;
   thr->out_pitch = output_stride;
   thr->in_pitch = input_stride;
   thr->width = width;
   thr->height = height;

   if (filt->in_fmt == SOFTFILTER_FMT_XRGB8888) {
      packets[0].work = scanline2x_work_cb_xrgb8888;
   } else if (filt->in_fmt == SOFTFILTER_FMT_RGB565) {
      packets[0].work = scanline2x_work_cb_rgb565;
   }
   packets[0].thread_data = thr;
}