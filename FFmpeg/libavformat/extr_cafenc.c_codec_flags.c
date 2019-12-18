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
typedef  int uint32_t ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;

/* Variables and functions */
#define  AV_CODEC_ID_PCM_F32BE 134 
#define  AV_CODEC_ID_PCM_F32LE 133 
#define  AV_CODEC_ID_PCM_F64BE 132 
#define  AV_CODEC_ID_PCM_F64LE 131 
#define  AV_CODEC_ID_PCM_S16LE 130 
#define  AV_CODEC_ID_PCM_S24LE 129 
#define  AV_CODEC_ID_PCM_S32LE 128 

__attribute__((used)) static uint32_t codec_flags(enum AVCodecID codec_id) {
    switch (codec_id) {
    case AV_CODEC_ID_PCM_F32BE:
    case AV_CODEC_ID_PCM_F64BE:
        return 1; //< kCAFLinearPCMFormatFlagIsFloat
    case AV_CODEC_ID_PCM_S16LE:
    case AV_CODEC_ID_PCM_S24LE:
    case AV_CODEC_ID_PCM_S32LE:
        return 2; //< kCAFLinearPCMFormatFlagIsLittleEndian
    case AV_CODEC_ID_PCM_F32LE:
    case AV_CODEC_ID_PCM_F64LE:
        return 3; //< kCAFLinearPCMFormatFlagIsFloat | kCAFLinearPCMFormatFlagIsLittleEndian
    default:
        return 0;
    }
}