#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int mb_x; int mb_y; int mb_width; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__*** last_mv; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 int ff_h261_get_picture_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_init_block_index (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_update_block_index (TYPE_1__*) ; 
 int /*<<< orphan*/  h261_encode_gob_header (TYPE_1__*,int /*<<< orphan*/ ) ; 

void ff_h261_reorder_mb_index(MpegEncContext *s)
{
    int index = s->mb_x + s->mb_y * s->mb_width;

    if (index % 11 == 0) {
        if (index % 33 == 0)
            h261_encode_gob_header(s, 0);
        s->last_mv[0][0][0] = 0;
        s->last_mv[0][0][1] = 0;
    }

    /* for CIF the GOB's are fragmented in the middle of a scanline
     * that's why we need to adjust the x and y index of the macroblocks */
    if (ff_h261_get_picture_format(s->width, s->height) == 1) { // CIF
        s->mb_x  = index % 11;
        index   /= 11;
        s->mb_y  = index % 3;
        index   /= 3;
        s->mb_x += 11 * (index % 2);
        index   /= 2;
        s->mb_y += 3 * index;

        ff_init_block_index(s);
        ff_update_block_index(s);
    }
}