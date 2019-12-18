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

/* Variables and functions */
 int /*<<< orphan*/  blend_pixels_xrgb8888 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void blit_linear_line_xrgb8888(uint32_t * out,
      const uint32_t *in, unsigned width)
{
   unsigned i;

   /* Splat pixels out on the line. */
   for (i = 0; i < width; i++)
      out[i << 1] = in[i];

   /* Blend in-between pixels. */
   for (i = 1; i < (width << 1) - 1; i += 2)
      out[i] = blend_pixels_xrgb8888(out[i - 1], out[i + 1]);

   /* Blend edge pixels against black. */
   out[0] = blend_pixels_xrgb8888(out[0], 0);
   out[(width << 1) - 1] =
      blend_pixels_xrgb8888(out[(width << 1) - 1], 0);
}