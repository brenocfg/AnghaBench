#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__** iface; } ;
typedef  TYPE_1__ joydata_t ;
struct TYPE_10__ {int /*<<< orphan*/  cookie; } ;
typedef  TYPE_2__ joy_elemdata_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* getElementValue ) (TYPE_4__**,int /*<<< orphan*/ ,TYPE_3__*) ;} ;
struct TYPE_11__ {int value; } ;
typedef  TYPE_3__ IOHIDEventStruct ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__**,int /*<<< orphan*/ ,TYPE_3__*) ; 

int joy_read_element(joydata_t *joy, joy_elemdata_t *elem)  {
    IOHIDEventStruct ev;

    memset(&ev, 0, sizeof(IOHIDEventStruct));

    (*joy->iface)->getElementValue(joy->iface, elem->cookie, &ev);

    return ev.value;
}