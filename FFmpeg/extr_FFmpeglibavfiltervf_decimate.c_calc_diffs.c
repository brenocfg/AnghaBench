#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;
struct qitem {scalar_t__ totdiff; scalar_t__ maxbdiff; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_7__ {int* linesize; int width; int height; scalar_t__** data; } ;
struct TYPE_6__ {int bdiffsize; int hsub; int vsub; int blockx; int blocky; int depth; int nxblocks; int nyblocks; scalar_t__ chroma; scalar_t__* bdiffs; } ;
typedef  TYPE_1__ DecimateContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int,int) ; 
 int FFMIN (int,int) ; 
 scalar_t__ abs (scalar_t__ const) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void calc_diffs(const DecimateContext *dm, struct qitem *q,
                       const AVFrame *f1, const AVFrame *f2)
{
    int64_t maxdiff = -1;
    int64_t *bdiffs = dm->bdiffs;
    int plane, i, j;

    memset(bdiffs, 0, dm->bdiffsize * sizeof(*bdiffs));

    for (plane = 0; plane < (dm->chroma && f1->data[2] ? 3 : 1); plane++) {
        int x, y, xl;
        const int linesize1 = f1->linesize[plane];
        const int linesize2 = f2->linesize[plane];
        const uint8_t *f1p = f1->data[plane];
        const uint8_t *f2p = f2->data[plane];
        int width    = plane ? AV_CEIL_RSHIFT(f1->width,  dm->hsub) : f1->width;
        int height   = plane ? AV_CEIL_RSHIFT(f1->height, dm->vsub) : f1->height;
        int hblockx  = dm->blockx / 2;
        int hblocky  = dm->blocky / 2;

        if (plane) {
            hblockx >>= dm->hsub;
            hblocky >>= dm->vsub;
        }

        for (y = 0; y < height; y++) {
            int ydest = y / hblocky;
            int xdest = 0;

#define CALC_DIFF(nbits) do {                               \
    for (x = 0; x < width; x += hblockx) {                  \
        int64_t acc = 0;                                    \
        int m = FFMIN(width, x + hblockx);                  \
        for (xl = x; xl < m; xl++)                          \
            acc += abs(((const uint##nbits##_t *)f1p)[xl] - \
                       ((const uint##nbits##_t *)f2p)[xl]); \
        bdiffs[ydest * dm->nxblocks + xdest] += acc;        \
        xdest++;                                            \
    }                                                       \
} while (0)
            if (dm->depth == 8) CALC_DIFF(8);
            else                CALC_DIFF(16);

            f1p += linesize1;
            f2p += linesize2;
        }
    }

    for (i = 0; i < dm->nyblocks - 1; i++) {
        for (j = 0; j < dm->nxblocks - 1; j++) {
            int64_t tmp = bdiffs[      i * dm->nxblocks + j    ]
                        + bdiffs[      i * dm->nxblocks + j + 1]
                        + bdiffs[(i + 1) * dm->nxblocks + j    ]
                        + bdiffs[(i + 1) * dm->nxblocks + j + 1];
            if (tmp > maxdiff)
                maxdiff = tmp;
        }
    }

    q->totdiff = 0;
    for (i = 0; i < dm->bdiffsize; i++)
        q->totdiff += bdiffs[i];
    q->maxbdiff = maxdiff;
}