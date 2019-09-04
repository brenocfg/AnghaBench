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
struct TYPE_5__ {scalar_t__ fcm; scalar_t__ mv_mode; int lumshift; int intcompfield; int lumshift2; scalar_t__ intcomp; int /*<<< orphan*/  p_frame_skipped; TYPE_1__ s; } ;
typedef  TYPE_2__ VC1Context ;

/* Variables and functions */
 scalar_t__ AV_PICTURE_TYPE_P ; 
 scalar_t__ ILACE_FIELD ; 
 scalar_t__ ILACE_FRAME ; 
 scalar_t__ MV_PMODE_INTENSITY_COMP ; 
 scalar_t__ PROGRESSIVE ; 

__attribute__((used)) static inline int vc1_get_LUMSHIFT(const VC1Context *v)
{
    if (v->s.pict_type == AV_PICTURE_TYPE_P && !v->p_frame_skipped) {
        if ((v->fcm == PROGRESSIVE && v->mv_mode == MV_PMODE_INTENSITY_COMP) ||
            (v->fcm == ILACE_FRAME && v->intcomp))
            return v->lumshift;
        else if (v->fcm == ILACE_FIELD && v->mv_mode == MV_PMODE_INTENSITY_COMP)
            switch (v->intcompfield) {
            case 1: return v->lumshift;
            case 2: return v->lumshift2;
            case 3: return v->lumshift;
        }
    }
    return 0;
}