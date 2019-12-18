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
typedef  int u16_t ;
struct TYPE_2__ {int txMCS; int txMT; } ;

/* Variables and functions */
 int ZM_ERR_INVALID_TX_RATE ; 
 int ZM_SUCCESS ; 
 TYPE_1__* wd ; 
 int* zcRateToMCS ; 
 int* zcRateToMT ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u16_t zfiWlanSetTxRate(zdev_t *dev, u16_t rate)
{
	/* jhlee HT 0 */
	zmw_get_wlan_dev(dev);

	if (rate <= 12) {
		wd->txMCS = zcRateToMCS[rate];
		wd->txMT = zcRateToMT[rate];
		return ZM_SUCCESS;
	} else if ((rate <= 28) || (rate == 13 + 32)) {
		wd->txMCS = rate - 12 - 1;
		wd->txMT = 2;
		return ZM_SUCCESS;
	}

	return ZM_ERR_INVALID_TX_RATE;
}