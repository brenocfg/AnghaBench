#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  int uint32_t ;
struct TYPE_12__ {int channels; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  frame_size; int /*<<< orphan*/  bit_rate; int /*<<< orphan*/  channel_layout; TYPE_2__* priv_data; } ;
struct TYPE_11__ {char* data; int size; } ;
struct TYPE_10__ {int frame_size; int nb_channels; int /*<<< orphan*/  sample_rate; TYPE_1__* frame; int /*<<< orphan*/  bit_rate; } ;
struct TYPE_9__ {int /*<<< orphan*/  nb_samples; } ;
typedef  int /*<<< orphan*/  MPADecodeHeader ;
typedef  TYPE_2__ MPADecodeContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_STEREO ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_RB32 (char const*) ; 
 int HEADER_SIZE ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int avpriv_mpegaudio_decode_header (int /*<<< orphan*/ *,int) ; 
 int mp_decode_frame (TYPE_2__*,int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static int decode_frame(AVCodecContext * avctx, void *data, int *got_frame_ptr,
                        AVPacket *avpkt)
{
    const uint8_t *buf  = avpkt->data;
    int buf_size        = avpkt->size;
    MPADecodeContext *s = avctx->priv_data;
    uint32_t header;
    int ret;

    int skipped = 0;
    while(buf_size && !*buf){
        buf++;
        buf_size--;
        skipped++;
    }

    if (buf_size < HEADER_SIZE)
        return AVERROR_INVALIDDATA;

    header = AV_RB32(buf);
    if (header>>8 == AV_RB32("TAG")>>8) {
        av_log(avctx, AV_LOG_DEBUG, "discarding ID3 tag\n");
        return buf_size + skipped;
    }
    ret = avpriv_mpegaudio_decode_header((MPADecodeHeader *)s, header);
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR, "Header missing\n");
        return AVERROR_INVALIDDATA;
    } else if (ret == 1) {
        /* free format: prepare to compute frame size */
        s->frame_size = -1;
        return AVERROR_INVALIDDATA;
    }
    /* update codec info */
    avctx->channels       = s->nb_channels;
    avctx->channel_layout = s->nb_channels == 1 ? AV_CH_LAYOUT_MONO : AV_CH_LAYOUT_STEREO;
    if (!avctx->bit_rate)
        avctx->bit_rate = s->bit_rate;

    if (s->frame_size <= 0) {
        av_log(avctx, AV_LOG_ERROR, "incomplete frame\n");
        return AVERROR_INVALIDDATA;
    } else if (s->frame_size < buf_size) {
        av_log(avctx, AV_LOG_DEBUG, "incorrect frame size - multiple frames in buffer?\n");
        buf_size= s->frame_size;
    }

    s->frame = data;

    ret = mp_decode_frame(s, NULL, buf, buf_size);
    if (ret >= 0) {
        s->frame->nb_samples = avctx->frame_size;
        *got_frame_ptr       = 1;
        avctx->sample_rate   = s->sample_rate;
        //FIXME maybe move the other codec info stuff from above here too
    } else {
        av_log(avctx, AV_LOG_ERROR, "Error while decoding MPEG audio frame.\n");
        /* Only return an error if the bad frame makes up the whole packet or
         * the error is related to buffer management.
         * If there is more data in the packet, just consume the bad frame
         * instead of returning an error, which would discard the whole
         * packet. */
        *got_frame_ptr = 0;
        if (buf_size == avpkt->size || ret != AVERROR_INVALIDDATA)
            return ret;
    }
    s->frame_size = 0;
    return buf_size + skipped;
}