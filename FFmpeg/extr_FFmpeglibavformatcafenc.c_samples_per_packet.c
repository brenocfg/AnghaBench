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
#define  AV_CODEC_ID_AC3 158 
#define  AV_CODEC_ID_ADPCM_IMA_QT 157 
#define  AV_CODEC_ID_ADPCM_IMA_WAV 156 
#define  AV_CODEC_ID_ADPCM_MS 155 
#define  AV_CODEC_ID_ALAC 154 
#define  AV_CODEC_ID_AMR_NB 153 
#define  AV_CODEC_ID_GSM 152 
#define  AV_CODEC_ID_GSM_MS 151 
#define  AV_CODEC_ID_ILBC 150 
#define  AV_CODEC_ID_MACE3 149 
#define  AV_CODEC_ID_MACE6 148 
#define  AV_CODEC_ID_MP1 147 
#define  AV_CODEC_ID_MP2 146 
#define  AV_CODEC_ID_MP3 145 
#define  AV_CODEC_ID_OPUS 144 
#define  AV_CODEC_ID_PCM_ALAW 143 
#define  AV_CODEC_ID_PCM_F32BE 142 
#define  AV_CODEC_ID_PCM_F32LE 141 
#define  AV_CODEC_ID_PCM_F64BE 140 
#define  AV_CODEC_ID_PCM_F64LE 139 
#define  AV_CODEC_ID_PCM_MULAW 138 
#define  AV_CODEC_ID_PCM_S16BE 137 
#define  AV_CODEC_ID_PCM_S16LE 136 
#define  AV_CODEC_ID_PCM_S24BE 135 
#define  AV_CODEC_ID_PCM_S24LE 134 
#define  AV_CODEC_ID_PCM_S32BE 133 
#define  AV_CODEC_ID_PCM_S32LE 132 
#define  AV_CODEC_ID_PCM_S8 131 
#define  AV_CODEC_ID_QCELP 130 
#define  AV_CODEC_ID_QDM2 129 
#define  AV_CODEC_ID_QDMC 128 

__attribute__((used)) static uint32_t samples_per_packet(enum AVCodecID codec_id, int channels, int block_align) {
    switch (codec_id) {
    case AV_CODEC_ID_PCM_S8:
    case AV_CODEC_ID_PCM_S16LE:
    case AV_CODEC_ID_PCM_S16BE:
    case AV_CODEC_ID_PCM_S24LE:
    case AV_CODEC_ID_PCM_S24BE:
    case AV_CODEC_ID_PCM_S32LE:
    case AV_CODEC_ID_PCM_S32BE:
    case AV_CODEC_ID_PCM_F32LE:
    case AV_CODEC_ID_PCM_F32BE:
    case AV_CODEC_ID_PCM_F64LE:
    case AV_CODEC_ID_PCM_F64BE:
    case AV_CODEC_ID_PCM_ALAW:
    case AV_CODEC_ID_PCM_MULAW:
        return 1;
    case AV_CODEC_ID_MACE3:
    case AV_CODEC_ID_MACE6:
        return 6;
    case AV_CODEC_ID_ADPCM_IMA_QT:
        return 64;
    case AV_CODEC_ID_AMR_NB:
    case AV_CODEC_ID_GSM:
    case AV_CODEC_ID_ILBC:
    case AV_CODEC_ID_QCELP:
        return 160;
    case AV_CODEC_ID_GSM_MS:
        return 320;
    case AV_CODEC_ID_MP1:
        return 384;
    case AV_CODEC_ID_OPUS:
        return 960;
    case AV_CODEC_ID_MP2:
    case AV_CODEC_ID_MP3:
        return 1152;
    case AV_CODEC_ID_AC3:
        return 1536;
    case AV_CODEC_ID_QDM2:
    case AV_CODEC_ID_QDMC:
        return 2048 * channels;
    case AV_CODEC_ID_ALAC:
        return 4096;
    case AV_CODEC_ID_ADPCM_IMA_WAV:
        return (block_align - 4 * channels) * 8 / (4 * channels) + 1;
    case AV_CODEC_ID_ADPCM_MS:
        return (block_align - 7 * channels) * 2 / channels + 2;
    default:
        return 0;
    }
}