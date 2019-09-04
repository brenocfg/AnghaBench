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
struct TYPE_6__ {int channels; int sample_rate; int frame_size; void* sample_fmt; } ;
struct TYPE_5__ {int duration; } ;
typedef  TYPE_1__ AVCodecParserContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 void* AV_SAMPLE_FMT_S16 ; 
 int const MSBC_SYNCWORD ; 
 int SBC_MODE_DUAL_CHANNEL ; 
 int SBC_MODE_JOINT_STEREO ; 
 int SBC_MODE_MONO ; 
 int const SBC_SYNCWORD ; 

__attribute__((used)) static int sbc_parse_header(AVCodecParserContext *s, AVCodecContext *avctx,
                            const uint8_t *data, size_t len)
{
    static const int sample_rates[4] = { 16000, 32000, 44100, 48000 };
    int sr, blocks, mode, subbands, bitpool, channels, joint;
    int length;

    if (len < 3)
        return -1;

    if (data[0] == MSBC_SYNCWORD && data[1] == 0 && data[2] == 0) {
        avctx->channels = 1;
        avctx->sample_fmt = AV_SAMPLE_FMT_S16;
        avctx->sample_rate = 16000;
        avctx->frame_size = 120;
        s->duration = avctx->frame_size;
        return 57;
    }

    if (data[0] != SBC_SYNCWORD)
        return -2;

    sr       =   (data[1] >> 6) & 0x03;
    blocks   = (((data[1] >> 4) & 0x03) + 1) << 2;
    mode     =   (data[1] >> 2) & 0x03;
    subbands = (((data[1] >> 0) & 0x01) + 1) << 2;
    bitpool  = data[2];

    channels = mode == SBC_MODE_MONO ? 1 : 2;
    joint    = mode == SBC_MODE_JOINT_STEREO;

    length = 4 + (subbands * channels) / 2
             + ((((mode == SBC_MODE_DUAL_CHANNEL) + 1) * blocks * bitpool
                 + (joint * subbands)) + 7) / 8;

    avctx->channels = channels;
    avctx->sample_fmt = AV_SAMPLE_FMT_S16;
    avctx->sample_rate = sample_rates[sr];
    avctx->frame_size = subbands * blocks;
    s->duration = avctx->frame_size;
    return length;
}