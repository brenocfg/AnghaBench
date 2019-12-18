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
struct TYPE_5__ {TYPE_1__* oppositeInfo; } ;
struct TYPE_6__ {TYPE_2__ sta; } ;
struct TYPE_4__ {int /*<<< orphan*/  aliveCounter; scalar_t__ valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_IBSS_PEER_ALIVE_COUNTER ; 
 int ZM_MAX_OPPOSITE_COUNT ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfStaInitOppositeInfo(zdev_t* dev)
{
    int i;

    zmw_get_wlan_dev(dev);

    for(i=0; i<ZM_MAX_OPPOSITE_COUNT; i++)
    {
        wd->sta.oppositeInfo[i].valid = 0;
        wd->sta.oppositeInfo[i].aliveCounter = ZM_IBSS_PEER_ALIVE_COUNTER;
    }
}