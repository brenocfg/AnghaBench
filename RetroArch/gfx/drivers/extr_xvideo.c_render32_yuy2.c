#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int width; int /*<<< orphan*/ * vtable; int /*<<< orphan*/ * utable; int /*<<< orphan*/ * ytable; TYPE_1__* image; } ;
typedef  TYPE_2__ xv_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */

__attribute__((used)) static void render32_yuy2(xv_t *xv, const void *input_,
      unsigned width, unsigned height, unsigned pitch)
{
   unsigned x, y;
   const uint32_t *input = (const uint32_t*)input_;
   uint8_t *output       = (uint8_t*)xv->image->data;

   for (y = 0; y < height; y++)
   {
      for (x = 0; x < width; x++)
      {
         uint8_t y0, u, v;
         unsigned img_width;
         uint32_t p = *input++;
         p = ((p >> 8) & 0xf800) | ((p >> 5) & 0x07e0)
            | ((p >> 3) & 0x1f); /* ARGB -> RGB16 */

         y0        = xv->ytable[p];
         u         = xv->utable[p];
         v         = xv->vtable[p];

         img_width = xv->width << 1;
         output[0] = output[img_width] = y0;
         output[1] = output[img_width + 1] = u;
         output[2] = output[img_width + 2] = y0;
         output[3] = output[img_width + 3] = v;
         output += 4;
      }

      input  += (pitch >> 2) - width;
      output += (xv->width - width) << 2;
   }
}