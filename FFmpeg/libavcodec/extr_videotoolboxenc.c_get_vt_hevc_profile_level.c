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
struct TYPE_6__ {int profile; } ;
typedef  TYPE_1__ VTEncContext ;
struct TYPE_8__ {int /*<<< orphan*/ * kVTProfileLevel_HEVC_Main10_AutoLevel; int /*<<< orphan*/ * kVTProfileLevel_HEVC_Main_AutoLevel; } ;
struct TYPE_7__ {TYPE_1__* priv_data; } ;
typedef  int /*<<< orphan*/ * CFStringRef ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  HEVC_PROF_AUTO 130 
#define  HEVC_PROF_MAIN 129 
#define  HEVC_PROF_MAIN10 128 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_4__ compat_keys ; 

__attribute__((used)) static bool get_vt_hevc_profile_level(AVCodecContext *avctx,
                                      CFStringRef    *profile_level_val)
{
    VTEncContext *vtctx = avctx->priv_data;
    int64_t profile = vtctx->profile;

    *profile_level_val = NULL;

    switch (profile) {
        case HEVC_PROF_AUTO:
            return true;
        case HEVC_PROF_MAIN:
            *profile_level_val =
                compat_keys.kVTProfileLevel_HEVC_Main_AutoLevel;
            break;
        case HEVC_PROF_MAIN10:
            *profile_level_val =
                compat_keys.kVTProfileLevel_HEVC_Main10_AutoLevel;
            break;
    }

    if (!*profile_level_val) {
        av_log(avctx, AV_LOG_ERROR, "Invalid Profile/Level.\n");
        return false;
    }

    return true;
}