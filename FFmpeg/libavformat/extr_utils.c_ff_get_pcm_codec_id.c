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
 int AV_CODEC_ID_NONE ; 
 int AV_CODEC_ID_PCM_F32BE ; 
 int AV_CODEC_ID_PCM_F32LE ; 
 int AV_CODEC_ID_PCM_F64BE ; 
 int AV_CODEC_ID_PCM_F64LE ; 
 int AV_CODEC_ID_PCM_S16BE ; 
 int AV_CODEC_ID_PCM_S16LE ; 
 int AV_CODEC_ID_PCM_S24BE ; 
 int AV_CODEC_ID_PCM_S24LE ; 
 int AV_CODEC_ID_PCM_S32BE ; 
 int AV_CODEC_ID_PCM_S32LE ; 
 int AV_CODEC_ID_PCM_S64BE ; 
 int AV_CODEC_ID_PCM_S64LE ; 
 int AV_CODEC_ID_PCM_S8 ; 
 int AV_CODEC_ID_PCM_U16BE ; 
 int AV_CODEC_ID_PCM_U16LE ; 
 int AV_CODEC_ID_PCM_U24BE ; 
 int AV_CODEC_ID_PCM_U24LE ; 
 int AV_CODEC_ID_PCM_U32BE ; 
 int AV_CODEC_ID_PCM_U32LE ; 
 int AV_CODEC_ID_PCM_U8 ; 

enum AVCodecID ff_get_pcm_codec_id(int bps, int flt, int be, int sflags)
{
    if (bps <= 0 || bps > 64)
        return AV_CODEC_ID_NONE;

    if (flt) {
        switch (bps) {
        case 32:
            return be ? AV_CODEC_ID_PCM_F32BE : AV_CODEC_ID_PCM_F32LE;
        case 64:
            return be ? AV_CODEC_ID_PCM_F64BE : AV_CODEC_ID_PCM_F64LE;
        default:
            return AV_CODEC_ID_NONE;
        }
    } else {
        bps  += 7;
        bps >>= 3;
        if (sflags & (1 << (bps - 1))) {
            switch (bps) {
            case 1:
                return AV_CODEC_ID_PCM_S8;
            case 2:
                return be ? AV_CODEC_ID_PCM_S16BE : AV_CODEC_ID_PCM_S16LE;
            case 3:
                return be ? AV_CODEC_ID_PCM_S24BE : AV_CODEC_ID_PCM_S24LE;
            case 4:
                return be ? AV_CODEC_ID_PCM_S32BE : AV_CODEC_ID_PCM_S32LE;
            case 8:
                return be ? AV_CODEC_ID_PCM_S64BE : AV_CODEC_ID_PCM_S64LE;
            default:
                return AV_CODEC_ID_NONE;
            }
        } else {
            switch (bps) {
            case 1:
                return AV_CODEC_ID_PCM_U8;
            case 2:
                return be ? AV_CODEC_ID_PCM_U16BE : AV_CODEC_ID_PCM_U16LE;
            case 3:
                return be ? AV_CODEC_ID_PCM_U24BE : AV_CODEC_ID_PCM_U24LE;
            case 4:
                return be ? AV_CODEC_ID_PCM_U32BE : AV_CODEC_ID_PCM_U32LE;
            default:
                return AV_CODEC_ID_NONE;
            }
        }
    }
}