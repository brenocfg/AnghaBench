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
struct TYPE_7__ {TYPE_1__* priv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  out_frame; int /*<<< orphan*/  decoder; int /*<<< orphan*/  headerset; } ;
typedef  TYPE_1__ DAVS2Context ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int DAVS2_DEFAULT ; 
 int DAVS2_ERROR ; 
 int DAVS2_GOT_FRAME ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int davs2_decoder_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  davs2_decoder_frame_unref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int davs2_dump_frames (TYPE_2__*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int send_delayed_frame(AVCodecContext *avctx, AVFrame *frame, int *got_frame)
{
    DAVS2Context *cad      = avctx->priv_data;
    int           ret      = DAVS2_DEFAULT;

    ret = davs2_decoder_flush(cad->decoder, &cad->headerset, &cad->out_frame);
    if (ret == DAVS2_ERROR) {
        av_log(avctx, AV_LOG_ERROR, "Decoder error: can't flush delayed frame\n");
        return AVERROR_EXTERNAL;
    }
    if (ret == DAVS2_GOT_FRAME) {
        ret = davs2_dump_frames(avctx, &cad->out_frame, got_frame, &cad->headerset, ret, frame);
        davs2_decoder_frame_unref(cad->decoder, &cad->out_frame);
    }
    return ret;
}