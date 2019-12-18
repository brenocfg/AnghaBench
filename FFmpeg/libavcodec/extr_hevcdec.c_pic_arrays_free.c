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
struct TYPE_4__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  size; int /*<<< orphan*/  entry_point_offset; } ;
struct TYPE_5__ {int /*<<< orphan*/  rpl_tab_pool; int /*<<< orphan*/  tab_mvf_pool; TYPE_1__ sh; int /*<<< orphan*/  vertical_bs; int /*<<< orphan*/  horizontal_bs; int /*<<< orphan*/  filter_slice_edges; int /*<<< orphan*/  tab_slice_address; int /*<<< orphan*/  qp_y_tab; int /*<<< orphan*/  is_pcm; int /*<<< orphan*/  cbf_luma; int /*<<< orphan*/  tab_ipm; int /*<<< orphan*/  tab_ct_depth; int /*<<< orphan*/  skip_flag; int /*<<< orphan*/  deblock; int /*<<< orphan*/  sao; } ;
typedef  TYPE_2__ HEVCContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_pool_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pic_arrays_free(HEVCContext *s)
{
    av_freep(&s->sao);
    av_freep(&s->deblock);

    av_freep(&s->skip_flag);
    av_freep(&s->tab_ct_depth);

    av_freep(&s->tab_ipm);
    av_freep(&s->cbf_luma);
    av_freep(&s->is_pcm);

    av_freep(&s->qp_y_tab);
    av_freep(&s->tab_slice_address);
    av_freep(&s->filter_slice_edges);

    av_freep(&s->horizontal_bs);
    av_freep(&s->vertical_bs);

    av_freep(&s->sh.entry_point_offset);
    av_freep(&s->sh.size);
    av_freep(&s->sh.offset);

    av_buffer_pool_uninit(&s->tab_mvf_pool);
    av_buffer_pool_uninit(&s->rpl_tab_pool);
}