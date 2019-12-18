#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  scalar_t__ u8_t ;
typedef  scalar_t__ u16_t ;

/* Variables and functions */
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u16_t zfComputeBssInfoWeightValue(zdev_t *dev, u8_t isBMode, u8_t isHT, u8_t isHT40, u8_t signalStrength)
{
	u8_t  weightOfB           = 0;
	u8_t  weightOfAGBelowThr  = 0;
	u8_t  weightOfAGUpThr     = 15;
	u8_t  weightOfN20BelowThr = 15;
	u8_t  weightOfN20UpThr    = 30;
	u8_t  weightOfN40BelowThr = 16;
	u8_t  weightOfN40UpThr    = 32;

    zmw_get_wlan_dev(dev);

    if( isBMode == 0 )
        return (signalStrength + weightOfB);    // pure b mode , do not add the weight value for this AP !
    else
    {
        if( isHT == 0 && isHT40 == 0 )
        { // a , g , b/g mode ! add the weight value 15 for this AP if it's signal strength is more than some value !
            if( signalStrength < 18 ) // -77 dBm
				return signalStrength + weightOfAGBelowThr;
			else
				return (signalStrength + weightOfAGUpThr);
        }
        else if( isHT == 1 && isHT40 == 0 )
        { // 80211n mode use 20MHz
            if( signalStrength < 23 ) // -72 dBm
                return (signalStrength + weightOfN20BelowThr);
            else
                return (signalStrength + weightOfN20UpThr);
        }
        else // isHT == 1 && isHT40 == 1
        { // 80211n mode use 40MHz
            if( signalStrength < 16 ) // -79 dBm
                return (signalStrength + weightOfN40BelowThr);
            else
                return (signalStrength + weightOfN40UpThr);
        }
    }
}