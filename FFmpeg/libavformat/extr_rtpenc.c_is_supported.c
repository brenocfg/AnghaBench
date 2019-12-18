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
#define  AV_CODEC_ID_AAC 162 
#define  AV_CODEC_ID_ADPCM_G722 161 
#define  AV_CODEC_ID_ADPCM_G726 160 
#define  AV_CODEC_ID_ADPCM_G726LE 159 
#define  AV_CODEC_ID_AMR_NB 158 
#define  AV_CODEC_ID_AMR_WB 157 
#define  AV_CODEC_ID_DIRAC 156 
#define  AV_CODEC_ID_H261 155 
#define  AV_CODEC_ID_H263 154 
#define  AV_CODEC_ID_H263P 153 
#define  AV_CODEC_ID_H264 152 
#define  AV_CODEC_ID_HEVC 151 
#define  AV_CODEC_ID_ILBC 150 
#define  AV_CODEC_ID_MJPEG 149 
#define  AV_CODEC_ID_MP2 148 
#define  AV_CODEC_ID_MP3 147 
#define  AV_CODEC_ID_MPEG1VIDEO 146 
#define  AV_CODEC_ID_MPEG2TS 145 
#define  AV_CODEC_ID_MPEG2VIDEO 144 
#define  AV_CODEC_ID_MPEG4 143 
#define  AV_CODEC_ID_OPUS 142 
#define  AV_CODEC_ID_PCM_ALAW 141 
#define  AV_CODEC_ID_PCM_MULAW 140 
#define  AV_CODEC_ID_PCM_S16BE 139 
#define  AV_CODEC_ID_PCM_S16LE 138 
#define  AV_CODEC_ID_PCM_S24BE 137 
#define  AV_CODEC_ID_PCM_S8 136 
#define  AV_CODEC_ID_PCM_U16BE 135 
#define  AV_CODEC_ID_PCM_U16LE 134 
#define  AV_CODEC_ID_PCM_U8 133 
#define  AV_CODEC_ID_SPEEX 132 
#define  AV_CODEC_ID_THEORA 131 
#define  AV_CODEC_ID_VORBIS 130 
#define  AV_CODEC_ID_VP8 129 
#define  AV_CODEC_ID_VP9 128 

__attribute__((used)) static int is_supported(enum AVCodecID id)
{
    switch(id) {
    case AV_CODEC_ID_DIRAC:
    case AV_CODEC_ID_H261:
    case AV_CODEC_ID_H263:
    case AV_CODEC_ID_H263P:
    case AV_CODEC_ID_H264:
    case AV_CODEC_ID_HEVC:
    case AV_CODEC_ID_MPEG1VIDEO:
    case AV_CODEC_ID_MPEG2VIDEO:
    case AV_CODEC_ID_MPEG4:
    case AV_CODEC_ID_AAC:
    case AV_CODEC_ID_MP2:
    case AV_CODEC_ID_MP3:
    case AV_CODEC_ID_PCM_ALAW:
    case AV_CODEC_ID_PCM_MULAW:
    case AV_CODEC_ID_PCM_S8:
    case AV_CODEC_ID_PCM_S16BE:
    case AV_CODEC_ID_PCM_S16LE:
    case AV_CODEC_ID_PCM_S24BE:
    case AV_CODEC_ID_PCM_U16BE:
    case AV_CODEC_ID_PCM_U16LE:
    case AV_CODEC_ID_PCM_U8:
    case AV_CODEC_ID_MPEG2TS:
    case AV_CODEC_ID_AMR_NB:
    case AV_CODEC_ID_AMR_WB:
    case AV_CODEC_ID_VORBIS:
    case AV_CODEC_ID_THEORA:
    case AV_CODEC_ID_VP8:
    case AV_CODEC_ID_VP9:
    case AV_CODEC_ID_ADPCM_G722:
    case AV_CODEC_ID_ADPCM_G726:
    case AV_CODEC_ID_ADPCM_G726LE:
    case AV_CODEC_ID_ILBC:
    case AV_CODEC_ID_MJPEG:
    case AV_CODEC_ID_SPEEX:
    case AV_CODEC_ID_OPUS:
        return 1;
    default:
        return 0;
    }
}