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
typedef  int /*<<< orphan*/  mb_event_group_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* check_event ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MB_EVENT_NO_EVENTS ; 
 int /*<<< orphan*/  MB_SLAVE_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* slave_interface_ptr ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

mb_event_group_t mbc_slave_check_event(mb_event_group_t group)
{
    MB_SLAVE_CHECK((slave_interface_ptr != NULL),
                    MB_EVENT_NO_EVENTS,
                    "Slave interface is not correctly initialized.");
    MB_SLAVE_CHECK((slave_interface_ptr->check_event != NULL), 
                    MB_EVENT_NO_EVENTS,
                    "Slave interface is not correctly initialized.");
    mb_event_group_t event = slave_interface_ptr->check_event(group);
    return event;
}