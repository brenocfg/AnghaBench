#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int int8_t ;
typedef  int int16_t ;
struct TYPE_10__ {int channels; int /*<<< orphan*/  channel_layout; } ;
struct TYPE_9__ {int nb_samples; scalar_t__* data; } ;
struct TYPE_8__ {int size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_STEREO ; 
 int av_clip (int,int /*<<< orphan*/ ,int) ; 
 int av_clip_int16 (int) ; 
 int* ff_adpcm_step_table ; 
 int ff_get_buffer (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_long (int /*<<< orphan*/ *,int) ; 
 void* get_sbits (int /*<<< orphan*/ *,int) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int* predict_table ; 
 int* size_table ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 
 scalar_t__** step_index_tables ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx, void *data,
                        int *got_frame_ptr, AVPacket *pkt)
{
    GetBitContext gb;
    AVFrame *frame = data;
    int16_t pcm_data[2];
    uint32_t samples;
    int8_t channel_hint[2];
    int ret, chan;
    int channels = 1;

    if (pkt->size < 13)
        return AVERROR_INVALIDDATA;

    if ((ret = init_get_bits8(&gb, pkt->data, pkt->size)) < 0)
        return ret;

    samples = get_bits_long(&gb, 32);
    if (samples == 0xffffffff) {
        skip_bits_long(&gb, 32);
        samples = get_bits_long(&gb, 32);
    }

    if (samples > pkt->size * 2)
        return AVERROR_INVALIDDATA;

    channel_hint[0] = get_sbits(&gb, 8);
    if (channel_hint[0] & 0x80) {
        channel_hint[0] = ~channel_hint[0];
        channels = 2;
    }
    avctx->channels = channels;
    avctx->channel_layout = (channels == 2) ? AV_CH_LAYOUT_STEREO
                                            : AV_CH_LAYOUT_MONO;
    pcm_data[0] = get_sbits(&gb, 16);
    if (channels > 1) {
        channel_hint[1] = get_sbits(&gb, 8);
        pcm_data[1]     = get_sbits(&gb, 16);
    }

    frame->nb_samples = samples;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;

    for (chan = 0; chan < channels; chan++) {
        uint16_t *dest = (uint16_t *)frame->data[0] + chan;
        int step_index = channel_hint[chan];
        int output = pcm_data[chan];
        int sample;

        for (sample = 0; sample < samples; sample++) {
            int lookup_size, lookup, highbit, lowbits;

            step_index  = av_clip(step_index, 0, 88);
            lookup_size = size_table[step_index];
            lookup      = get_bits(&gb, lookup_size);
            highbit     = 1 << (lookup_size - 1);
            lowbits     = highbit - 1;

            if (lookup & highbit)
                lookup ^= highbit;
            else
                highbit = 0;

            if (lookup == lowbits) {
                output = get_sbits(&gb, 16);
            } else {
                int predict_index, diff;

                predict_index = (lookup << (7 - lookup_size)) | (step_index << 6);
                predict_index = av_clip(predict_index, 0, 5785);
                diff          = predict_table[predict_index];
                if (lookup)
                    diff += ff_adpcm_step_table[step_index] >> (lookup_size - 1);
                if (highbit)
                    diff = -diff;

                output = av_clip_int16(output + diff);
            }

            *dest = output;
            dest += channels;

            step_index += step_index_tables[lookup_size - 2][lookup];
        }
    }

    *got_frame_ptr = 1;

    return pkt->size;
}