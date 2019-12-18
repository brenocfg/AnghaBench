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
typedef  size_t u16_t ;
struct TYPE_2__ {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 size_t ZM_VAP_PORT_NUMBER ; 
 TYPE_1__* vap ; 

u16_t zfLnxGetVapId(zdev_t* dev)
{
    u16_t i;

    for (i=0; i<ZM_VAP_PORT_NUMBER; i++)
    {
        if (vap[i].dev == dev)
        {
            return i;
        }
    }
    return 0xffff;
}