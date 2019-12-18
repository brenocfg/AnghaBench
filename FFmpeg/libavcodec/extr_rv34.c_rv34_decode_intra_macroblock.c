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
typedef  int /*<<< orphan*/  int8_t ;
struct TYPE_12__ {int mb_x; int mb_y; int mb_stride; int resync_mb_x; int resync_mb_y; int mb_width; int /*<<< orphan*/  qscale; TYPE_2__* current_picture_ptr; } ;
struct TYPE_9__ {int /*<<< orphan*/  quant; } ;
struct TYPE_11__ {int* cbp_luma; int* cbp_chroma; int* deblock_coefs; scalar_t__ is16; TYPE_1__ si; int /*<<< orphan*/ * avail_cache; TYPE_4__ s; } ;
struct TYPE_10__ {int /*<<< orphan*/ * qscale_table; int /*<<< orphan*/ * mb_type; } ;
typedef  TYPE_3__ RV34DecContext ;
typedef  TYPE_4__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  fill_rectangle (int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int rv34_decode_intra_mb_header (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rv34_output_i16x16 (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rv34_output_intra (TYPE_3__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rv34_decode_intra_macroblock(RV34DecContext *r, int8_t *intra_types)
{
    MpegEncContext *s = &r->s;
    int cbp, dist;
    int mb_pos = s->mb_x + s->mb_y * s->mb_stride;

    // Calculate which neighbours are available. Maybe it's worth optimizing too.
    memset(r->avail_cache, 0, sizeof(r->avail_cache));
    fill_rectangle(r->avail_cache + 6, 2, 2, 4, 1, 4);
    dist = (s->mb_x - s->resync_mb_x) + (s->mb_y - s->resync_mb_y) * s->mb_width;
    if(s->mb_x && dist)
        r->avail_cache[5] =
        r->avail_cache[9] = s->current_picture_ptr->mb_type[mb_pos - 1];
    if(dist >= s->mb_width)
        r->avail_cache[2] =
        r->avail_cache[3] = s->current_picture_ptr->mb_type[mb_pos - s->mb_stride];
    if(((s->mb_x+1) < s->mb_width) && dist >= s->mb_width - 1)
        r->avail_cache[4] = s->current_picture_ptr->mb_type[mb_pos - s->mb_stride + 1];
    if(s->mb_x && dist > s->mb_width)
        r->avail_cache[1] = s->current_picture_ptr->mb_type[mb_pos - s->mb_stride - 1];

    s->qscale = r->si.quant;
    cbp = rv34_decode_intra_mb_header(r, intra_types);
    r->cbp_luma  [mb_pos] = cbp;
    r->cbp_chroma[mb_pos] = cbp >> 16;
    r->deblock_coefs[mb_pos] = 0xFFFF;
    s->current_picture_ptr->qscale_table[mb_pos] = s->qscale;

    if(cbp == -1)
        return -1;

    if(r->is16){
        rv34_output_i16x16(r, intra_types, cbp);
        return 0;
    }

    rv34_output_intra(r, intra_types, cbp);
    return 0;
}