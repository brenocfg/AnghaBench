#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * er_temp_buffer; int /*<<< orphan*/ * error_status_table; } ;
struct TYPE_7__ {int /*<<< orphan*/ * obmc_scratchpad; int /*<<< orphan*/  b_scratchpad; int /*<<< orphan*/  rd_scratchpad; int /*<<< orphan*/ * edge_emu_buffer; } ;
struct TYPE_6__ {int /*<<< orphan*/  temp; int /*<<< orphan*/ * scratchpad; int /*<<< orphan*/ * score_map; int /*<<< orphan*/ * map; } ;
struct TYPE_9__ {int /*<<< orphan*/ * bits_tab; int /*<<< orphan*/ * cplx_tab; int /*<<< orphan*/ * lambda_table; int /*<<< orphan*/ * mb_index2xy; TYPE_3__ er; int /*<<< orphan*/ * mbskip_table; int /*<<< orphan*/ * pred_dir_table; int /*<<< orphan*/ * cbp_table; int /*<<< orphan*/ * mbintra_table; int /*<<< orphan*/ * coded_block_base; int /*<<< orphan*/ * dc_val_base; int /*<<< orphan*/ ** p_field_select_table; int /*<<< orphan*/ *** p_field_mv_table; int /*<<< orphan*/ *** p_field_mv_table_base; int /*<<< orphan*/ *** b_field_select_table; int /*<<< orphan*/ **** b_field_mv_table; int /*<<< orphan*/ **** b_field_mv_table_base; int /*<<< orphan*/ * b_direct_mv_table; int /*<<< orphan*/ * b_bidir_back_mv_table; int /*<<< orphan*/ * b_bidir_forw_mv_table; int /*<<< orphan*/ * b_back_mv_table; int /*<<< orphan*/ * b_forw_mv_table; int /*<<< orphan*/ * p_mv_table; int /*<<< orphan*/ * b_direct_mv_table_base; int /*<<< orphan*/ * b_bidir_back_mv_table_base; int /*<<< orphan*/ * b_bidir_forw_mv_table_base; int /*<<< orphan*/ * b_back_mv_table_base; int /*<<< orphan*/ * b_forw_mv_table_base; int /*<<< orphan*/ * p_mv_table_base; int /*<<< orphan*/ * mb_type; int /*<<< orphan*/ * picture; scalar_t__ allocated_bitstream_buffer_size; int /*<<< orphan*/ * bitstream_buffer; TYPE_2__ sc; TYPE_1__ me; int /*<<< orphan*/ ** ac_val; int /*<<< orphan*/ * ac_val_base; int /*<<< orphan*/ * dpcm_macroblock; scalar_t__ dpcm_direction; int /*<<< orphan*/ * pblocks; int /*<<< orphan*/ * block32; int /*<<< orphan*/ * blocks; int /*<<< orphan*/ * block; int /*<<< orphan*/ * dct_error_sum; int /*<<< orphan*/ * thread_context; int /*<<< orphan*/  new_picture; int /*<<< orphan*/  current_picture; int /*<<< orphan*/  last_picture; int /*<<< orphan*/  next_picture; } ;
typedef  TYPE_4__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clear_context(MpegEncContext *s)
{
    int i, j, k;

    memset(&s->next_picture, 0, sizeof(s->next_picture));
    memset(&s->last_picture, 0, sizeof(s->last_picture));
    memset(&s->current_picture, 0, sizeof(s->current_picture));
    memset(&s->new_picture, 0, sizeof(s->new_picture));

    memset(s->thread_context, 0, sizeof(s->thread_context));

    s->me.map = NULL;
    s->me.score_map = NULL;
    s->dct_error_sum = NULL;
    s->block = NULL;
    s->blocks = NULL;
    s->block32 = NULL;
    memset(s->pblocks, 0, sizeof(s->pblocks));
    s->dpcm_direction = 0;
    s->dpcm_macroblock = NULL;
    s->ac_val_base = NULL;
    s->ac_val[0] =
    s->ac_val[1] =
    s->ac_val[2] =NULL;
    s->sc.edge_emu_buffer = NULL;
    s->me.scratchpad = NULL;
    s->me.temp =
    s->sc.rd_scratchpad =
    s->sc.b_scratchpad =
    s->sc.obmc_scratchpad = NULL;


    s->bitstream_buffer = NULL;
    s->allocated_bitstream_buffer_size = 0;
    s->picture          = NULL;
    s->mb_type          = NULL;
    s->p_mv_table_base  = NULL;
    s->b_forw_mv_table_base = NULL;
    s->b_back_mv_table_base = NULL;
    s->b_bidir_forw_mv_table_base = NULL;
    s->b_bidir_back_mv_table_base = NULL;
    s->b_direct_mv_table_base = NULL;
    s->p_mv_table            = NULL;
    s->b_forw_mv_table       = NULL;
    s->b_back_mv_table       = NULL;
    s->b_bidir_forw_mv_table = NULL;
    s->b_bidir_back_mv_table = NULL;
    s->b_direct_mv_table     = NULL;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            for (k = 0; k < 2; k++) {
                s->b_field_mv_table_base[i][j][k] = NULL;
                s->b_field_mv_table[i][j][k] = NULL;
            }
            s->b_field_select_table[i][j] = NULL;
            s->p_field_mv_table_base[i][j] = NULL;
            s->p_field_mv_table[i][j] = NULL;
        }
        s->p_field_select_table[i] = NULL;
    }

    s->dc_val_base = NULL;
    s->coded_block_base = NULL;
    s->mbintra_table = NULL;
    s->cbp_table = NULL;
    s->pred_dir_table = NULL;

    s->mbskip_table = NULL;

    s->er.error_status_table = NULL;
    s->er.er_temp_buffer = NULL;
    s->mb_index2xy = NULL;
    s->lambda_table = NULL;

    s->cplx_tab = NULL;
    s->bits_tab = NULL;
}