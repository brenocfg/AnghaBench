#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
typedef  int int32_t ;
struct TYPE_12__ {int i_stepsize; } ;
struct TYPE_11__ {int** coord; } ;
struct TYPE_10__ {int* i_data; int** coord; } ;
struct TYPE_9__ {int* data; int stride; } ;
typedef  TYPE_1__ Jpeg2000T1Context ;
typedef  TYPE_2__ Jpeg2000Component ;
typedef  TYPE_3__ Jpeg2000Cblk ;
typedef  TYPE_4__ Jpeg2000Band ;

/* Variables and functions */

__attribute__((used)) static void dequantization_int(int x, int y, Jpeg2000Cblk *cblk,
                               Jpeg2000Component *comp,
                               Jpeg2000T1Context *t1, Jpeg2000Band *band)
{
    int i, j;
    int w = cblk->coord[0][1] - cblk->coord[0][0];
    for (j = 0; j < (cblk->coord[1][1] - cblk->coord[1][0]); ++j) {
        int32_t *datap = &comp->i_data[(comp->coord[0][1] - comp->coord[0][0]) * (y + j) + x];
        int *src = t1->data + j*t1->stride;
        if (band->i_stepsize == 32768) {
            for (i = 0; i < w; ++i)
                datap[i] = src[i] / 2;
        } else {
            // This should be VERY uncommon
            for (i = 0; i < w; ++i)
                datap[i] = (src[i] * (int64_t)band->i_stepsize) / 65536;
        }
    }
}