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
typedef  int u32 ;
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_PEG_TUNE_CAPABILITY ; 
 int QLCNIC_PEG_TUNE_MN_PRESENT ; 
 int QLCRD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qlcnic_has_mn(struct qlcnic_adapter *adapter)
{
	u32 capability;
	capability = 0;

	capability = QLCRD32(adapter, QLCNIC_PEG_TUNE_CAPABILITY);
	if (capability & QLCNIC_PEG_TUNE_MN_PRESENT)
		return 1;

	return 0;
}