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
#define  AV_CODEC_ID_H264 131 
#define  AV_CODEC_ID_HEVC 130 
#define  AV_CODEC_ID_MPEG2VIDEO 129 
#define  AV_CODEC_ID_VC1 128 
 int FF_PROFILE_UNKNOWN ; 
 int MFX_PROFILE_UNKNOWN ; 

int ff_qsv_profile_to_mfx(enum AVCodecID codec_id, int profile)
{
    if (profile == FF_PROFILE_UNKNOWN)
        return MFX_PROFILE_UNKNOWN;
    switch (codec_id) {
    case AV_CODEC_ID_H264:
    case AV_CODEC_ID_HEVC:
        return profile;
    case AV_CODEC_ID_VC1:
        return 4 * profile + 1;
    case AV_CODEC_ID_MPEG2VIDEO:
        return 0x10 * profile;
    }
    return MFX_PROFILE_UNKNOWN;
}