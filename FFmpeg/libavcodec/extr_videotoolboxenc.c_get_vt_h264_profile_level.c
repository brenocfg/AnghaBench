#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_6__ {int profile; scalar_t__ level; scalar_t__ has_b_frames; } ;
typedef  TYPE_1__ VTEncContext ;
struct TYPE_8__ {int /*<<< orphan*/ * kVTProfileLevel_H264_Extended_5_0; int /*<<< orphan*/ * kVTProfileLevel_H264_Extended_AutoLevel; int /*<<< orphan*/ * kVTProfileLevel_H264_High_5_2; int /*<<< orphan*/ * kVTProfileLevel_H264_High_5_1; int /*<<< orphan*/ * kVTProfileLevel_H264_High_4_2; int /*<<< orphan*/ * kVTProfileLevel_H264_High_4_1; int /*<<< orphan*/ * kVTProfileLevel_H264_High_4_0; int /*<<< orphan*/ * kVTProfileLevel_H264_High_3_2; int /*<<< orphan*/ * kVTProfileLevel_H264_High_3_1; int /*<<< orphan*/ * kVTProfileLevel_H264_High_3_0; int /*<<< orphan*/ * kVTProfileLevel_H264_High_AutoLevel; int /*<<< orphan*/ * kVTProfileLevel_H264_Main_5_2; int /*<<< orphan*/ * kVTProfileLevel_H264_Main_5_1; int /*<<< orphan*/ * kVTProfileLevel_H264_Main_4_2; int /*<<< orphan*/ * kVTProfileLevel_H264_Main_AutoLevel; int /*<<< orphan*/ * kVTProfileLevel_H264_Baseline_5_2; int /*<<< orphan*/ * kVTProfileLevel_H264_Baseline_5_1; int /*<<< orphan*/ * kVTProfileLevel_H264_Baseline_5_0; int /*<<< orphan*/ * kVTProfileLevel_H264_Baseline_4_2; int /*<<< orphan*/ * kVTProfileLevel_H264_Baseline_4_0; int /*<<< orphan*/ * kVTProfileLevel_H264_Baseline_AutoLevel; } ;
struct TYPE_7__ {TYPE_1__* priv_data; } ;
typedef  int /*<<< orphan*/ * CFStringRef ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  H264_PROF_AUTO 132 
#define  H264_PROF_BASELINE 131 
#define  H264_PROF_EXTENDED 130 
#define  H264_PROF_HIGH 129 
#define  H264_PROF_MAIN 128 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_4__ compat_keys ; 
 int /*<<< orphan*/ * kVTProfileLevel_H264_Baseline_1_3 ; 
 int /*<<< orphan*/ * kVTProfileLevel_H264_Baseline_3_0 ; 
 int /*<<< orphan*/ * kVTProfileLevel_H264_Baseline_3_1 ; 
 int /*<<< orphan*/ * kVTProfileLevel_H264_Baseline_3_2 ; 
 int /*<<< orphan*/ * kVTProfileLevel_H264_Baseline_4_1 ; 
 int /*<<< orphan*/ * kVTProfileLevel_H264_High_5_0 ; 
 int /*<<< orphan*/ * kVTProfileLevel_H264_Main_3_0 ; 
 int /*<<< orphan*/ * kVTProfileLevel_H264_Main_3_1 ; 
 int /*<<< orphan*/ * kVTProfileLevel_H264_Main_3_2 ; 
 int /*<<< orphan*/ * kVTProfileLevel_H264_Main_4_0 ; 
 int /*<<< orphan*/ * kVTProfileLevel_H264_Main_4_1 ; 
 int /*<<< orphan*/ * kVTProfileLevel_H264_Main_5_0 ; 

