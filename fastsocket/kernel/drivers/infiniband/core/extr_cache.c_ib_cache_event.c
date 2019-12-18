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
struct ib_update_work {int /*<<< orphan*/  work; int /*<<< orphan*/  port_num; int /*<<< orphan*/  device; } ;
struct ib_event_handler {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_num; } ;
struct ib_event {scalar_t__ event; TYPE_1__ element; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IB_EVENT_CLIENT_REREGISTER ; 
 scalar_t__ IB_EVENT_GID_CHANGE ; 
 scalar_t__ IB_EVENT_LID_CHANGE ; 
 scalar_t__ IB_EVENT_PKEY_CHANGE ; 
 scalar_t__ IB_EVENT_PORT_ACTIVE ; 
 scalar_t__ IB_EVENT_PORT_ERR ; 
 scalar_t__ IB_EVENT_SM_CHANGE ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_cache_task ; 
 int /*<<< orphan*/  ib_wq ; 
 struct ib_update_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ib_cache_event(struct ib_event_handler *handler,
			   struct ib_event *event)
{
	struct ib_update_work *work;

	if (event->event == IB_EVENT_PORT_ERR    ||
	    event->event == IB_EVENT_PORT_ACTIVE ||
	    event->event == IB_EVENT_LID_CHANGE  ||
	    event->event == IB_EVENT_PKEY_CHANGE ||
	    event->event == IB_EVENT_SM_CHANGE   ||
	    event->event == IB_EVENT_CLIENT_REREGISTER ||
	    event->event == IB_EVENT_GID_CHANGE) {
		work = kmalloc(sizeof *work, GFP_ATOMIC);
		if (work) {
			INIT_WORK(&work->work, ib_cache_task);
			work->device   = event->device;
			work->port_num = event->element.port_num;
			queue_work(ib_wq, &work->work);
		}
	}
}