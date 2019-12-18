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
typedef  int uint8_t ;
typedef  int int8_t ;
struct TYPE_6__ {int nb_samples; int** data; } ;
struct TYPE_5__ {int* data; int size; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_RL16 (int const*) ; 
 int /*<<< orphan*/  EINVAL ; 
 int av_clip_uint8 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int ff_get_buffer (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int* ws_adpcm_4bit ; 

__attribute__((used)) static int ws_snd_decode_frame(AVCodecContext *avctx, void *data,
                               int *got_frame_ptr, AVPacket *avpkt)
{
    AVFrame *frame     = data;
    const uint8_t *buf = avpkt->data;
    int buf_size       = avpkt->size;

    int in_size, out_size, ret;
    int sample = 128;
    uint8_t *samples;
    uint8_t *samples_end;

    if (!buf_size)
        return 0;

    if (buf_size < 4) {
        av_log(avctx, AV_LOG_ERROR, "packet is too small\n");
        return AVERROR(EINVAL);
    }

    out_size = AV_RL16(&buf[0]);
    in_size  = AV_RL16(&buf[2]);
    buf += 4;

    if (in_size > buf_size) {
        av_log(avctx, AV_LOG_ERROR, "Frame data is larger than input buffer\n");
        return AVERROR_INVALIDDATA;
    }

    /* get output buffer */
    frame->nb_samples = out_size;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;
    samples     = frame->data[0];
    samples_end = samples + out_size;

    if (in_size == out_size) {
        memcpy(samples, buf, out_size);
        *got_frame_ptr = 1;
        return buf_size;
    }

    while (samples < samples_end && buf - avpkt->data < buf_size) {
        int code, smp, size;
        uint8_t count;
        code  = *buf >> 6;
        count = *buf & 0x3F;
        buf++;

        /* make sure we don't write past the output buffer */
        switch (code) {
        case 0:  smp = 4 * (count + 1);                break;
        case 1:  smp = 2 * (count + 1);                break;
        case 2:  smp = (count & 0x20) ? 1 : count + 1; break;
        default: smp = count + 1;                      break;
        }
        if (samples_end - samples < smp)
            break;

        /* make sure we don't read past the input buffer */
        size = ((code == 2 && (count & 0x20)) || code == 3) ? 0 : count + 1;
        if ((buf - avpkt->data) + size > buf_size)
            break;

        switch (code) {
        case 0: /* ADPCM 2-bit */
            for (count++; count > 0; count--) {
                code = *buf++;
                sample += ( code       & 0x3) - 2;
                sample = av_clip_uint8(sample);
                *samples++ = sample;
                sample += ((code >> 2) & 0x3) - 2;
                sample = av_clip_uint8(sample);
                *samples++ = sample;
                sample += ((code >> 4) & 0x3) - 2;
                sample = av_clip_uint8(sample);
                *samples++ = sample;
                sample +=  (code >> 6)        - 2;
                sample = av_clip_uint8(sample);
                *samples++ = sample;
            }
            break;
        case 1: /* ADPCM 4-bit */
            for (count++; count > 0; count--) {
                code = *buf++;
                sample += ws_adpcm_4bit[code & 0xF];
                sample = av_clip_uint8(sample);
                *samples++ = sample;
                sample += ws_adpcm_4bit[code >> 4];
                sample = av_clip_uint8(sample);
                *samples++ = sample;
            }
            break;
        case 2: /* no compression */
            if (count & 0x20) { /* big delta */
                int8_t t;
                t = count;
                t <<= 3;
                sample += t >> 3;
                sample = av_clip_uint8(sample);
                *samples++ = sample;
            } else { /* copy */
                memcpy(samples, buf, smp);
                samples += smp;
                buf     += smp;
                sample = buf[-1];
            }
            break;
        default: /* run */
            memset(samples, sample, smp);
            samples += smp;
        }
    }

    frame->nb_samples = samples - frame->data[0];
    *got_frame_ptr    = 1;

    return buf_size;
}