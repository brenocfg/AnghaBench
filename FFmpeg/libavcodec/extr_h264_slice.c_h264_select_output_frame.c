#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_13__ {scalar_t__ strict_std_compliance; int has_b_frames; int frame_number; int flags; int flags2; } ;
struct TYPE_8__ {TYPE_3__* sps; } ;
struct TYPE_12__ {int mmco_reset; scalar_t__* last_pocs; scalar_t__ next_outputed_poc; int frame_recovered; TYPE_7__* avctx; TYPE_4__* next_output_pic; TYPE_4__** delayed_pic; TYPE_4__* cur_pic_ptr; TYPE_1__ ps; } ;
struct TYPE_11__ {int mmco_reset; scalar_t__ poc; scalar_t__ reference; int recovered; TYPE_2__* f; } ;
struct TYPE_10__ {int num_reorder_frames; scalar_t__ bitstream_restriction_flag; } ;
struct TYPE_9__ {scalar_t__ pict_type; int /*<<< orphan*/  flags; scalar_t__ key_frame; } ;
typedef  TYPE_3__ SPS ;
typedef  TYPE_4__ H264Picture ;
typedef  TYPE_5__ H264Context ;

/* Variables and functions */
 int AV_CODEC_FLAG2_SHOW_ALL ; 
 int AV_CODEC_FLAG_OUTPUT_CORRUPT ; 
 int /*<<< orphan*/  AV_FRAME_FLAG_CORRUPT ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int AV_LOG_VERBOSE ; 
 int AV_LOG_WARNING ; 
 scalar_t__ AV_PICTURE_TYPE_B ; 
 scalar_t__ DELAYED_PIC_REF ; 
 void* FFMAX (int,int) ; 
 scalar_t__ FF_COMPLIANCE_STRICT ; 
 int FRAME_RECOVERED_SEI ; 
 scalar_t__ INT_MIN ; 
 int MAX_DELAYED_PIC_COUNT ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int,char*,...) ; 

__attribute__((used)) static int h264_select_output_frame(H264Context *h)
{
    const SPS *sps = h->ps.sps;
    H264Picture *out = h->cur_pic_ptr;
    H264Picture *cur = h->cur_pic_ptr;
    int i, pics, out_of_order, out_idx;

    cur->mmco_reset = h->mmco_reset;
    h->mmco_reset = 0;

    if (sps->bitstream_restriction_flag ||
        h->avctx->strict_std_compliance >= FF_COMPLIANCE_STRICT) {
        h->avctx->has_b_frames = FFMAX(h->avctx->has_b_frames, sps->num_reorder_frames);
    }

    for (i = 0; 1; i++) {
        if(i == MAX_DELAYED_PIC_COUNT || cur->poc < h->last_pocs[i]){
            if(i)
                h->last_pocs[i-1] = cur->poc;
            break;
        } else if(i) {
            h->last_pocs[i-1]= h->last_pocs[i];
        }
    }
    out_of_order = MAX_DELAYED_PIC_COUNT - i;
    if(   cur->f->pict_type == AV_PICTURE_TYPE_B
       || (h->last_pocs[MAX_DELAYED_PIC_COUNT-2] > INT_MIN && h->last_pocs[MAX_DELAYED_PIC_COUNT-1] - (int64_t)h->last_pocs[MAX_DELAYED_PIC_COUNT-2] > 2))
        out_of_order = FFMAX(out_of_order, 1);
    if (out_of_order == MAX_DELAYED_PIC_COUNT) {
        av_log(h->avctx, AV_LOG_VERBOSE, "Invalid POC %d<%d\n", cur->poc, h->last_pocs[0]);
        for (i = 1; i < MAX_DELAYED_PIC_COUNT; i++)
            h->last_pocs[i] = INT_MIN;
        h->last_pocs[0] = cur->poc;
        cur->mmco_reset = 1;
    } else if(h->avctx->has_b_frames < out_of_order && !sps->bitstream_restriction_flag){
        int loglevel = h->avctx->frame_number > 1 ? AV_LOG_WARNING : AV_LOG_VERBOSE;
        av_log(h->avctx, loglevel, "Increasing reorder buffer to %d\n", out_of_order);
        h->avctx->has_b_frames = out_of_order;
    }

    pics = 0;
    while (h->delayed_pic[pics])
        pics++;

    av_assert0(pics <= MAX_DELAYED_PIC_COUNT);

    h->delayed_pic[pics++] = cur;
    if (cur->reference == 0)
        cur->reference = DELAYED_PIC_REF;

    out     = h->delayed_pic[0];
    out_idx = 0;
    for (i = 1; h->delayed_pic[i] &&
                !h->delayed_pic[i]->f->key_frame &&
                !h->delayed_pic[i]->mmco_reset;
         i++)
        if (h->delayed_pic[i]->poc < out->poc) {
            out     = h->delayed_pic[i];
            out_idx = i;
        }
    if (h->avctx->has_b_frames == 0 &&
        (h->delayed_pic[0]->f->key_frame || h->delayed_pic[0]->mmco_reset))
        h->next_outputed_poc = INT_MIN;
    out_of_order = out->poc < h->next_outputed_poc;

    if (out_of_order || pics > h->avctx->has_b_frames) {
        out->reference &= ~DELAYED_PIC_REF;
        for (i = out_idx; h->delayed_pic[i]; i++)
            h->delayed_pic[i] = h->delayed_pic[i + 1];
    }
    if (!out_of_order && pics > h->avctx->has_b_frames) {
        h->next_output_pic = out;
        if (out_idx == 0 && h->delayed_pic[0] && (h->delayed_pic[0]->f->key_frame || h->delayed_pic[0]->mmco_reset)) {
            h->next_outputed_poc = INT_MIN;
        } else
            h->next_outputed_poc = out->poc;

        if (out->recovered) {
            // We have reached an recovery point and all frames after it in
            // display order are "recovered".
            h->frame_recovered |= FRAME_RECOVERED_SEI;
        }
        out->recovered |= !!(h->frame_recovered & FRAME_RECOVERED_SEI);

        if (!out->recovered) {
            if (!(h->avctx->flags & AV_CODEC_FLAG_OUTPUT_CORRUPT) &&
                !(h->avctx->flags2 & AV_CODEC_FLAG2_SHOW_ALL)) {
                h->next_output_pic = NULL;
            } else {
                out->f->flags |= AV_FRAME_FLAG_CORRUPT;
            }
        }
    } else {
        av_log(h->avctx, AV_LOG_DEBUG, "no picture %s\n", out_of_order ? "ooo" : "");
    }

    return 0;
}