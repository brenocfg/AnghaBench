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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_12__ {TYPE_1__* priv_data; } ;
struct TYPE_11__ {int nb_samples; scalar_t__* data; } ;
struct TYPE_10__ {int* data; scalar_t__ size; } ;
struct TYPE_9__ {scalar_t__ block_size; size_t* shuffle; scalar_t__ is_pal; scalar_t__ is_12bit; } ;
typedef  TYPE_1__ DVAudioContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 void* AV_RB16 (int const*) ; 
 void* dv_audio_12to16 (int const) ; 
 int dv_get_audio_sample_count (int*,scalar_t__) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx, void *data,
                        int *got_frame_ptr, AVPacket *pkt)
{
    DVAudioContext *s = avctx->priv_data;
    AVFrame *frame = data;
    const uint8_t *src = pkt->data;
    int16_t *dst;
    int ret, i;

    if (pkt->size < s->block_size)
        return AVERROR_INVALIDDATA;

    frame->nb_samples = dv_get_audio_sample_count(pkt->data + 244, s->is_pal);
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;
    dst = (int16_t *)frame->data[0];

    for (i = 0; i < frame->nb_samples; i++) {
       const uint8_t *v = &src[s->shuffle[i]];

       if (s->is_12bit) {
           *dst++ = dv_audio_12to16((v[0] << 4) | ((v[2] >> 4) & 0x0f));
           *dst++ = dv_audio_12to16((v[1] << 4) | ((v[2] >> 0) & 0x0f));
       } else {
           *dst++ = AV_RB16(&v[0]);
           *dst++ = AV_RB16(&v[s->is_pal ? 4320 : 3600]);
       }
    }

    *got_frame_ptr = 1;

    return s->block_size;
}