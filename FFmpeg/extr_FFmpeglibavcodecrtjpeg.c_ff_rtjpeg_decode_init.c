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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int* idct_permutation; } ;
struct TYPE_5__ {int w; int h; int /*<<< orphan*/ * cquant; int /*<<< orphan*/ * lquant; TYPE_1__ idsp; } ;
typedef  TYPE_2__ RTJpegContext ;

/* Variables and functions */

void ff_rtjpeg_decode_init(RTJpegContext *c, int width, int height,
                           const uint32_t *lquant, const uint32_t *cquant) {
    int i;
    for (i = 0; i < 64; i++) {
        int p = c->idsp.idct_permutation[i];
        c->lquant[p] = lquant[i];
        c->cquant[p] = cquant[i];
    }
    c->w = width;
    c->h = height;
}