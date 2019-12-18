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
typedef  int /*<<< orphan*/  u16_t ;
struct TYPE_2__ {int /*<<< orphan*/  frequency; } ;

/* Variables and functions */
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfChGetFirstChannel (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfCoreSetFrequency (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfHpGetRegulationTablefromCountry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfHpGetRegulationTablefromRegionCode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfiWlanSetRegulatory(zdev_t* dev, u8_t CCS, u16_t Code, u8_t bfirstChannel)
{
    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    if (CCS)
    {
        /* Reset Regulation Table by Country Code */
        zfHpGetRegulationTablefromCountry(dev, Code);
    }
    else
    {
        /* Reset Regulation Table by Region Code */
        zfHpGetRegulationTablefromRegionCode(dev, Code);
    }

    if (bfirstChannel) {
        zmw_enter_critical_section(dev);
        wd->frequency = zfChGetFirstChannel(dev, NULL);
        zmw_leave_critical_section(dev);
        zfCoreSetFrequency(dev, wd->frequency);
    }
}