#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  double uint16_t ;
struct TYPE_6__ {int block_size; } ;
struct TYPE_5__ {int y; int x; } ;
typedef  TYPE_1__ PosCode ;
typedef  TYPE_2__ BM3DContext ;

/* Variables and functions */

__attribute__((used)) static double do_block_ssd16(BM3DContext *s, PosCode *pos, const uint8_t *src, int src_stride, int r_y, int r_x)
{
    const uint16_t *srcp = (uint16_t *)src + pos->y * src_stride / 2 + pos->x;
    const uint16_t *refp = (uint16_t *)src + r_y * src_stride / 2 + r_x;
    const int block_size = s->block_size;
    double dist = 0.;
    int x, y;

    for (y = 0; y < block_size; y++) {
        for (x = 0; x < block_size; x++) {
            double temp = refp[x] - srcp[x];
            dist += temp * temp;
        }

        srcp += src_stride / 2;
        refp += src_stride / 2;
    }

    return dist;
}