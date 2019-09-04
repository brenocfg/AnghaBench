#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pict_type; } ;
struct TYPE_5__ {scalar_t__ fcm; scalar_t__ mv_mode; scalar_t__ mv_mode2; int /*<<< orphan*/  p_frame_skipped; TYPE_1__ s; scalar_t__ mv_type_is_raw; } ;
typedef  TYPE_2__ VC1Context ;

/* Variables and functions */
 scalar_t__ AV_PICTURE_TYPE_P ; 
 scalar_t__ MV_PMODE_INTENSITY_COMP ; 
 scalar_t__ MV_PMODE_MIXED_MV ; 
 scalar_t__ PROGRESSIVE ; 

__attribute__((used)) static inline int vc1_has_MVTYPEMB_bitplane(const VC1Context *v)
{
    if (v->mv_type_is_raw)
        return 0;
    return v->fcm == PROGRESSIVE &&
           (v->s.pict_type == AV_PICTURE_TYPE_P && !v->p_frame_skipped) &&
           (v->mv_mode == MV_PMODE_MIXED_MV ||
            (v->mv_mode == MV_PMODE_INTENSITY_COMP &&
             v->mv_mode2 == MV_PMODE_MIXED_MV));
}