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
struct pcmcia_socket {int state; TYPE_1__* ops; int /*<<< orphan*/  socket; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* suspend ) (struct pcmcia_socket*) ;int /*<<< orphan*/  (* set_socket ) (struct pcmcia_socket*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CS_EVENT_PM_SUSPEND ; 
 int /*<<< orphan*/  CS_EVENT_PRI_LOW ; 
 int EBUSY ; 
 int SOCKET_SUSPEND ; 
 int /*<<< orphan*/  dead_socket ; 
 int /*<<< orphan*/  send_event (struct pcmcia_socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct pcmcia_socket*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct pcmcia_socket*) ; 

__attribute__((used)) static int socket_suspend(struct pcmcia_socket *skt)
{
	if (skt->state & SOCKET_SUSPEND)
		return -EBUSY;

	send_event(skt, CS_EVENT_PM_SUSPEND, CS_EVENT_PRI_LOW);
	skt->socket = dead_socket;
	skt->ops->set_socket(skt, &skt->socket);
	if (skt->ops->suspend)
		skt->ops->suspend(skt);
	skt->state |= SOCKET_SUSPEND;

	return 0;
}