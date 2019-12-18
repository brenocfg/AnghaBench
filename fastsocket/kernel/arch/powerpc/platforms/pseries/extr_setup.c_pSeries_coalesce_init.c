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
struct hvcall_mpp_x_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_FEATURE_CMO ; 
 int /*<<< orphan*/  FW_FEATURE_XCMO ; 
 scalar_t__ firmware_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h_get_mpp_x (struct hvcall_mpp_x_data*) ; 
 int /*<<< orphan*/  powerpc_firmware_features ; 

void pSeries_coalesce_init(void)
{
	struct hvcall_mpp_x_data mpp_x_data;

	if (firmware_has_feature(FW_FEATURE_CMO) && !h_get_mpp_x(&mpp_x_data))
		powerpc_firmware_features |= FW_FEATURE_XCMO;
	else
		powerpc_firmware_features &= ~FW_FEATURE_XCMO;
}