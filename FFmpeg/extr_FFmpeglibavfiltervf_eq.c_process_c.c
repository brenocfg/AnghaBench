#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {int contrast; double brightness; } ;
typedef  TYPE_1__ EQParameters ;

/* Variables and functions */

__attribute__((used)) static void process_c(EQParameters *param, uint8_t *dst, int dst_stride,
                      const uint8_t *src, int src_stride, int w, int h)
{
    int x, y, pel;

    int contrast = (int) (param->contrast * 256 * 16);
    int brightness = ((int) (100.0 * param->brightness + 100.0) * 511) / 200 - 128 - contrast / 32;

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            pel = ((src[y * src_stride + x] * contrast) >> 12) + brightness;

            if (pel & ~255)
                pel = (-pel) >> 31;

            dst[y * dst_stride + x] = pel;
        }
    }
}