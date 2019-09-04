#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int16_t ;
struct TYPE_10__ {int chunk_size; int out_bps; } ;
typedef  TYPE_1__ VmdAudioContext ;
struct TYPE_13__ {int block_align; int channels; TYPE_1__* priv_data; } ;
struct TYPE_12__ {int nb_samples; int** data; } ;
struct TYPE_11__ {int* data; int size; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_RB32 (int const*) ; 
 int BLOCK_TYPE_AUDIO ; 
 int BLOCK_TYPE_INITIAL ; 
 int BLOCK_TYPE_SILENCE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int av_popcount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_audio_s16 (int*,int const*,int,int) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static int vmdaudio_decode_frame(AVCodecContext *avctx, void *data,
                                 int *got_frame_ptr, AVPacket *avpkt)
{
    AVFrame *frame     = data;
    const uint8_t *buf = avpkt->data;
    const uint8_t *buf_end;
    int buf_size = avpkt->size;
    VmdAudioContext *s = avctx->priv_data;
    int block_type, silent_chunks, audio_chunks;
    int ret;
    uint8_t *output_samples_u8;
    int16_t *output_samples_s16;

    if (buf_size < 16) {
        av_log(avctx, AV_LOG_WARNING, "skipping small junk packet\n");
        *got_frame_ptr = 0;
        return buf_size;
    }

    block_type = buf[6];
    if (block_type < BLOCK_TYPE_AUDIO || block_type > BLOCK_TYPE_SILENCE) {
        av_log(avctx, AV_LOG_ERROR, "unknown block type: %d\n", block_type);
        return AVERROR(EINVAL);
    }
    buf      += 16;
    buf_size -= 16;

    /* get number of silent chunks */
    silent_chunks = 0;
    if (block_type == BLOCK_TYPE_INITIAL) {
        uint32_t flags;
        if (buf_size < 4) {
            av_log(avctx, AV_LOG_ERROR, "packet is too small\n");
            return AVERROR(EINVAL);
        }
        flags         = AV_RB32(buf);
        silent_chunks = av_popcount(flags);
        buf      += 4;
        buf_size -= 4;
    } else if (block_type == BLOCK_TYPE_SILENCE) {
        silent_chunks = 1;
        buf_size = 0; // should already be zero but set it just to be sure
    }

    /* ensure output buffer is large enough */
    audio_chunks = buf_size / s->chunk_size;

    /* drop incomplete chunks */
    buf_size     = audio_chunks * s->chunk_size;

    /* get output buffer */
    frame->nb_samples = ((silent_chunks + audio_chunks) * avctx->block_align) /
                        avctx->channels;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;
    output_samples_u8  =            frame->data[0];
    output_samples_s16 = (int16_t *)frame->data[0];

    /* decode silent chunks */
    if (silent_chunks > 0) {
        int silent_size = avctx->block_align * silent_chunks;
        av_assert0(avctx->block_align * silent_chunks <= frame->nb_samples * avctx->channels);

        if (s->out_bps == 2) {
            memset(output_samples_s16, 0x00, silent_size * 2);
            output_samples_s16 += silent_size;
        } else {
            memset(output_samples_u8,  0x80, silent_size);
            output_samples_u8 += silent_size;
        }
    }

    /* decode audio chunks */
    if (audio_chunks > 0) {
        buf_end = buf + buf_size;
        av_assert0((buf_size & (avctx->channels > 1)) == 0);
        while (buf_end - buf >= s->chunk_size) {
            if (s->out_bps == 2) {
                decode_audio_s16(output_samples_s16, buf, s->chunk_size,
                                 avctx->channels);
                output_samples_s16 += avctx->block_align;
            } else {
                memcpy(output_samples_u8, buf, s->chunk_size);
                output_samples_u8  += avctx->block_align;
            }
            buf += s->chunk_size;
        }
    }

    *got_frame_ptr = 1;

    return avpkt->size;
}