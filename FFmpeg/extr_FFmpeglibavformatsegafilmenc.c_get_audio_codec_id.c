#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;

/* Variables and functions */
#define  AV_CODEC_ID_ADPCM_ADX 130 
#define  AV_CODEC_ID_PCM_S16BE_PLANAR 129 
#define  AV_CODEC_ID_PCM_S8_PLANAR 128 

__attribute__((used)) static int get_audio_codec_id(enum AVCodecID codec_id)
{
    /* 0 (PCM) and 2 (ADX) are the only known values */
    switch (codec_id) {
    case AV_CODEC_ID_PCM_S8_PLANAR:
    case AV_CODEC_ID_PCM_S16BE_PLANAR:
        return 0;
        break;
    case AV_CODEC_ID_ADPCM_ADX:
        return 2;
        break;
    default:
        return -1;
    }
}