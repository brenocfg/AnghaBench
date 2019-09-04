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
 int AV_CODEC_ID_PCM_F32LE ; 
 int AV_CODEC_ID_PCM_F64LE ; 
 int AV_CODEC_ID_PCM_S24LE ; 
 int AV_CODEC_ID_PCM_S32LE ; 

__attribute__((used)) static int mov_pcm_le_gt16(enum AVCodecID codec_id)
{
    return codec_id == AV_CODEC_ID_PCM_S24LE ||
           codec_id == AV_CODEC_ID_PCM_S32LE ||
           codec_id == AV_CODEC_ID_PCM_F32LE ||
           codec_id == AV_CODEC_ID_PCM_F64LE;
}