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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_1__ req; } ;
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
#define  QLCNIC_SET_FAC_DEF_MAC 129 
#define  QLCNIC_SET_STATION_MAC 128 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

void qlcnic_83xx_configure_mac(struct qlcnic_adapter *adapter, u8 *mac,
			       u8 type, struct qlcnic_cmd_args *cmd)
{
	switch (type) {
	case QLCNIC_SET_STATION_MAC:
	case QLCNIC_SET_FAC_DEF_MAC:
		memcpy(&cmd->req.arg[2], mac, sizeof(u32));
		memcpy(&cmd->req.arg[3], &mac[4], sizeof(u16));
		break;
	}
	cmd->req.arg[1] = type;
}