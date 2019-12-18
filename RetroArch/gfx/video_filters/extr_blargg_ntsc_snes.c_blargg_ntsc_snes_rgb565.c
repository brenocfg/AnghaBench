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

/* Variables and functions */
 int /*<<< orphan*/  blargg_ntsc_snes_render_rgb565 (void*,unsigned int,unsigned int,int,int,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void blargg_ntsc_snes_rgb565(void *data, unsigned width, unsigned height,
      int first, int last, uint16_t *src,
      unsigned src_stride, uint16_t *dst, unsigned dst_stride)
{
   blargg_ntsc_snes_render_rgb565(data, width, height,
         first, last,
         src, src_stride,
         dst, dst_stride);

}