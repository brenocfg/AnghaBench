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
 int AV_CODEC_ID_PCM_S16BE ; 
 int AV_CODEC_ID_PCM_S24BE ; 
 int AV_CODEC_ID_PCM_S32BE ; 
 int AV_CODEC_ID_PCM_S8 ; 

__attribute__((used)) static enum AVCodecID aiff_codec_get_id(int bps)
{
    if (bps <= 8)
        return AV_CODEC_ID_PCM_S8;
    if (bps <= 16)
        return AV_CODEC_ID_PCM_S16BE;
    if (bps <= 24)
        return AV_CODEC_ID_PCM_S24BE;
    if (bps <= 32)
        return AV_CODEC_ID_PCM_S32BE;

    /* bigger than 32 isn't allowed  */
    return AV_CODEC_ID_NONE;
}