#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pcmcia_socket {int /*<<< orphan*/  socket_released; int /*<<< orphan*/  socket_list; scalar_t__ thread; int /*<<< orphan*/  ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  cs_dbg (struct pcmcia_socket*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_socket_list_rwsem ; 
 int /*<<< orphan*/  release_cis_mem (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  release_resource_db (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void pcmcia_unregister_socket(struct pcmcia_socket *socket)
{
	if (!socket)
		return;

	cs_dbg(socket, 0, "pcmcia_unregister_socket(0x%p)\n", socket->ops);

	if (socket->thread)
		kthread_stop(socket->thread);

	release_cis_mem(socket);

	/* remove from our own list */
	down_write(&pcmcia_socket_list_rwsem);
	list_del(&socket->socket_list);
	up_write(&pcmcia_socket_list_rwsem);

	/* wait for sysfs to drop all references */
	release_resource_db(socket);
	wait_for_completion(&socket->socket_released);
}