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
typedef  int /*<<< orphan*/  u32_t ;
struct TYPE_3__ {int /*<<< orphan*/  defaultTA; int /*<<< orphan*/  htCtrlSG; int /*<<< orphan*/  htCtrlSTBC; int /*<<< orphan*/  htCtrlBandwidth; int /*<<< orphan*/  preambleTypeHT; } ;
struct TYPE_4__ {int /*<<< orphan*/  forceTxTPC; int /*<<< orphan*/  enableWDS; int /*<<< orphan*/  enableAggregation; TYPE_1__ sta; int /*<<< orphan*/  preambleType; } ;

/* Variables and functions */
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfiWlanQueryHTCtrl(zdev_t *dev, u32_t *setting, u32_t *forceTxTPC)
{
	zmw_get_wlan_dev(dev);

	setting[0] = wd->preambleType;
	setting[1] = wd->sta.preambleTypeHT;
	setting[2] = wd->sta.htCtrlBandwidth;
	setting[3] = wd->sta.htCtrlSTBC;
	setting[4] = wd->sta.htCtrlSG;
	setting[5] = wd->sta.defaultTA;
	setting[6] = wd->enableAggregation;
	setting[7] = wd->enableWDS;

	*forceTxTPC = wd->forceTxTPC;
}