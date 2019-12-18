#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int configurationVersion; int lengthSizeMinusOne; int general_profile_compatibility_flags; int general_constraint_indicator_flags; scalar_t__ min_spatial_segmentation_idc; } ;
typedef  TYPE_1__ HEVCDecoderConfigurationRecord ;

/* Variables and functions */
 scalar_t__ MAX_SPATIAL_SEGMENTATION ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hvcc_init(HEVCDecoderConfigurationRecord *hvcc)
{
    memset(hvcc, 0, sizeof(HEVCDecoderConfigurationRecord));
    hvcc->configurationVersion = 1;
    hvcc->lengthSizeMinusOne   = 3; // 4 bytes

    /*
     * The following fields have all their valid bits set by default,
     * the ProfileTierLevel parsing code will unset them when needed.
     */
    hvcc->general_profile_compatibility_flags = 0xffffffff;
    hvcc->general_constraint_indicator_flags  = 0xffffffffffff;

    /*
     * Initialize this field with an invalid value which can be used to detect
     * whether we didn't see any VUI (in which case it should be reset to zero).
     */
    hvcc->min_spatial_segmentation_idc = MAX_SPATIAL_SEGMENTATION + 1;
}