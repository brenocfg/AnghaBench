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
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;

/* Variables and functions */
 int AV_CODEC_ID_NONE ; 
 int AV_CODEC_ID_PCM_S16LE ; 
 int AV_CODEC_ID_PCM_S32LE ; 
 int AV_CODEC_ID_PCM_U8 ; 
#define  AV_SAMPLE_FMT_S16 130 
#define  AV_SAMPLE_FMT_S32 129 
#define  AV_SAMPLE_FMT_U8 128 

__attribute__((used)) static enum AVCodecID waveform_codec_id(enum AVSampleFormat sample_fmt)
{
    switch (sample_fmt) {
    case AV_SAMPLE_FMT_U8:  return AV_CODEC_ID_PCM_U8;
    case AV_SAMPLE_FMT_S16: return AV_CODEC_ID_PCM_S16LE;
    case AV_SAMPLE_FMT_S32: return AV_CODEC_ID_PCM_S32LE;
    default:                return AV_CODEC_ID_NONE; /* Should never happen. */
    }
}