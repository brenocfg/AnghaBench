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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  scalar_t__ u32_t ;
struct TYPE_2__ {scalar_t__ swSniffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_LV_0 ; 
 int /*<<< orphan*/  ZM_LV_1 ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfHpSetSnifferMode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zm_msg1_mm (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfiWlanSetPacketTypePromiscuous(zdev_t *dev, u32_t setValue)
{
	zmw_get_wlan_dev(dev);

	wd->swSniffer = setValue;
	zm_msg1_mm(ZM_LV_0, "wd->swSniffer ", wd->swSniffer);
	if (setValue) {
		/* write register for sniffer mode */
		zfHpSetSnifferMode(dev, 1);
		zm_msg0_mm(ZM_LV_1, "enalbe sniffer mode");
	} else {
		zfHpSetSnifferMode(dev, 0);
		zm_msg0_mm(ZM_LV_0, "disalbe sniffer mode");
	}
}