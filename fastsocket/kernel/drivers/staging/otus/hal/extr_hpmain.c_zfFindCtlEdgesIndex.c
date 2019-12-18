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
typedef  size_t u8_t ;
struct zsHpPriv {int /*<<< orphan*/ * eepromImage; } ;
struct ar5416Eeprom {size_t* ctlIndex; } ;
struct TYPE_2__ {struct zsHpPriv* hpPrivate; } ;

/* Variables and functions */
 size_t AR5416_NUM_CTLS ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u8_t zfFindCtlEdgesIndex(zdev_t* dev, u8_t desired_CtlIndex)
{
    u8_t i;
    struct zsHpPriv* hpPriv;
    struct ar5416Eeprom* eepromImage;

    zmw_get_wlan_dev(dev);

    hpPriv = wd->hpPrivate;

    eepromImage = (struct ar5416Eeprom*)&(hpPriv->eepromImage[(1024+512)/4]);

    //for (i = 0; (i < AR5416_NUM_CTLS) && eepromImage->ctlIndex[i]; i++)
    for (i = 0; i < AR5416_NUM_CTLS; i++)
    {
        if(desired_CtlIndex == eepromImage->ctlIndex[i])
            break;
    }
    return i;
}