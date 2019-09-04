#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* th_ycbcr_buffer ;
struct TYPE_18__ {int granulepos; int /*<<< orphan*/  bytes; int /*<<< orphan*/  packet; } ;
typedef  TYPE_2__ ogg_packet ;
struct TYPE_19__ {int keyframe_mask; int /*<<< orphan*/  t_state; scalar_t__ uv_vshift; scalar_t__ uv_hshift; } ;
typedef  TYPE_3__ TheoraContext ;
struct TYPE_22__ {int flags; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_3__* priv_data; } ;
struct TYPE_21__ {int /*<<< orphan*/  pts; int /*<<< orphan*/ * data; int /*<<< orphan*/ * linesize; } ;
struct TYPE_20__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; int /*<<< orphan*/  data; } ;
struct TYPE_17__ {int width; int height; int /*<<< orphan*/  data; int /*<<< orphan*/  stride; } ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_EXTERNAL ; 
 int AV_CODEC_FLAG_PASS1 ; 
 int AV_CODEC_FLAG_PASS2 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int FFALIGN (int /*<<< orphan*/ ,int) ; 
#define  TH_EINVAL 128 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,...) ; 
 int ff_alloc_packet2 (TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_stats (TYPE_6__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int submit_stats (TYPE_6__*) ; 
 int th_encode_packetout (int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int th_encode_ycbcr_in (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int encode_frame(AVCodecContext* avc_context, AVPacket *pkt,
                        const AVFrame *frame, int *got_packet)
{
    th_ycbcr_buffer t_yuv_buffer;
    TheoraContext *h = avc_context->priv_data;
    ogg_packet o_packet;
    int result, i, ret;

    // EOS, finish and get 1st pass stats if applicable
    if (!frame) {
        th_encode_packetout(h->t_state, 1, &o_packet);
        if (avc_context->flags & AV_CODEC_FLAG_PASS1)
            if ((ret = get_stats(avc_context, 1)) < 0)
                return ret;
        return 0;
    }

    /* Copy planes to the theora yuv_buffer */
    for (i = 0; i < 3; i++) {
        t_yuv_buffer[i].width  = FFALIGN(avc_context->width,  16) >> (i && h->uv_hshift);
        t_yuv_buffer[i].height = FFALIGN(avc_context->height, 16) >> (i && h->uv_vshift);
        t_yuv_buffer[i].stride = frame->linesize[i];
        t_yuv_buffer[i].data   = frame->data[i];
    }

    if (avc_context->flags & AV_CODEC_FLAG_PASS2)
        if ((ret = submit_stats(avc_context)) < 0)
            return ret;

    /* Now call into theora_encode_YUVin */
    result = th_encode_ycbcr_in(h->t_state, t_yuv_buffer);
    if (result) {
        const char* message;
        switch (result) {
        case -1:
            message = "differing frame sizes";
            break;
        case TH_EINVAL:
            message = "encoder is not ready or is finished";
            break;
        default:
            message = "unknown reason";
            break;
        }
        av_log(avc_context, AV_LOG_ERROR, "theora_encode_YUVin failed (%s) [%d]\n", message, result);
        return AVERROR_EXTERNAL;
    }

    if (avc_context->flags & AV_CODEC_FLAG_PASS1)
        if ((ret = get_stats(avc_context, 0)) < 0)
            return ret;

    /* Pick up returned ogg_packet */
    result = th_encode_packetout(h->t_state, 0, &o_packet);
    switch (result) {
    case 0:
        /* No packet is ready */
        return 0;
    case 1:
        /* Success, we have a packet */
        break;
    default:
        av_log(avc_context, AV_LOG_ERROR, "theora_encode_packetout failed [%d]\n", result);
        return AVERROR_EXTERNAL;
    }

    /* Copy ogg_packet content out to buffer */
    if ((ret = ff_alloc_packet2(avc_context, pkt, o_packet.bytes, 0)) < 0)
        return ret;
    memcpy(pkt->data, o_packet.packet, o_packet.bytes);

    // HACK: assumes no encoder delay, this is true until libtheora becomes
    // multithreaded (which will be disabled unless explicitly requested)
    pkt->pts = pkt->dts = frame->pts;
#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
    avc_context->coded_frame->key_frame = !(o_packet.granulepos & h->keyframe_mask);
FF_ENABLE_DEPRECATION_WARNINGS
#endif
    if (!(o_packet.granulepos & h->keyframe_mask))
        pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;

    return 0;
}