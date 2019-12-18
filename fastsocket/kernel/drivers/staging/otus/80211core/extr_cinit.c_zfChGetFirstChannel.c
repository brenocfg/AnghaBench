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
struct TYPE_5__ {TYPE_1__* allowChannel; } ;
struct TYPE_6__ {TYPE_2__ regulationTable; } ;
struct TYPE_4__ {int channelFlags; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int ZM_REG_FLAG_CHANNEL_PASSIVE ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u16_t zfChGetFirstChannel(zdev_t* dev, u8_t* pbPassive)
{
    u8_t   bPassive;

    zmw_get_wlan_dev(dev);

    /* Avoid NULL value */
    if ( pbPassive == NULL )
    {
        pbPassive = &bPassive;
    }

   if ( wd->regulationTable.allowChannel[0].channelFlags & ZM_REG_FLAG_CHANNEL_PASSIVE )
    {
        *pbPassive = TRUE;
    }
    else
    {
        *pbPassive = FALSE;
    }

    return wd->regulationTable.allowChannel[0].channel;
}