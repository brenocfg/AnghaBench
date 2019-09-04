#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_25__ {int /*<<< orphan*/  afq; int /*<<< orphan*/  handle; } ;
struct TYPE_24__ {int numBufs; void** bufs; int* bufferIdentifiers; int* bufSizes; int* bufElSizes; int /*<<< orphan*/  member_0; } ;
struct TYPE_23__ {int numInSamples; int /*<<< orphan*/  member_0; } ;
struct TYPE_22__ {int numOutBytes; int /*<<< orphan*/  member_0; } ;
struct TYPE_21__ {int channels; int /*<<< orphan*/  frame_size; TYPE_7__* priv_data; } ;
struct TYPE_20__ {int nb_samples; void** data; } ;
struct TYPE_19__ {int size; int /*<<< orphan*/  duration; int /*<<< orphan*/  pts; void* data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;
typedef  TYPE_4__ AACENC_OutArgs ;
typedef  TYPE_5__ AACENC_InArgs ;
typedef  scalar_t__ AACENC_ERROR ;
typedef  TYPE_6__ AACENC_BufDesc ;
typedef  TYPE_7__ AACContext ;

/* Variables and functions */
 scalar_t__ AACENC_ENCODE_EOF ; 
 scalar_t__ AACENC_OK ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FFMAX (int,int) ; 
 int IN_AUDIO_DATA ; 
 int OUT_BITSTREAM_DATA ; 
 scalar_t__ aacEncEncode (int /*<<< orphan*/ ,TYPE_6__*,TYPE_6__*,TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  aac_get_error (scalar_t__) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ff_af_queue_add (int /*<<< orphan*/ *,TYPE_2__ const*) ; 
 int /*<<< orphan*/  ff_af_queue_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_alloc_packet2 (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aac_encode_frame(AVCodecContext *avctx, AVPacket *avpkt,
                            const AVFrame *frame, int *got_packet_ptr)
{
    AACContext    *s        = avctx->priv_data;
    AACENC_BufDesc in_buf   = { 0 }, out_buf = { 0 };
    AACENC_InArgs  in_args  = { 0 };
    AACENC_OutArgs out_args = { 0 };
    int in_buffer_identifier = IN_AUDIO_DATA;
    int in_buffer_size, in_buffer_element_size;
    int out_buffer_identifier = OUT_BITSTREAM_DATA;
    int out_buffer_size, out_buffer_element_size;
    void *in_ptr, *out_ptr;
    int ret;
    uint8_t dummy_buf[1];
    AACENC_ERROR err;

    /* handle end-of-stream small frame and flushing */
    if (!frame) {
        /* Must be a non-null pointer, even if it's a dummy. We could use
         * the address of anything else on the stack as well. */
        in_ptr               = dummy_buf;
        in_buffer_size       = 0;

        in_args.numInSamples = -1;
    } else {
        in_ptr               = frame->data[0];
        in_buffer_size       = 2 * avctx->channels * frame->nb_samples;

        in_args.numInSamples = avctx->channels * frame->nb_samples;

        /* add current frame to the queue */
        if ((ret = ff_af_queue_add(&s->afq, frame)) < 0)
            return ret;
    }

    in_buffer_element_size   = 2;
    in_buf.numBufs           = 1;
    in_buf.bufs              = &in_ptr;
    in_buf.bufferIdentifiers = &in_buffer_identifier;
    in_buf.bufSizes          = &in_buffer_size;
    in_buf.bufElSizes        = &in_buffer_element_size;

    /* The maximum packet size is 6144 bits aka 768 bytes per channel. */
    if ((ret = ff_alloc_packet2(avctx, avpkt, FFMAX(8192, 768 * avctx->channels), 0)) < 0)
        return ret;

    out_ptr                   = avpkt->data;
    out_buffer_size           = avpkt->size;
    out_buffer_element_size   = 1;
    out_buf.numBufs           = 1;
    out_buf.bufs              = &out_ptr;
    out_buf.bufferIdentifiers = &out_buffer_identifier;
    out_buf.bufSizes          = &out_buffer_size;
    out_buf.bufElSizes        = &out_buffer_element_size;

    if ((err = aacEncEncode(s->handle, &in_buf, &out_buf, &in_args,
                            &out_args)) != AACENC_OK) {
        if (!frame && err == AACENC_ENCODE_EOF)
            return 0;
        av_log(avctx, AV_LOG_ERROR, "Unable to encode frame: %s\n",
               aac_get_error(err));
        return AVERROR(EINVAL);
    }

    if (!out_args.numOutBytes)
        return 0;

    /* Get the next frame pts & duration */
    ff_af_queue_remove(&s->afq, avctx->frame_size, &avpkt->pts,
                       &avpkt->duration);

    avpkt->size     = out_args.numOutBytes;
    *got_packet_ptr = 1;
    return 0;
}