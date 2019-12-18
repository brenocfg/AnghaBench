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
typedef  char u8_t ;
typedef  int u16_t ;

/* Variables and functions */
 int /*<<< orphan*/  zfCoreSetIsoName (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  zfHpGetRegulationTable (int /*<<< orphan*/ *,int,int,int) ; 

void zfHpGetRegulationTablefromRegionCode(zdev_t* dev, u16_t regionCode)
{
    u16_t c_lo = 2000, c_hi = 6000; //default channel is all enable
    u8_t isoName[3] = {'N', 'A', 0};

    zfCoreSetIsoName(dev, isoName);

    zfHpGetRegulationTable(dev, regionCode, c_lo, c_hi);
}