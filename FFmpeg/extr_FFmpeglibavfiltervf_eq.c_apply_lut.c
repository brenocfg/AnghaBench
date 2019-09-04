#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_4__ {size_t* lut; int /*<<< orphan*/  lut_clean; } ;
typedef  TYPE_1__ EQParameters ;

/* Variables and functions */
 int /*<<< orphan*/  create_lut (TYPE_1__*) ; 

__attribute__((used)) static void apply_lut(EQParameters *param, uint8_t *dst, int dst_stride,
                      const uint8_t *src, int src_stride, int w, int h)
{
    int x, y;

    if (!param->lut_clean)
        create_lut(param);

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            dst[y * dst_stride + x] = param->lut[src[y * src_stride + x]];
        }
    }
}