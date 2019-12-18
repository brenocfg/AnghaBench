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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int scale_v; int scale_h; } ;
typedef  TYPE_1__ GDVContext ;

/* Variables and functions */
 int PREAMBLE_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scaledown (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scaleup_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void rescale(GDVContext *gdv, uint8_t *dst, int w, int h, int scale_v, int scale_h)
{
    int j, y;

    if ((gdv->scale_v == scale_v) && (gdv->scale_h == scale_h)) {
        return;
    }

    if (gdv->scale_v) {
        for (j = 0; j < h; j++) {
            int y = h - j - 1;
            uint8_t *dst1 = dst + PREAMBLE_SIZE + y * w;
            uint8_t *src1 = dst + PREAMBLE_SIZE + (y>>!!gdv->scale_h) * (w>>1);

            scaleup_rev(dst1, src1, w);
        }
    } else if (gdv->scale_h) {
        for (j = 0; j < h; j++) {
            int y = h - j - 1;
            uint8_t *dst1 = dst + PREAMBLE_SIZE + y * w;
            uint8_t *src1 = dst + PREAMBLE_SIZE + (y>>1) * w;
            memcpy(dst1, src1, w);
        }
    }

    if (scale_h && scale_v) {
        for (y = 0; y < (h>>1); y++) {
            uint8_t *dst1 = dst + PREAMBLE_SIZE + y * (w>>1);
            uint8_t *src1 = dst + PREAMBLE_SIZE + y*2 * w;
            scaledown(dst1, src1, w>>1);
        }
    } else if (scale_h) {
        for (y = 0; y < (h>>1); y++) {
            uint8_t *dst1 = dst + PREAMBLE_SIZE + y * w;
            uint8_t *src1 = dst + PREAMBLE_SIZE + y*2 * w;
            memcpy(dst1, src1, w);
        }
    } else if (scale_v) {
        for (y = 0; y < h; y++) {
            uint8_t *dst1 = dst + PREAMBLE_SIZE + y * w;
            scaledown(dst1, dst1, w>>1);
        }
    }

    gdv->scale_v = scale_v;
    gdv->scale_h = scale_h;
}