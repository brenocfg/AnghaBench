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
struct TYPE_3__ {int profile; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
#define  FF_PROFILE_DNXHR_444 132 
#define  FF_PROFILE_DNXHR_HQ 131 
#define  FF_PROFILE_DNXHR_HQX 130 
#define  FF_PROFILE_DNXHR_LB 129 
#define  FF_PROFILE_DNXHR_SQ 128 

__attribute__((used)) static int dnxhd_find_hr_cid(AVCodecContext *avctx)
{
    switch (avctx->profile) {
    case FF_PROFILE_DNXHR_444:
        return 1270;
    case FF_PROFILE_DNXHR_HQX:
        return 1271;
    case FF_PROFILE_DNXHR_HQ:
        return 1272;
    case FF_PROFILE_DNXHR_SQ:
        return 1273;
    case FF_PROFILE_DNXHR_LB:
        return 1274;
    }
    return 0;
}