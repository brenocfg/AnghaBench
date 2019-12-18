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
typedef  scalar_t__ u32_t ;
struct TYPE_4__ {int RxMacStatus; } ;
struct TYPE_5__ {TYPE_1__ Data; } ;
struct zsAdditionInfo {int* PlcpHeader; TYPE_2__ Tail; } ;
struct TYPE_6__ {int modulationType; int rateField; int rxInfo; int CurrentRxRateUpdated; scalar_t__ CurrentRxRateKbps; } ;

/* Variables and functions */
 TYPE_3__* wd ; 
 scalar_t__ zfUpdateRxRate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfWlanUpdateRxRate(zdev_t *dev, struct zsAdditionInfo *addInfo)
{
	u32_t rxRateKbps;
	zmw_get_wlan_dev(dev);
	/* zm_msg1_mm(ZM_LV_0, "addInfo->Tail.Data.RxMacStatus =",
	*  addInfo->Tail.Data.RxMacStatus & 0x03);
	*/

	/* b5~b4: MPDU indication.                */
	/*        00: Single MPDU.                */
	/*        10: First MPDU of A-MPDU.       */
	/*        11: Middle MPDU of A-MPDU.      */
	/*        01: Last MPDU of A-MPDU.        */
	/* Only First MPDU and Single MPDU have PLCP header */
	/* First MPDU  : (mpduInd & 0x30) == 0x00 */
	/* Single MPDU : (mpduInd & 0x30) == 0x20 */
	if ((addInfo->Tail.Data.RxMacStatus & 0x10) == 0) {
		/* Modulation type */
		wd->modulationType = addInfo->Tail.Data.RxMacStatus & 0x03;
		switch (wd->modulationType) {
		/* CCK mode */
		case 0x0:
			wd->rateField = addInfo->PlcpHeader[0] & 0xff;
			wd->rxInfo = 0;
			break;
		/* Legacy-OFDM mode */
		case 0x1:
			wd->rateField = addInfo->PlcpHeader[0] & 0x0f;
			wd->rxInfo = 0;
			break;
		/* HT-OFDM mode */
		case 0x2:
			wd->rateField = addInfo->PlcpHeader[3];
			wd->rxInfo = addInfo->PlcpHeader[6];
			break;
		default:
			break;
		}

		rxRateKbps = zfUpdateRxRate(dev);
		if (wd->CurrentRxRateUpdated == 1) {
			if (rxRateKbps > wd->CurrentRxRateKbps)
				wd->CurrentRxRateKbps = rxRateKbps;
		} else {
			wd->CurrentRxRateKbps = rxRateKbps;
			wd->CurrentRxRateUpdated = 1;
		}
	}
}