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
struct TYPE_6__ {scalar_t__ extended_data; int /*<<< orphan*/  nb_samples; } ;
struct TYPE_5__ {int size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  SAMPLES_PER_FRAME ; 
 int al_decode_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,float**) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int ff_get_buffer (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atrac3al_decode_frame(AVCodecContext *avctx, void *data,
                                 int *got_frame_ptr, AVPacket *avpkt)
{
    AVFrame *frame = data;
    int ret;

    frame->nb_samples = SAMPLES_PER_FRAME;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;

    ret = al_decode_frame(avctx, avpkt->data, avpkt->size,
                          (float **)frame->extended_data);
    if (ret) {
        av_log(avctx, AV_LOG_ERROR, "Frame decoding error!\n");
        return ret;
    }

    *got_frame_ptr = 1;

    return avpkt->size;
}