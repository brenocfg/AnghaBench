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
struct TYPE_3__ {int counter; } ;
struct TYPE_4__ {int supportMode; TYPE_1__ ledStruct; } ;

/* Variables and functions */
 int ZM_WIRELESS_MODE_24 ; 
 int ZM_WIRELESS_MODE_5 ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfHpLedCtrl (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfLedCtrlType2_scan(zdev_t* dev)
{
    zmw_get_wlan_dev(dev);

    // When doing scan, blink(Amber/Blue) and off per 500ms (about 400ms in our driver)
    //               _______                         _______
    // LED[0] ON    |       |       8       12      |       |
    // ------ OFF->-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+->>>...
    // LED[1] ON    0       4       |_______|       0       3
    //

    switch(wd->ledStruct.counter % 16)
    {
        case 0:   // case 0~3, LED[0] on
            if(wd->supportMode & ZM_WIRELESS_MODE_24)
            {
                zfHpLedCtrl(dev, 0, 1);
                zfHpLedCtrl(dev, 1, 0);
            }
            else
            {
                zfHpLedCtrl(dev, 1, 1);
                zfHpLedCtrl(dev, 0, 0);
            }
            break;

        case 8:   // case 8~11, LED[1] on
            if(wd->supportMode & ZM_WIRELESS_MODE_5)
            {
                zfHpLedCtrl(dev, 1, 1);
                zfHpLedCtrl(dev, 0, 0);
            }
            else
            {
                zfHpLedCtrl(dev, 0, 1);
                zfHpLedCtrl(dev, 1, 0);
            }
            break;

        default:  // others, all off
            zfHpLedCtrl(dev, 0, 0);
            zfHpLedCtrl(dev, 1, 0);
            break;
    }
}