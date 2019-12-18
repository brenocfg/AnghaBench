#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ priv; } ;
typedef  TYPE_1__ wlandevice_t ;
typedef  int /*<<< orphan*/  hfa384x_t ;

/* Variables and functions */
 int /*<<< orphan*/  HFA384x_RID_CNFMAXDATALEN ; 
 int /*<<< orphan*/  WLAN_DATA_MAXLEN ; 
 int hfa384x_drvr_setconfig16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prism2sta_globalsetup(wlandevice_t *wlandev)
{
	hfa384x_t *hw = (hfa384x_t *) wlandev->priv;

	/* Set the maximum frame size */
	return hfa384x_drvr_setconfig16(hw, HFA384x_RID_CNFMAXDATALEN,
					WLAN_DATA_MAXLEN);
}