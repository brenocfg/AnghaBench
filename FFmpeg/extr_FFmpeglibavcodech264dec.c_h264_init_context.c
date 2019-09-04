#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct TYPE_22__ {int active_thread_type; int thread_count; int /*<<< orphan*/  chroma_sample_location; int /*<<< orphan*/  flags; int /*<<< orphan*/  workaround_bugs; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_20__ {void* f; } ;
struct TYPE_19__ {void* f; } ;
struct TYPE_17__ {int x264_build; } ;
struct TYPE_16__ {int arrangement_cancel_flag; } ;
struct TYPE_13__ {TYPE_3__ unregistered; TYPE_2__ frame_packing; } ;
struct TYPE_15__ {int prev_poc_msb; int prev_frame_num; } ;
struct TYPE_21__ {int cur_chroma_format_idc; int recovery_frame; int nb_slice_ctx; TYPE_12__* slice_ctx; TYPE_6__ last_pic_for_ec; TYPE_5__ cur_pic; TYPE_4__* DPB; TYPE_11__ sei; void** last_pocs; void* next_outputed_poc; TYPE_1__ poc; scalar_t__ frame_recovered; int /*<<< orphan*/  flags; int /*<<< orphan*/  workaround_bugs; int /*<<< orphan*/  picture_structure; int /*<<< orphan*/  height_from_caller; int /*<<< orphan*/  width_from_caller; TYPE_8__* avctx; } ;
struct TYPE_18__ {void* f; } ;
struct TYPE_14__ {TYPE_7__* h264; } ;
typedef  TYPE_7__ H264Context ;
typedef  TYPE_8__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVCHROMA_LOC_LEFT ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FF_THREAD_SLICE ; 
 int H264_MAX_PICTURE_COUNT ; 
 void* INT_MIN ; 
 int MAX_DELAYED_PIC_COUNT ; 
 int /*<<< orphan*/  PICT_FRAME ; 
 void* av_frame_alloc () ; 
 TYPE_12__* av_mallocz_array (int,int) ; 
 int /*<<< orphan*/  ff_h264_sei_uninit (TYPE_11__*) ; 

__attribute__((used)) static int h264_init_context(AVCodecContext *avctx, H264Context *h)
{
    int i;

    h->avctx                 = avctx;
    h->cur_chroma_format_idc = -1;

    h->width_from_caller     = avctx->width;
    h->height_from_caller    = avctx->height;

    h->picture_structure     = PICT_FRAME;
    h->workaround_bugs       = avctx->workaround_bugs;
    h->flags                 = avctx->flags;
    h->poc.prev_poc_msb      = 1 << 16;
    h->recovery_frame        = -1;
    h->frame_recovered       = 0;
    h->poc.prev_frame_num    = -1;
    h->sei.frame_packing.arrangement_cancel_flag = -1;
    h->sei.unregistered.x264_build = -1;

    h->next_outputed_poc = INT_MIN;
    for (i = 0; i < MAX_DELAYED_PIC_COUNT; i++)
        h->last_pocs[i] = INT_MIN;

    ff_h264_sei_uninit(&h->sei);

    avctx->chroma_sample_location = AVCHROMA_LOC_LEFT;

    h->nb_slice_ctx = (avctx->active_thread_type & FF_THREAD_SLICE) ? avctx->thread_count : 1;
    h->slice_ctx = av_mallocz_array(h->nb_slice_ctx, sizeof(*h->slice_ctx));
    if (!h->slice_ctx) {
        h->nb_slice_ctx = 0;
        return AVERROR(ENOMEM);
    }

    for (i = 0; i < H264_MAX_PICTURE_COUNT; i++) {
        h->DPB[i].f = av_frame_alloc();
        if (!h->DPB[i].f)
            return AVERROR(ENOMEM);
    }

    h->cur_pic.f = av_frame_alloc();
    if (!h->cur_pic.f)
        return AVERROR(ENOMEM);

    h->last_pic_for_ec.f = av_frame_alloc();
    if (!h->last_pic_for_ec.f)
        return AVERROR(ENOMEM);

    for (i = 0; i < h->nb_slice_ctx; i++)
        h->slice_ctx[i].h264 = h;

    return 0;
}