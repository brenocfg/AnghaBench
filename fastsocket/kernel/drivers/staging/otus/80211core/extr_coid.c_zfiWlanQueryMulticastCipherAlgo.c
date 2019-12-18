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
struct TYPE_3__ {int currentAuthMode; int* rsnIe; int /*<<< orphan*/  encryMode; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_AES ; 
#define  ZM_AUTH_MODE_WPA 131 
#define  ZM_AUTH_MODE_WPA2 130 
#define  ZM_AUTH_MODE_WPA2PSK 129 
#define  ZM_AUTH_MODE_WPAPSK 128 
 int /*<<< orphan*/  ZM_TKIP ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u8_t zfiWlanQueryMulticastCipherAlgo(zdev_t *dev)
{
    zmw_get_wlan_dev(dev);

    switch( wd->sta.currentAuthMode )
    {
        case ZM_AUTH_MODE_WPA2PSK:
        case ZM_AUTH_MODE_WPA2:
            if ( wd->sta.rsnIe[7] == 2 )
            {
                return ZM_TKIP;
            }
            else
            {
                return ZM_AES;
            }
            break;

        case ZM_AUTH_MODE_WPAPSK:
        case ZM_AUTH_MODE_WPA:
            if ( wd->sta.rsnIe[11] == 2 )
            {
                return ZM_TKIP;
            }
            else
            {
                return ZM_AES;
            }
            break;

        default:
            return wd->sta.encryMode;
    }
}