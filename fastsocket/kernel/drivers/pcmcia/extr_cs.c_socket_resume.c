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
struct pcmcia_socket {int state; } ;

/* Variables and functions */
 int EBUSY ; 
 int SOCKET_SUSPEND ; 
 int /*<<< orphan*/  socket_early_resume (struct pcmcia_socket*) ; 
 int socket_late_resume (struct pcmcia_socket*) ; 

__attribute__((used)) static int socket_resume(struct pcmcia_socket *skt)
{
	if (!(skt->state & SOCKET_SUSPEND))
		return -EBUSY;

	socket_early_resume(skt);
	return socket_late_resume(skt);
}