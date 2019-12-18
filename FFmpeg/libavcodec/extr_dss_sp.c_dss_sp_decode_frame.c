#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_11__ {int /*<<< orphan*/ * priv_data; } ;
struct TYPE_10__ {scalar_t__* data; int /*<<< orphan*/  nb_samples; } ;
struct TYPE_9__ {int size; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  DssSpContext ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int DSS_SP_FRAME_SIZE ; 
 int /*<<< orphan*/  DSS_SP_SAMPLE_COUNT ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dss_sp_decode_one_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int ff_get_buffer (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dss_sp_decode_frame(AVCodecContext *avctx, void *data,
                               int *got_frame_ptr, AVPacket *avpkt)
{
    DssSpContext *p    = avctx->priv_data;
    AVFrame *frame     = data;
    const uint8_t *buf = avpkt->data;
    int buf_size       = avpkt->size;

    int16_t *out;
    int ret;

    if (buf_size < DSS_SP_FRAME_SIZE) {
        if (buf_size)
            av_log(avctx, AV_LOG_WARNING,
                   "Expected %d bytes, got %d - skipping packet.\n",
                   DSS_SP_FRAME_SIZE, buf_size);
        *got_frame_ptr = 0;
        return AVERROR_INVALIDDATA;
    }

    frame->nb_samples = DSS_SP_SAMPLE_COUNT;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;

    out = (int16_t *)frame->data[0];

    dss_sp_decode_one_frame(p, out, buf);

    *got_frame_ptr = 1;

    return DSS_SP_FRAME_SIZE;
}