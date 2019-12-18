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
typedef  int /*<<< orphan*/  u8_t ;
typedef  int u32_t ;
struct TYPE_3__ {int /*<<< orphan*/  LEDCtrlFlag; } ;
struct TYPE_4__ {TYPE_1__ ledStruct; } ;

/* Variables and functions */
 scalar_t__ ZM_LED_CTRL_FLAG_ALPHA ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfHpLedCtrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfLedCtrl_BlinkWhenScan_Alpha(zdev_t* dev)
{
    static u32_t counter = 0;
    zmw_get_wlan_dev(dev);

    if(counter > 34)        // counter for 3 sec
    {
        wd->ledStruct.LEDCtrlFlag &= ~(u8_t)ZM_LED_CTRL_FLAG_ALPHA;
        counter = 0;
    }

    if( (counter % 3) < 2)
        zfHpLedCtrl(dev, 0, 1);
    else
        zfHpLedCtrl(dev, 0, 0);

    counter++;
}