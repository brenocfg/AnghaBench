#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_2__ {int fw_type; } ;

/* Variables and functions */
 int QLCNIC_FLASH_ROMIMAGE ; 
#define  QLCNIC_UNIFIED_ROMIMAGE 129 
#define  QLCNIC_UNKNOWN_ROMIMAGE 128 

__attribute__((used)) static void
qlcnic_get_next_fwtype(struct qlcnic_adapter *adapter)
{
	u8 fw_type;

	switch (adapter->ahw->fw_type) {
	case QLCNIC_UNKNOWN_ROMIMAGE:
		fw_type = QLCNIC_UNIFIED_ROMIMAGE;
		break;

	case QLCNIC_UNIFIED_ROMIMAGE:
	default:
		fw_type = QLCNIC_FLASH_ROMIMAGE;
		break;
	}

	adapter->ahw->fw_type = fw_type;
}