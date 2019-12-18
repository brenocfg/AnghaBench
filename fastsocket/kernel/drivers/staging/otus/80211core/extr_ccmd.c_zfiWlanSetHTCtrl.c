#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  void* u8_t ;
typedef  scalar_t__ u32_t ;
struct TYPE_3__ {void* defaultTA; void* htCtrlSG; void* htCtrlSTBC; void* htCtrlBandwidth; void* preambleTypeHT; } ;
struct TYPE_4__ {scalar_t__ forceTxTPC; void* enableWDS; void* enableAggregation; TYPE_1__ sta; void* preambleType; } ;

/* Variables and functions */
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfiWlanSetHTCtrl(zdev_t *dev, u32_t *setting, u32_t forceTxTPC)
{
	zmw_get_wlan_dev(dev);

	wd->preambleType        = (u8_t)setting[0];
	wd->sta.preambleTypeHT  = (u8_t)setting[1];
	wd->sta.htCtrlBandwidth = (u8_t)setting[2];
	wd->sta.htCtrlSTBC      = (u8_t)setting[3];
	wd->sta.htCtrlSG        = (u8_t)setting[4];
	wd->sta.defaultTA       = (u8_t)setting[5];
	wd->enableAggregation   = (u8_t)setting[6];
	wd->enableWDS           = (u8_t)setting[7];

	wd->forceTxTPC          = forceTxTPC;
}