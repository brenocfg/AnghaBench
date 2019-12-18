#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_3__* sps; } ;
struct TYPE_11__ {int no_output_of_prior_pics_flag; } ;
struct TYPE_16__ {int no_rasl_output_flag; scalar_t__ poc; scalar_t__ seq_output; scalar_t__ seq_decode; int /*<<< orphan*/  avctx; TYPE_5__* DPB; TYPE_4__ ps; TYPE_1__ sh; } ;
struct TYPE_15__ {int flags; scalar_t__ poc; scalar_t__ sequence; int /*<<< orphan*/  frame; } ;
struct TYPE_13__ {int max_sub_layers; TYPE_2__* temporal_layer; } ;
struct TYPE_12__ {int num_reorder_pics; } ;
typedef  TYPE_5__ HEVCFrame ;
typedef  TYPE_6__ HEVCContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int FF_ARRAY_ELEMS (TYPE_5__*) ; 
 int HEVC_FRAME_FLAG_BUMPING ; 
 int HEVC_FRAME_FLAG_OUTPUT ; 
 int INT_MAX ; 
 int av_frame_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ff_hevc_unref_frame (TYPE_6__*,TYPE_5__*,int) ; 

int ff_hevc_output_frame(HEVCContext *s, AVFrame *out, int flush)
{
    do {
        int nb_output = 0;
        int min_poc   = INT_MAX;
        int i, min_idx, ret;

        if (s->sh.no_output_of_prior_pics_flag == 1 && s->no_rasl_output_flag == 1) {
            for (i = 0; i < FF_ARRAY_ELEMS(s->DPB); i++) {
                HEVCFrame *frame = &s->DPB[i];
                if (!(frame->flags & HEVC_FRAME_FLAG_BUMPING) && frame->poc != s->poc &&
                        frame->sequence == s->seq_output) {
                    ff_hevc_unref_frame(s, frame, HEVC_FRAME_FLAG_OUTPUT);
                }
            }
        }

        for (i = 0; i < FF_ARRAY_ELEMS(s->DPB); i++) {
            HEVCFrame *frame = &s->DPB[i];
            if ((frame->flags & HEVC_FRAME_FLAG_OUTPUT) &&
                frame->sequence == s->seq_output) {
                nb_output++;
                if (frame->poc < min_poc || nb_output == 1) {
                    min_poc = frame->poc;
                    min_idx = i;
                }
            }
        }

        /* wait for more frames before output */
        if (!flush && s->seq_output == s->seq_decode && s->ps.sps &&
            nb_output <= s->ps.sps->temporal_layer[s->ps.sps->max_sub_layers - 1].num_reorder_pics)
            return 0;

        if (nb_output) {
            HEVCFrame *frame = &s->DPB[min_idx];

            ret = av_frame_ref(out, frame->frame);
            if (frame->flags & HEVC_FRAME_FLAG_BUMPING)
                ff_hevc_unref_frame(s, frame, HEVC_FRAME_FLAG_OUTPUT | HEVC_FRAME_FLAG_BUMPING);
            else
                ff_hevc_unref_frame(s, frame, HEVC_FRAME_FLAG_OUTPUT);
            if (ret < 0)
                return ret;

            av_log(s->avctx, AV_LOG_DEBUG,
                   "Output frame with POC %d.\n", frame->poc);
            return 1;
        }

        if (s->seq_output != s->seq_decode)
            s->seq_output = (s->seq_output + 1) & 0xff;
        else
            break;
    } while (1);

    return 0;
}