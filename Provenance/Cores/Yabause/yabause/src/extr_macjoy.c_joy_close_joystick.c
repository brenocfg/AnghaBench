#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ open; TYPE_2__** iface; } ;
typedef  TYPE_1__ joydata_t ;
struct TYPE_5__ {scalar_t__ (* close ) (TYPE_2__**) ;} ;
typedef  scalar_t__ IOReturn ;

/* Variables and functions */
 scalar_t__ kIOReturnNotOpen ; 
 scalar_t__ kIOReturnSuccess ; 
 scalar_t__ stub1 (TYPE_2__**) ; 

int joy_close_joystick(joydata_t *joy)  {
    IOReturn rv;

    if(!joy->open)  {
        return 1;
    }

    rv = (*joy->iface)->close(joy->iface);

    if(rv == kIOReturnNotOpen) {
        /* The device wasn't open so it can't be closed. */
        return 1;
    }
    else if(rv != kIOReturnSuccess)    {
        return 0;
    }

    joy->open = 0;

    return 1;
}