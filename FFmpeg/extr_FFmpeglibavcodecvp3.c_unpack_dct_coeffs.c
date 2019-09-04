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
struct TYPE_7__ {int /*<<< orphan*/ * ac_vlc_4; int /*<<< orphan*/ * ac_vlc_3; int /*<<< orphan*/ * ac_vlc_2; int /*<<< orphan*/ * ac_vlc_1; int /*<<< orphan*/ * fragment_height; int /*<<< orphan*/ * fragment_width; int /*<<< orphan*/ * fragment_start; TYPE_1__* avctx; int /*<<< orphan*/ * dc_vlc; int /*<<< orphan*/  dct_tokens_base; int /*<<< orphan*/ ** dct_tokens; } ;
typedef  TYPE_2__ Vp3DecodeContext ;
typedef  int /*<<< orphan*/  VLC ;
struct TYPE_6__ {int flags; } ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_CODEC_FLAG_GRAY ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reverse_dc_prediction (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int unpack_vlcs (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static int unpack_dct_coeffs(Vp3DecodeContext *s, GetBitContext *gb)
{
    int i;
    int dc_y_table;
    int dc_c_table;
    int ac_y_table;
    int ac_c_table;
    int residual_eob_run = 0;
    VLC *y_tables[64];
    VLC *c_tables[64];

    s->dct_tokens[0][0] = s->dct_tokens_base;

    if (get_bits_left(gb) < 16)
        return AVERROR_INVALIDDATA;

    /* fetch the DC table indexes */
    dc_y_table = get_bits(gb, 4);
    dc_c_table = get_bits(gb, 4);

    /* unpack the Y plane DC coefficients */
    residual_eob_run = unpack_vlcs(s, gb, &s->dc_vlc[dc_y_table], 0,
                                   0, residual_eob_run);
    if (residual_eob_run < 0)
        return residual_eob_run;
    if (get_bits_left(gb) < 8)
        return AVERROR_INVALIDDATA;

    /* reverse prediction of the Y-plane DC coefficients */
    reverse_dc_prediction(s, 0, s->fragment_width[0], s->fragment_height[0]);

    /* unpack the C plane DC coefficients */
    residual_eob_run = unpack_vlcs(s, gb, &s->dc_vlc[dc_c_table], 0,
                                   1, residual_eob_run);
    if (residual_eob_run < 0)
        return residual_eob_run;
    residual_eob_run = unpack_vlcs(s, gb, &s->dc_vlc[dc_c_table], 0,
                                   2, residual_eob_run);
    if (residual_eob_run < 0)
        return residual_eob_run;

    /* reverse prediction of the C-plane DC coefficients */
    if (!(s->avctx->flags & AV_CODEC_FLAG_GRAY)) {
        reverse_dc_prediction(s, s->fragment_start[1],
                              s->fragment_width[1], s->fragment_height[1]);
        reverse_dc_prediction(s, s->fragment_start[2],
                              s->fragment_width[1], s->fragment_height[1]);
    }

    if (get_bits_left(gb) < 8)
        return AVERROR_INVALIDDATA;
    /* fetch the AC table indexes */
    ac_y_table = get_bits(gb, 4);
    ac_c_table = get_bits(gb, 4);

    /* build tables of AC VLC tables */
    for (i = 1; i <= 5; i++) {
        y_tables[i] = &s->ac_vlc_1[ac_y_table];
        c_tables[i] = &s->ac_vlc_1[ac_c_table];
    }
    for (i = 6; i <= 14; i++) {
        y_tables[i] = &s->ac_vlc_2[ac_y_table];
        c_tables[i] = &s->ac_vlc_2[ac_c_table];
    }
    for (i = 15; i <= 27; i++) {
        y_tables[i] = &s->ac_vlc_3[ac_y_table];
        c_tables[i] = &s->ac_vlc_3[ac_c_table];
    }
    for (i = 28; i <= 63; i++) {
        y_tables[i] = &s->ac_vlc_4[ac_y_table];
        c_tables[i] = &s->ac_vlc_4[ac_c_table];
    }

    /* decode all AC coefficients */
    for (i = 1; i <= 63; i++) {
        residual_eob_run = unpack_vlcs(s, gb, y_tables[i], i,
                                       0, residual_eob_run);
        if (residual_eob_run < 0)
            return residual_eob_run;

        residual_eob_run = unpack_vlcs(s, gb, c_tables[i], i,
                                       1, residual_eob_run);
        if (residual_eob_run < 0)
            return residual_eob_run;
        residual_eob_run = unpack_vlcs(s, gb, c_tables[i], i,
                                       2, residual_eob_run);
        if (residual_eob_run < 0)
            return residual_eob_run;
    }

    return 0;
}