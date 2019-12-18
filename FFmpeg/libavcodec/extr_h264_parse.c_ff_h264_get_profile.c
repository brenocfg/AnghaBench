#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int profile_idc; int constraint_set_flags; } ;
typedef  TYPE_1__ SPS ;

/* Variables and functions */
#define  FF_PROFILE_H264_BASELINE 131 
 int FF_PROFILE_H264_CONSTRAINED ; 
#define  FF_PROFILE_H264_HIGH_10 130 
#define  FF_PROFILE_H264_HIGH_422 129 
#define  FF_PROFILE_H264_HIGH_444_PREDICTIVE 128 
 int FF_PROFILE_H264_INTRA ; 

int ff_h264_get_profile(const SPS *sps)
{
    int profile = sps->profile_idc;

    switch (sps->profile_idc) {
    case FF_PROFILE_H264_BASELINE:
        // constraint_set1_flag set to 1
        profile |= (sps->constraint_set_flags & 1 << 1) ? FF_PROFILE_H264_CONSTRAINED : 0;
        break;
    case FF_PROFILE_H264_HIGH_10:
    case FF_PROFILE_H264_HIGH_422:
    case FF_PROFILE_H264_HIGH_444_PREDICTIVE:
        // constraint_set3_flag set to 1
        profile |= (sps->constraint_set_flags & 1 << 3) ? FF_PROFILE_H264_INTRA : 0;
        break;
    }

    return profile;
}