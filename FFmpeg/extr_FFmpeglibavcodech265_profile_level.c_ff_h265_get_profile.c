#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t profile_idc; int max_14bit; int max_12bit; int max_10bit; int max_8bit; int max_422chroma; int max_420chroma; int max_monochrome; int intra; int one_picture_only; int lower_bit_rate; } ;
struct TYPE_7__ {size_t general_profile_idc; int general_max_14bit_constraint_flag; int general_max_12bit_constraint_flag; int general_max_10bit_constraint_flag; int general_max_8bit_constraint_flag; int general_max_422chroma_constraint_flag; int general_max_420chroma_constraint_flag; int general_max_monochrome_constraint_flag; int general_intra_constraint_flag; int general_one_picture_only_constraint_flag; int general_lower_bit_rate_constraint_flag; int /*<<< orphan*/ * general_profile_compatibility_flag; scalar_t__ general_profile_space; } ;
typedef  TYPE_1__ H265RawProfileTierLevel ;
typedef  TYPE_2__ H265ProfileDescriptor ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_2__*) ; 
 TYPE_2__* h265_profiles ; 

const H265ProfileDescriptor *ff_h265_get_profile(const H265RawProfileTierLevel *ptl)
{
    int i;

    if (ptl->general_profile_space)
        return NULL;

    for (i = 0; i < FF_ARRAY_ELEMS(h265_profiles); i++) {
        const H265ProfileDescriptor *profile = &h265_profiles[i];

        if (ptl->general_profile_idc &&
            ptl->general_profile_idc != profile->profile_idc)
            continue;
        if (!ptl->general_profile_compatibility_flag[profile->profile_idc])
            continue;

#define check_flag(name) \
        if (profile->name < 2) { \
            if (profile->name != ptl->general_ ## name ## _constraint_flag) \
                continue; \
        }
        check_flag(max_14bit);
        check_flag(max_12bit);
        check_flag(max_10bit);
        check_flag(max_8bit);
        check_flag(max_422chroma);
        check_flag(max_420chroma);
        check_flag(max_monochrome);
        check_flag(intra);
        check_flag(one_picture_only);
        check_flag(lower_bit_rate);
#undef check_flag

        return profile;
    }

    return NULL;
}