__attribute__((used)) static bool get_vt_h264_profile_level(AVCodecContext *avctx,
                                      CFStringRef    *profile_level_val)
{
    VTEncContext *vtctx = avctx->priv_data;
    int64_t profile = vtctx->profile;

    if (profile == H264_PROF_AUTO && vtctx->level) {
        //Need to pick a profile if level is not auto-selected.
        profile = vtctx->has_b_frames ? H264_PROF_MAIN : H264_PROF_BASELINE;
    }

    *profile_level_val = NULL;

    switch (profile) {
        case H264_PROF_AUTO:
            return true;

        case H264_PROF_BASELINE:
            switch (vtctx->level) {
                case  0: *profile_level_val =
                                  compat_keys.kVTProfileLevel_H264_Baseline_AutoLevel; break;
                case 13: *profile_level_val = kVTProfileLevel_H264_Baseline_1_3;       break;
                case 30: *profile_level_val = kVTProfileLevel_H264_Baseline_3_0;       break;
                case 31: *profile_level_val = kVTProfileLevel_H264_Baseline_3_1;       break;
                case 32: *profile_level_val = kVTProfileLevel_H264_Baseline_3_2;       break;
                case 40: *profile_level_val =
                                  compat_keys.kVTProfileLevel_H264_Baseline_4_0;       break;
                case 41: *profile_level_val = kVTProfileLevel_H264_Baseline_4_1;       break;
                case 42: *profile_level_val =
                                  compat_keys.kVTProfileLevel_H264_Baseline_4_2;       break;
                case 50: *profile_level_val =
                                  compat_keys.kVTProfileLevel_H264_Baseline_5_0;       break;
                case 51: *profile_level_val =
                                  compat_keys.kVTProfileLevel_H264_Baseline_5_1;       break;
                case 52: *profile_level_val =
                                  compat_keys.kVTProfileLevel_H264_Baseline_5_2;       break;
            }
            break;

        case H264_PROF_MAIN:
            switch (vtctx->level) {
                case  0: *profile_level_val =
                                  compat_keys.kVTProfileLevel_H264_Main_AutoLevel; break;
                case 30: *profile_level_val = kVTProfileLevel_H264_Main_3_0;       break;
                case 31: *profile_level_val = kVTProfileLevel_H264_Main_3_1;       break;
                case 32: *profile_level_val = kVTProfileLevel_H264_Main_3_2;       break;
                case 40: *profile_level_val = kVTProfileLevel_H264_Main_4_0;       break;
                case 41: *profile_level_val = kVTProfileLevel_H264_Main_4_1;       break;
                case 42: *profile_level_val =
                                  compat_keys.kVTProfileLevel_H264_Main_4_2;       break;
                case 50: *profile_level_val = kVTProfileLevel_H264_Main_5_0;       break;
                case 51: *profile_level_val =
                                  compat_keys.kVTProfileLevel_H264_Main_5_1;       break;
                case 52: *profile_level_val =
                                  compat_keys.kVTProfileLevel_H264_Main_5_2;       break;
            }
            break;

        case H264_PROF_HIGH:
            switch (vtctx->level) {
                case  0: *profile_level_val =
                                  compat_keys.kVTProfileLevel_H264_High_AutoLevel; break;
                case 30: *profile_level_val =
                                  compat_keys.kVTProfileLevel_H264_High_3_0;       break;
                case 31: *profile_level_val =
                                  compat_keys.kVTProfileLevel_H264_High_3_1;       break;
                case 32: *profile_level_val =
                                  compat_keys.kVTProfileLevel_H264_High_3_2;       break;
                case 40: *profile_level_val =
                                  compat_keys.kVTProfileLevel_H264_High_4_0;       break;
                case 41: *profile_level_val =
                                  compat_keys.kVTProfileLevel_H264_High_4_1;       break;
                case 42: *profile_level_val =
                                  compat_keys.kVTProfileLevel_H264_High_4_2;       break;
                case 50: *profile_level_val = kVTProfileLevel_H264_High_5_0;       break;
                case 51: *profile_level_val =
                                  compat_keys.kVTProfileLevel_H264_High_5_1;       break;
                case 52: *profile_level_val =
                                  compat_keys.kVTProfileLevel_H264_High_5_2;       break;
            }
            break;
        case H264_PROF_EXTENDED:
            switch (vtctx->level) {
                case  0: *profile_level_val =
                                  compat_keys.kVTProfileLevel_H264_Extended_AutoLevel; break;
                case 50: *profile_level_val =
                                  compat_keys.kVTProfileLevel_H264_Extended_5_0;       break;
            }
            break;
    }

    if (!*profile_level_val) {
        av_log(avctx, AV_LOG_ERROR, "Invalid Profile/Level.\n");
        return false;
    }

    return true;
}