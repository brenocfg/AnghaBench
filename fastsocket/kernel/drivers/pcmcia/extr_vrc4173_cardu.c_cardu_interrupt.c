#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int events; int /*<<< orphan*/  tq_work; int /*<<< orphan*/  event_lock; } ;
typedef  TYPE_1__ vrc4173_socket_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  cardu_bh ; 
 int get_events (TYPE_1__*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cardu_interrupt(int irq, void *dev_id)
{
	vrc4173_socket_t *socket = (vrc4173_socket_t *)dev_id;
	uint16_t events;

	INIT_WORK(&socket->tq_work, cardu_bh, socket);

	events = get_events(socket);
	if (events) {
		spin_lock(&socket->event_lock);
		socket->events |= events;
		spin_unlock(&socket->event_lock);
		schedule_work(&socket->tq_work);
	}
}