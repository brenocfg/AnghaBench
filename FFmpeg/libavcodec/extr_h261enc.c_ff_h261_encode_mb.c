#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_9__ {int mtype; } ;
struct TYPE_8__ {size_t mb_skip_run; int*** last_mv; int qscale; int dquant; int /*<<< orphan*/  pb; scalar_t__ loop_filter; int /*<<< orphan*/  mb_intra; int /*<<< orphan*/  skip_count; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  TYPE_2__ H261Context ;

/* Variables and functions */
 scalar_t__ HAS_CBP (size_t) ; 
 scalar_t__ IS_16X16 (size_t) ; 
 scalar_t__ IS_QUANT (size_t) ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int** ff_h261_cbp_tab ; 
 int* ff_h261_mba_bits ; 
 int* ff_h261_mba_code ; 
 int* ff_h261_mtype_bits ; 
 int* ff_h261_mtype_code ; 
 size_t* ff_h261_mtype_map ; 
 int /*<<< orphan*/  ff_set_qscale (TYPE_1__*,int) ; 
 int get_cbp (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  h261_encode_block (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  h261_encode_motion (TYPE_2__*,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

void ff_h261_encode_mb(MpegEncContext *s, int16_t block[6][64],
                       int motion_x, int motion_y)
{
    H261Context *h = (H261Context *)s;
    int mvd, mv_diff_x, mv_diff_y, i, cbp;
    cbp = 63; // avoid warning
    mvd = 0;

    h->mtype = 0;

    if (!s->mb_intra) {
        /* compute cbp */
        cbp = get_cbp(s, block);

        /* mvd indicates if this block is motion compensated */
        mvd = motion_x | motion_y;

        if ((cbp | mvd) == 0) {
            /* skip macroblock */
            s->skip_count++;
            s->mb_skip_run++;
            s->last_mv[0][0][0] = 0;
            s->last_mv[0][0][1] = 0;
            s->qscale -= s->dquant;
            return;
        }
    }

    /* MB is not skipped, encode MBA */
    put_bits(&s->pb,
             ff_h261_mba_bits[s->mb_skip_run],
             ff_h261_mba_code[s->mb_skip_run]);
    s->mb_skip_run = 0;

    /* calculate MTYPE */
    if (!s->mb_intra) {
        h->mtype++;

        if (mvd || s->loop_filter)
            h->mtype += 3;
        if (s->loop_filter)
            h->mtype += 3;
        if (cbp)
            h->mtype++;
        av_assert1(h->mtype > 1);
    }

    if (s->dquant && cbp) {
        h->mtype++;
    } else
        s->qscale -= s->dquant;

    put_bits(&s->pb,
             ff_h261_mtype_bits[h->mtype],
             ff_h261_mtype_code[h->mtype]);

    h->mtype = ff_h261_mtype_map[h->mtype];

    if (IS_QUANT(h->mtype)) {
        ff_set_qscale(s, s->qscale + s->dquant);
        put_bits(&s->pb, 5, s->qscale);
    }

    if (IS_16X16(h->mtype)) {
        mv_diff_x       = (motion_x >> 1) - s->last_mv[0][0][0];
        mv_diff_y       = (motion_y >> 1) - s->last_mv[0][0][1];
        s->last_mv[0][0][0] = (motion_x >> 1);
        s->last_mv[0][0][1] = (motion_y >> 1);
        h261_encode_motion(h, mv_diff_x);
        h261_encode_motion(h, mv_diff_y);
    }

    if (HAS_CBP(h->mtype)) {
        av_assert1(cbp > 0);
        put_bits(&s->pb,
                 ff_h261_cbp_tab[cbp - 1][1],
                 ff_h261_cbp_tab[cbp - 1][0]);
    }
    for (i = 0; i < 6; i++)
        /* encode each block */
        h261_encode_block(h, block[i], i);

    if (!IS_16X16(h->mtype)) {
        s->last_mv[0][0][0] = 0;
        s->last_mv[0][0][1] = 0;
    }
}