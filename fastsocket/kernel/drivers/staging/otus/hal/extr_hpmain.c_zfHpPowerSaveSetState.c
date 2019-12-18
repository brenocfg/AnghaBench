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
typedef  scalar_t__ u8_t ;
struct zsHpPriv {scalar_t__ hwFrequency; } ;
struct TYPE_2__ {struct zsHpPriv* hpPrivate; } ;

/* Variables and functions */
 scalar_t__ ZM_CH_G_14 ; 
 int /*<<< orphan*/  reg_write (int,int) ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfFlushDelayWrite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfHpPowerSaveSetState(zdev_t* dev, u8_t psState)
{
    struct zsHpPriv* hpPriv;

    zmw_get_wlan_dev(dev);
    hpPriv = wd->hpPrivate;

	//DbgPrint("INTO zfHpPowerSaveSetState");

    if ( psState == 0 ) //power up
    {
        //DbgPrint("zfHpPowerSaveSetState Wake up from PS\n");
        reg_write(0x982C, 0x0000a000); //wake up ADDAC
        reg_write(0x9808, 0x0);        //enable all agc gain and offset updates to a2
        //# bank 3
        if (((struct zsHpPriv*)wd->hpPrivate)->hwFrequency <= ZM_CH_G_14)
        {
            /* 11g */
            //reg_write (0x98f0,  0x01c00018);
            reg_write (0x98f0,  0x01c20098);//syn_on+RX_ON
        }
        else
        {
            /* 11a */
            //reg_write (0x98f0,  0x01400018);
            reg_write (0x98f0,  0x01420098);//syn_on+RX_ON
        }

        ////#bank 5
        //reg_write(0x98b0,  0x00000013);
        //reg_write(0x98e4,  0x00000002);


        zfFlushDelayWrite(dev);
    }
    else //power down
    {
        //DbgPrint("zfHpPowerSaveSetState Go to PS\n");
        //reg_write(0x982C, 0xa000a000);
        reg_write(0x9808, 0x8000000);    //disable all agc gain and offset updates to a2
        reg_write(0x982C, 0xa000a000);   //power down ADDAC
        //# bank 3
        if (((struct zsHpPriv*)wd->hpPrivate)->hwFrequency <= ZM_CH_G_14)
        {
            /* 11g */
            reg_write (0x98f0,  0x00c00018);//syn_off+RX_off
        }
        else
        {
            /* 11a */
            reg_write (0x98f0,  0x00400018);//syn_off+RX_off
        }

        ////#bank 5
        //reg_write(0x98b0,  0x000e0013);
        //reg_write(0x98e4,  0x00018002);


        zfFlushDelayWrite(dev);
    }
}