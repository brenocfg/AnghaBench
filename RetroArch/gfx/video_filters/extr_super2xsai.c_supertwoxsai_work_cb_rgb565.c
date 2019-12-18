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
typedef  int /*<<< orphan*/  uint16_t ;
struct softfilter_thread_data {unsigned int width; unsigned int height; int in_pitch; int out_pitch; int /*<<< orphan*/  last; int /*<<< orphan*/  first; scalar_t__ out_data; scalar_t__ in_data; } ;

/* Variables and functions */
 int SOFTFILTER_BPP_RGB565 ; 
 int /*<<< orphan*/  supertwoxsai_generic_rgb565 (unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void supertwoxsai_work_cb_rgb565(void *data, void *thread_data)
{
   struct softfilter_thread_data *thr = (struct softfilter_thread_data*)thread_data;
   uint16_t *input = (uint16_t*)thr->in_data;
   uint16_t *output = (uint16_t*)thr->out_data;
   unsigned width = thr->width;
   unsigned height = thr->height;

   supertwoxsai_generic_rgb565(width, height,
         thr->first, thr->last, input,
        (unsigned)(thr->in_pitch / SOFTFILTER_BPP_RGB565),
        output,
        (unsigned)(thr->out_pitch / SOFTFILTER_BPP_RGB565));
}