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
typedef  size_t u8_t ;
typedef  size_t u16_t ;

/* Variables and functions */
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u16_t zfFindMinimumUtilizationChannelIndex(zdev_t* dev, u16_t* array, u16_t count)
{
    u8_t   i;
    u16_t  tempMinIndex, tempMinValue;

    zmw_get_wlan_dev(dev);

    i = 1;
    tempMinIndex = 0;
    tempMinValue = array[tempMinIndex];
    while( i< count )
    {
        if( array[i] < tempMinValue )
        {
            tempMinValue = array[i];
            tempMinIndex = i;
        }
        i++;
    }

    return tempMinIndex;
}