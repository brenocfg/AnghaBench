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
struct TYPE_4__ {int open; TYPE_2__** iface; } ;
typedef  TYPE_1__ joydata_t ;
struct TYPE_5__ {scalar_t__ (* open ) (TYPE_2__**,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ stub1 (TYPE_2__**,int /*<<< orphan*/ ) ; 

int joy_open_joystick(joydata_t *joy)   {
    if((*joy->iface)->open(joy->iface, 0))  {
        return 0;
    }

    joy->open = 1;

    return 1;
}