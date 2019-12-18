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
struct TYPE_2__ {int bRate; int bRateBasic; } ;

/* Variables and functions */
 TYPE_1__* wd ; 
 int* zg11bRateTbl ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfiWlanQuerySupportRate(zdev_t* dev, u8_t* rateArray, u8_t* pLength)
{
    u8_t   i, j=0;

    zmw_get_wlan_dev(dev);

    for( i=0; i<4; i++ )
    {
        if ( wd->bRate & (0x1 << i) )
        {
            rateArray[j] = zg11bRateTbl[i] +
                           ((wd->bRateBasic & (0x1<<i))<<(7-i));
            j++;
        }
    }

    *pLength = j;
}