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
struct TYPE_4__ {scalar_t__ hats; scalar_t__ axes; scalar_t__ buttons; TYPE_2__** iface; } ;
typedef  TYPE_1__ joydata_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* Release ) (TYPE_2__**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__**) ; 

__attribute__((used)) static void joy_release_joystick(joydata_t *joy)    {
    (*joy->iface)->Release(joy->iface);

    joy->iface = NULL;

    if(joy->buttons)
        free(joy->buttons);

    if(joy->axes)
        free(joy->axes);

    if(joy->hats)
        free(joy->hats);
}