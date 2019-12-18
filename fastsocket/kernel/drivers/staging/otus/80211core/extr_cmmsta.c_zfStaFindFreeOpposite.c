#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  u16_t ;
typedef  int s8_t ;
struct TYPE_5__ {int oppositeCount; TYPE_1__* oppositeInfo; } ;
struct TYPE_6__ {TYPE_2__ sta; } ;
struct TYPE_4__ {scalar_t__ valid; int /*<<< orphan*/  aliveCounter; int /*<<< orphan*/  macAddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_IBSS_PEER_ALIVE_COUNTER ; 
 int ZM_MAX_OPPOSITE_COUNT ; 
 TYPE_3__* wd ; 
 scalar_t__ zfMemoryIsEqual (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

s8_t zfStaFindFreeOpposite(zdev_t* dev, u16_t *sa, int *pFoundIdx)
{
    int oppositeCount;
    int i;

    zmw_get_wlan_dev(dev);

    oppositeCount = wd->sta.oppositeCount;

    for(i=0; i < ZM_MAX_OPPOSITE_COUNT; i++)
    {
        if ( oppositeCount == 0 )
        {
            break;
        }

        if ( wd->sta.oppositeInfo[i].valid == 0 )
        {
            continue;
        }

        oppositeCount--;
        if ( zfMemoryIsEqual((u8_t*) sa, wd->sta.oppositeInfo[i].macAddr, 6) )
        {
            //wd->sta.oppositeInfo[i].aliveCounter++;
            wd->sta.oppositeInfo[i].aliveCounter = ZM_IBSS_PEER_ALIVE_COUNTER;

            /* it is already stored */
            return 1;
        }
    }

    // Check if there's still space for new comer
    if ( wd->sta.oppositeCount == ZM_MAX_OPPOSITE_COUNT )
    {
        return -1;
    }

    // Find an unused slot for new peer station
    for(i=0; i < ZM_MAX_OPPOSITE_COUNT; i++)
    {
        if ( wd->sta.oppositeInfo[i].valid == 0 )
        {
            break;
        }
    }

    *pFoundIdx = i;
    return 0;
}