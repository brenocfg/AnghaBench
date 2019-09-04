#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct xvmc_pix_fmt {scalar_t__ xvmc_id; int allocated_mv_blocks; int const allocated_data_blocks; int const start_mv_blocks_num; int const next_free_data_block_num; int /*<<< orphan*/ * p_surface; int /*<<< orphan*/ * p_past_surface; int /*<<< orphan*/ * p_future_surface; int /*<<< orphan*/  flags; int /*<<< orphan*/  picture_structure; scalar_t__ filled_mv_blocks_num; int /*<<< orphan*/  mv_blocks; int /*<<< orphan*/  data_blocks; } ;
struct TYPE_16__ {TYPE_5__* f; } ;
struct TYPE_14__ {TYPE_3__* f; } ;
struct TYPE_12__ {TYPE_1__* f; } ;
struct MpegEncContext {int chroma_format; int pict_type; TYPE_6__ last_picture; TYPE_4__ next_picture; scalar_t__ first_field; int /*<<< orphan*/  picture_structure; TYPE_2__ current_picture; } ;
struct TYPE_17__ {struct MpegEncContext* priv_data; } ;
struct TYPE_15__ {scalar_t__* data; } ;
struct TYPE_13__ {scalar_t__* data; } ;
struct TYPE_11__ {scalar_t__* data; } ;
typedef  TYPE_7__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  AV_PICTURE_TYPE_B 130 
#define  AV_PICTURE_TYPE_I 129 
#define  AV_PICTURE_TYPE_P 128 
 scalar_t__ AV_XVMC_ID ; 
 int INT_MAX ; 
 int /*<<< orphan*/  XVMC_SECOND_FIELD ; 
 int /*<<< orphan*/  assert (TYPE_7__*) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int ff_xvmc_field_start(AVCodecContext *avctx, const uint8_t *buf, uint32_t buf_size)
{
    struct MpegEncContext *s = avctx->priv_data;
    struct xvmc_pix_fmt *last, *next, *render = (struct xvmc_pix_fmt*)s->current_picture.f->data[2];
    const int mb_block_count = 4 + (1 << s->chroma_format);

    assert(avctx);
    if (!render || render->xvmc_id != AV_XVMC_ID ||
        !render->data_blocks || !render->mv_blocks ||
        (unsigned int)render->allocated_mv_blocks   > INT_MAX/(64*6) ||
        (unsigned int)render->allocated_data_blocks > INT_MAX/64     ||
        !render->p_surface) {
        av_log(avctx, AV_LOG_ERROR,
               "Render token doesn't look as expected.\n");
        return -1; // make sure that this is a render packet
    }

    if (render->filled_mv_blocks_num) {
        av_log(avctx, AV_LOG_ERROR,
               "Rendering surface contains %i unprocessed blocks.\n",
               render->filled_mv_blocks_num);
        return -1;
    }
    if (render->allocated_mv_blocks   < 1 ||
        render->allocated_data_blocks <  render->allocated_mv_blocks*mb_block_count ||
        render->start_mv_blocks_num   >= render->allocated_mv_blocks                ||
        render->next_free_data_block_num >
                        render->allocated_data_blocks -
                        mb_block_count*(render->allocated_mv_blocks-render->start_mv_blocks_num)) {
        av_log(avctx, AV_LOG_ERROR,
               "Rendering surface doesn't provide enough block structures to work with.\n");
        return -1;
    }

    render->picture_structure = s->picture_structure;
    render->flags             = s->first_field ? 0 : XVMC_SECOND_FIELD;
    render->p_future_surface  = NULL;
    render->p_past_surface    = NULL;

    switch(s->pict_type) {
        case  AV_PICTURE_TYPE_I:
            return 0; // no prediction from other frames
        case  AV_PICTURE_TYPE_B:
            next = (struct xvmc_pix_fmt*)s->next_picture.f->data[2];
            if (!next)
                return -1;
            if (next->xvmc_id != AV_XVMC_ID)
                return -1;
            render->p_future_surface = next->p_surface;
            // no return here, going to set forward prediction
        case  AV_PICTURE_TYPE_P:
            last = (struct xvmc_pix_fmt*)s->last_picture.f->data[2];
            if (!last)
                last = render; // predict second field from the first
            if (last->xvmc_id != AV_XVMC_ID)
                return -1;
            render->p_past_surface = last->p_surface;
            return 0;
    }

return -1;
}