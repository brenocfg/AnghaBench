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
#define  AV_CODEC_ID_PCM_F32BE 139 
#define  AV_CODEC_ID_PCM_F32LE 138 
#define  AV_CODEC_ID_PCM_F64BE 137 
#define  AV_CODEC_ID_PCM_F64LE 136 
#define  AV_CODEC_ID_PCM_S16BE 135 
#define  AV_CODEC_ID_PCM_S16LE 134 
#define  AV_CODEC_ID_PCM_S24BE 133 
#define  AV_CODEC_ID_PCM_S24LE 132 
#define  AV_CODEC_ID_PCM_S32BE 131 
#define  AV_CODEC_ID_PCM_S32LE 130 
#define  AV_CODEC_ID_PCM_S8 129 
#define  AV_CODEC_ID_PCM_U8 128 

__attribute__((used)) static int mov_get_lpcm_flags(enum AVCodecID codec_id)
{
    switch (codec_id) {
    case AV_CODEC_ID_PCM_F32BE:
    case AV_CODEC_ID_PCM_F64BE:
        return 11;
    case AV_CODEC_ID_PCM_F32LE:
    case AV_CODEC_ID_PCM_F64LE:
        return 9;
    case AV_CODEC_ID_PCM_U8:
        return 10;
    case AV_CODEC_ID_PCM_S16BE:
    case AV_CODEC_ID_PCM_S24BE:
    case AV_CODEC_ID_PCM_S32BE:
        return 14;
    case AV_CODEC_ID_PCM_S8:
    case AV_CODEC_ID_PCM_S16LE:
    case AV_CODEC_ID_PCM_S24LE:
    case AV_CODEC_ID_PCM_S32LE:
        return 12;
    default:
        return 0;
    }
}