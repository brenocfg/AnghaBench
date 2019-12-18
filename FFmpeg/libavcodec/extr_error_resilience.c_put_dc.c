#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {TYPE_1__* f; } ;
struct TYPE_7__ {int** dc_val; int b8_stride; int mb_stride; TYPE_2__ cur_pic; } ;
struct TYPE_5__ {int* linesize; } ;
typedef  TYPE_3__ ERContext ;

/* Variables and functions */

__attribute__((used)) static void put_dc(ERContext *s, uint8_t *dest_y, uint8_t *dest_cb,
                   uint8_t *dest_cr, int mb_x, int mb_y)
{
    int *linesize = s->cur_pic.f->linesize;
    int dc, dcu, dcv, y, i;
    for (i = 0; i < 4; i++) {
        dc = s->dc_val[0][mb_x * 2 + (i &  1) + (mb_y * 2 + (i >> 1)) * s->b8_stride];
        if (dc < 0)
            dc = 0;
        else if (dc > 2040)
            dc = 2040;
        for (y = 0; y < 8; y++) {
            int x;
            for (x = 0; x < 8; x++)
                dest_y[x + (i &  1) * 8 + (y + (i >> 1) * 8) * linesize[0]] = dc / 8;
        }
    }
    dcu = s->dc_val[1][mb_x + mb_y * s->mb_stride];
    dcv = s->dc_val[2][mb_x + mb_y * s->mb_stride];
    if (dcu < 0)
        dcu = 0;
    else if (dcu > 2040)
        dcu = 2040;
    if (dcv < 0)
        dcv = 0;
    else if (dcv > 2040)
        dcv = 2040;

    if (dest_cr)
    for (y = 0; y < 8; y++) {
        int x;
        for (x = 0; x < 8; x++) {
            dest_cb[x + y * linesize[1]] = dcu / 8;
            dest_cr[x + y * linesize[2]] = dcv / 8;
        }
    }
}