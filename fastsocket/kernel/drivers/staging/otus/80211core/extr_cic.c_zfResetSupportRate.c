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
typedef  int u8_t ;
struct TYPE_2__ {int bRate; int bRateBasic; int gRate; int gRateBasic; } ;

/* Variables and functions */
#define  ZM_DEFAULT_SUPPORT_RATE_DISCONNECT 131 
#define  ZM_DEFAULT_SUPPORT_RATE_IBSS_AG 130 
#define  ZM_DEFAULT_SUPPORT_RATE_IBSS_B 129 
#define  ZM_DEFAULT_SUPPORT_RATE_ZERO 128 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfResetSupportRate(zdev_t* dev, u8_t type)
{
    zmw_get_wlan_dev(dev);

    switch(type)
    {
    case ZM_DEFAULT_SUPPORT_RATE_ZERO:
        wd->bRate = 0;
        wd->bRateBasic = 0;
        wd->gRate = 0;
        wd->gRateBasic = 0;
        break;
    case ZM_DEFAULT_SUPPORT_RATE_DISCONNECT:
        wd->bRate = 0xf;
        wd->bRateBasic = 0xf;
        wd->gRate = 0xff;
        wd->gRateBasic = 0x15;
        break;
    case ZM_DEFAULT_SUPPORT_RATE_IBSS_B:
        wd->bRate = 0xf;
        wd->bRateBasic = 0xf;
        wd->gRate = 0;
        wd->gRateBasic = 0;
        break;
    case ZM_DEFAULT_SUPPORT_RATE_IBSS_AG:
        wd->bRate = 0xf;
        wd->bRateBasic = 0xf;
        wd->gRate = 0xff;
        wd->gRateBasic = 0;
        break;
    }
}