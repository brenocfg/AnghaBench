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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  Wmv2Context ;
struct TYPE_5__ {int linesize; int uvlinesize; TYPE_1__* avctx; } ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 int AV_CODEC_FLAG_GRAY ; 
 int /*<<< orphan*/  wmv2_add_block (int /*<<< orphan*/ * const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

void ff_wmv2_add_mb(MpegEncContext *s, int16_t block1[6][64],
                    uint8_t *dest_y, uint8_t *dest_cb, uint8_t *dest_cr)
{
    Wmv2Context *const w = (Wmv2Context *) s;

    wmv2_add_block(w, block1[0], dest_y,                       s->linesize, 0);
    wmv2_add_block(w, block1[1], dest_y + 8,                   s->linesize, 1);
    wmv2_add_block(w, block1[2], dest_y + 8 * s->linesize,     s->linesize, 2);
    wmv2_add_block(w, block1[3], dest_y + 8 + 8 * s->linesize, s->linesize, 3);

    if (s->avctx->flags & AV_CODEC_FLAG_GRAY)
        return;

    wmv2_add_block(w, block1[4], dest_cb, s->uvlinesize, 4);
    wmv2_add_block(w, block1[5], dest_cr, s->uvlinesize, 5);
}