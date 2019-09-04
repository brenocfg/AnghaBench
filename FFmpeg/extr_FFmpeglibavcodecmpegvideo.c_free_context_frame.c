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
struct TYPE_4__ {int /*<<< orphan*/  er_temp_buffer; int /*<<< orphan*/  error_status_table; } ;
struct TYPE_5__ {scalar_t__ uvlinesize; scalar_t__ linesize; int /*<<< orphan*/  bits_tab; int /*<<< orphan*/  cplx_tab; int /*<<< orphan*/  lambda_table; int /*<<< orphan*/  mb_index2xy; TYPE_1__ er; int /*<<< orphan*/  mbskip_table; int /*<<< orphan*/  pred_dir_table; int /*<<< orphan*/  cbp_table; int /*<<< orphan*/  mbintra_table; int /*<<< orphan*/  coded_block_base; int /*<<< orphan*/  dc_val_base; int /*<<< orphan*/ * p_field_select_table; int /*<<< orphan*/ *** p_field_mv_table; int /*<<< orphan*/ ** p_field_mv_table_base; int /*<<< orphan*/ ** b_field_select_table; int /*<<< orphan*/ **** b_field_mv_table; int /*<<< orphan*/ *** b_field_mv_table_base; int /*<<< orphan*/ * b_direct_mv_table; int /*<<< orphan*/ * b_bidir_back_mv_table; int /*<<< orphan*/ * b_bidir_forw_mv_table; int /*<<< orphan*/ * b_back_mv_table; int /*<<< orphan*/ * b_forw_mv_table; int /*<<< orphan*/ * p_mv_table; int /*<<< orphan*/  b_direct_mv_table_base; int /*<<< orphan*/  b_bidir_back_mv_table_base; int /*<<< orphan*/  b_bidir_forw_mv_table_base; int /*<<< orphan*/  b_back_mv_table_base; int /*<<< orphan*/  b_forw_mv_table_base; int /*<<< orphan*/  p_mv_table_base; int /*<<< orphan*/  mb_type; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_context_frame(MpegEncContext *s)
{
    int i, j, k;

    av_freep(&s->mb_type);
    av_freep(&s->p_mv_table_base);
    av_freep(&s->b_forw_mv_table_base);
    av_freep(&s->b_back_mv_table_base);
    av_freep(&s->b_bidir_forw_mv_table_base);
    av_freep(&s->b_bidir_back_mv_table_base);
    av_freep(&s->b_direct_mv_table_base);
    s->p_mv_table            = NULL;
    s->b_forw_mv_table       = NULL;
    s->b_back_mv_table       = NULL;
    s->b_bidir_forw_mv_table = NULL;
    s->b_bidir_back_mv_table = NULL;
    s->b_direct_mv_table     = NULL;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            for (k = 0; k < 2; k++) {
                av_freep(&s->b_field_mv_table_base[i][j][k]);
                s->b_field_mv_table[i][j][k] = NULL;
            }
            av_freep(&s->b_field_select_table[i][j]);
            av_freep(&s->p_field_mv_table_base[i][j]);
            s->p_field_mv_table[i][j] = NULL;
        }
        av_freep(&s->p_field_select_table[i]);
    }

    av_freep(&s->dc_val_base);
    av_freep(&s->coded_block_base);
    av_freep(&s->mbintra_table);
    av_freep(&s->cbp_table);
    av_freep(&s->pred_dir_table);

    av_freep(&s->mbskip_table);

    av_freep(&s->er.error_status_table);
    av_freep(&s->er.er_temp_buffer);
    av_freep(&s->mb_index2xy);
    av_freep(&s->lambda_table);

    av_freep(&s->cplx_tab);
    av_freep(&s->bits_tab);

    s->linesize = s->uvlinesize = 0;
}