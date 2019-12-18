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
 int AV_CODEC_ID_PCM_S16LE ; 
 int AV_CODEC_ID_PCM_U8 ; 
 int AV_CODEC_ID_SOL_DPCM ; 
 int SOL_16BIT ; 
 int SOL_DPCM ; 

__attribute__((used)) static enum AVCodecID sol_codec_id(int magic, int type)
{
    if (type & SOL_DPCM)
        return AV_CODEC_ID_SOL_DPCM;

    if (magic == 0x0B8D)
        return AV_CODEC_ID_PCM_U8;

    if (type & SOL_16BIT)
        return AV_CODEC_ID_PCM_S16LE;

    return AV_CODEC_ID_PCM_U8;
}