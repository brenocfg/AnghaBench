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
struct TYPE_5__ {scalar_t__ profile; scalar_t__ bi_type; TYPE_1__ s; scalar_t__ acpred_is_raw; } ;
typedef  TYPE_2__ VC1Context ;

/* Variables and functions */
 scalar_t__ AV_PICTURE_TYPE_B ; 
 scalar_t__ AV_PICTURE_TYPE_I ; 
 scalar_t__ PROFILE_ADVANCED ; 

__attribute__((used)) static inline int vc1_has_ACPRED_bitplane(const VC1Context *v)
{
    if (v->acpred_is_raw)
        return 0;
    return v->profile == PROFILE_ADVANCED &&
           (v->s.pict_type == AV_PICTURE_TYPE_I ||
            (v->s.pict_type == AV_PICTURE_TYPE_B && v->bi_type));
}