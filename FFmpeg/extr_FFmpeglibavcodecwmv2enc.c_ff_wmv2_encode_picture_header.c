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
struct TYPE_5__ {int per_mb_abt; int abt_type; int j_type; scalar_t__ per_mb_rl_bit; scalar_t__ abt_flag; scalar_t__ mspel_bit; int /*<<< orphan*/  cbp_table_index; scalar_t__ j_type_bit; } ;
typedef  TYPE_1__ Wmv2Context ;
struct TYPE_6__ {int pict_type; int qscale; int dc_table_index; int mv_table_index; int per_mb_rl_table; int mspel; int flipflop_rounding; int no_rounding; int rl_chroma_table_index; int rl_table_index; scalar_t__ esc3_run_length; scalar_t__ esc3_level_length; scalar_t__ inter_intra_pred; int /*<<< orphan*/  pb; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ AV_PICTURE_TYPE_I ; 
 int SKIP_TYPE_NONE ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  ff_msmpeg4_code012 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  wmv2_get_cbp_table_index (TYPE_2__*,int) ; 

int ff_wmv2_encode_picture_header(MpegEncContext *s, int picture_number)
{
    Wmv2Context *const w = (Wmv2Context *) s;

    put_bits(&s->pb, 1, s->pict_type - 1);
    if (s->pict_type == AV_PICTURE_TYPE_I)
        put_bits(&s->pb, 7, 0);
    put_bits(&s->pb, 5, s->qscale);

    s->dc_table_index  = 1;
    s->mv_table_index  = 1; /* only if P-frame */
    s->per_mb_rl_table = 0;
    s->mspel           = 0;
    w->per_mb_abt      = 0;
    w->abt_type        = 0;
    w->j_type          = 0;

    av_assert0(s->flipflop_rounding);

    if (s->pict_type == AV_PICTURE_TYPE_I) {
        av_assert0(s->no_rounding == 1);
        if (w->j_type_bit)
            put_bits(&s->pb, 1, w->j_type);

        if (w->per_mb_rl_bit)
            put_bits(&s->pb, 1, s->per_mb_rl_table);

        if (!s->per_mb_rl_table) {
            ff_msmpeg4_code012(&s->pb, s->rl_chroma_table_index);
            ff_msmpeg4_code012(&s->pb, s->rl_table_index);
        }

        put_bits(&s->pb, 1, s->dc_table_index);

        s->inter_intra_pred = 0;
    } else {
        int cbp_index;

        put_bits(&s->pb, 2, SKIP_TYPE_NONE);

        ff_msmpeg4_code012(&s->pb, cbp_index = 0);
        w->cbp_table_index = wmv2_get_cbp_table_index(s, cbp_index);

        if (w->mspel_bit)
            put_bits(&s->pb, 1, s->mspel);

        if (w->abt_flag) {
            put_bits(&s->pb, 1, w->per_mb_abt ^ 1);
            if (!w->per_mb_abt)
                ff_msmpeg4_code012(&s->pb, w->abt_type);
        }

        if (w->per_mb_rl_bit)
            put_bits(&s->pb, 1, s->per_mb_rl_table);

        if (!s->per_mb_rl_table) {
            ff_msmpeg4_code012(&s->pb, s->rl_table_index);
            s->rl_chroma_table_index = s->rl_table_index;
        }
        put_bits(&s->pb, 1, s->dc_table_index);
        put_bits(&s->pb, 1, s->mv_table_index);

        s->inter_intra_pred = 0; // (s->width * s->height < 320 * 240 && s->bit_rate <= II_BITRATE);
    }
    s->esc3_level_length = 0;
    s->esc3_run_length   = 0;

    return 0;
}