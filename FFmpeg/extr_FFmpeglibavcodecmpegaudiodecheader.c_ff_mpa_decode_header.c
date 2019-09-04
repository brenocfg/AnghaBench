#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_3__ {int layer; int sample_rate; int nb_channels; int bit_rate; int frame_size; int /*<<< orphan*/  lsf; } ;
typedef  TYPE_1__ MPADecodeHeader ;

/* Variables and functions */
 int AV_CODEC_ID_MP1 ; 
 int AV_CODEC_ID_MP2 ; 
 int AV_CODEC_ID_MP3 ; 
 int AV_CODEC_ID_MP3ADU ; 
 scalar_t__ avpriv_mpegaudio_decode_header (TYPE_1__*,int /*<<< orphan*/ ) ; 

int ff_mpa_decode_header(uint32_t head, int *sample_rate, int *channels, int *frame_size, int *bit_rate, enum AVCodecID *codec_id)
{
    MPADecodeHeader s1, *s = &s1;

    if (avpriv_mpegaudio_decode_header(s, head) != 0) {
        return -1;
    }

    switch(s->layer) {
    case 1:
        *codec_id = AV_CODEC_ID_MP1;
        *frame_size = 384;
        break;
    case 2:
        *codec_id = AV_CODEC_ID_MP2;
        *frame_size = 1152;
        break;
    default:
    case 3:
        if (*codec_id != AV_CODEC_ID_MP3ADU)
            *codec_id = AV_CODEC_ID_MP3;
        if (s->lsf)
            *frame_size = 576;
        else
            *frame_size = 1152;
        break;
    }

    *sample_rate = s->sample_rate;
    *channels = s->nb_channels;
    *bit_rate = s->bit_rate;
    return s->frame_size;
}