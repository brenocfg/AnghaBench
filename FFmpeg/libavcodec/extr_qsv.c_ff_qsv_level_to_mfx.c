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
#define  AV_CODEC_ID_HEVC 128 
 int FF_LEVEL_UNKNOWN ; 
 int MFX_LEVEL_UNKNOWN ; 

int ff_qsv_level_to_mfx(enum AVCodecID codec_id, int level)
{
    if (level == FF_LEVEL_UNKNOWN)
        return MFX_LEVEL_UNKNOWN;

    switch (codec_id) {
    case AV_CODEC_ID_HEVC:
        return level / 3;
    default:
        return level;
    }
}