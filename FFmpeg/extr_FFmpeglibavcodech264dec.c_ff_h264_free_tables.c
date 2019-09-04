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
struct TYPE_7__ {int nb_slice_ctx; TYPE_2__* slice_ctx; int /*<<< orphan*/  ref_index_pool; int /*<<< orphan*/  motion_val_pool; int /*<<< orphan*/  mb_type_pool; int /*<<< orphan*/  qscale_table_pool; int /*<<< orphan*/  mb2br_xy; int /*<<< orphan*/  mb2b_xy; int /*<<< orphan*/  list_counts; int /*<<< orphan*/ * slice_table; int /*<<< orphan*/  slice_table_base; int /*<<< orphan*/  non_zero_count; int /*<<< orphan*/  direct_table; int /*<<< orphan*/ * mvd_table; int /*<<< orphan*/  cbp_table; int /*<<< orphan*/  chroma_pred_mode_table; int /*<<< orphan*/  intra4x4_pred_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  er_temp_buffer; int /*<<< orphan*/  error_status_table; int /*<<< orphan*/  mb_index2xy; } ;
struct TYPE_6__ {scalar_t__* top_borders_allocated; scalar_t__ edge_emu_buffer_allocated; scalar_t__ bipred_scratchpad_allocated; int /*<<< orphan*/ * top_borders; int /*<<< orphan*/  edge_emu_buffer; int /*<<< orphan*/  bipred_scratchpad; TYPE_1__ er; int /*<<< orphan*/  dc_val_base; } ;
typedef  TYPE_2__ H264SliceContext ;
typedef  TYPE_3__ H264Context ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_pool_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

void ff_h264_free_tables(H264Context *h)
{
    int i;

    av_freep(&h->intra4x4_pred_mode);
    av_freep(&h->chroma_pred_mode_table);
    av_freep(&h->cbp_table);
    av_freep(&h->mvd_table[0]);
    av_freep(&h->mvd_table[1]);
    av_freep(&h->direct_table);
    av_freep(&h->non_zero_count);
    av_freep(&h->slice_table_base);
    h->slice_table = NULL;
    av_freep(&h->list_counts);

    av_freep(&h->mb2b_xy);
    av_freep(&h->mb2br_xy);

    av_buffer_pool_uninit(&h->qscale_table_pool);
    av_buffer_pool_uninit(&h->mb_type_pool);
    av_buffer_pool_uninit(&h->motion_val_pool);
    av_buffer_pool_uninit(&h->ref_index_pool);

    for (i = 0; i < h->nb_slice_ctx; i++) {
        H264SliceContext *sl = &h->slice_ctx[i];

        av_freep(&sl->dc_val_base);
        av_freep(&sl->er.mb_index2xy);
        av_freep(&sl->er.error_status_table);
        av_freep(&sl->er.er_temp_buffer);

        av_freep(&sl->bipred_scratchpad);
        av_freep(&sl->edge_emu_buffer);
        av_freep(&sl->top_borders[0]);
        av_freep(&sl->top_borders[1]);

        sl->bipred_scratchpad_allocated = 0;
        sl->edge_emu_buffer_allocated   = 0;
        sl->top_borders_allocated[0]    = 0;
        sl->top_borders_allocated[1]    = 0;
    }
}