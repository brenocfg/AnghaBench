#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* UINT ;
struct TYPE_9__ {void* SecurityLogSwitchType; void* PacketLogSwitchType; } ;
struct TYPE_8__ {int /*<<< orphan*/  SecurityLogger; int /*<<< orphan*/  PacketLogger; TYPE_5__ LogSetting; } ;
struct TYPE_7__ {int /*<<< orphan*/  SecurityLogSwitchType; int /*<<< orphan*/  PacketLogSwitchType; } ;
typedef  TYPE_1__ HUB_LOG ;
typedef  TYPE_2__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (TYPE_5__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  SetLogSwitchType (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void SetHubLogSettingEx(HUB *h, HUB_LOG *setting, bool no_change_switch_type)
{
	UINT i1, i2;
	// Validate arguments
	if (setting == NULL || h == NULL)
	{
		return;
	}

	i1 = h->LogSetting.PacketLogSwitchType;
	i2 = h->LogSetting.SecurityLogSwitchType;

	Copy(&h->LogSetting, setting, sizeof(HUB_LOG));

	if (no_change_switch_type)
	{
		h->LogSetting.PacketLogSwitchType = i1;
		h->LogSetting.SecurityLogSwitchType = i2;
	}

	// Packet logger configuration
	SetLogSwitchType(h->PacketLogger, setting->PacketLogSwitchType);
	SetLogSwitchType(h->SecurityLogger, setting->SecurityLogSwitchType);
}