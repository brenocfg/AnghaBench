#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct TYPE_5__ {int /*<<< orphan*/  uapsdQ; } ;
struct TYPE_4__ {int /*<<< orphan*/  uapsdQ; } ;
struct TYPE_6__ {TYPE_2__ sta; TYPE_1__ ap; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_LV_0 ; 
 int /*<<< orphan*/  ZM_WLAN_STATE_CLOSEDED ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfAggRxFreeBuf (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfBssInfoDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfHpRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfHpStopRecv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfQueueDestroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfWlanReset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_msg0_init (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u16_t zfiWlanClose(zdev_t *dev)
{
	zmw_get_wlan_dev(dev);

	zm_msg0_init(ZM_LV_0, "enter");

	wd->state = ZM_WLAN_STATE_CLOSEDED;

	/* zfiWlanDisable(dev, 1); */
	zfWlanReset(dev);

	zfHpStopRecv(dev);

	/* Disable MAC */
	/* Disable PHY */
	/* Disable RF */

	zfHpRelease(dev);

	zfQueueDestroy(dev, wd->ap.uapsdQ);
	zfQueueDestroy(dev, wd->sta.uapsdQ);

	zfBssInfoDestroy(dev);

#ifdef ZM_ENABLE_AGGREGATION
	/* add by honda */
	zfAggRxFreeBuf(dev, 1);  /* 1 for release structure memory */
	/* end of add by honda */
#endif

	zm_msg0_init(ZM_LV_0, "exit");

	return 0;
}