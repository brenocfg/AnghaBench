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
struct pcmcia_socket {int state; int /*<<< orphan*/  skt_mutex; TYPE_1__* callback; } ;
struct TYPE_2__ {int (* suspend ) (struct pcmcia_socket*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int EPERM ; 
 int SOCKET_CARDBUS ; 
 int SOCKET_PRESENT ; 
 int /*<<< orphan*/  cs_dbg (struct pcmcia_socket*,int,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int socket_suspend (struct pcmcia_socket*) ; 
 int stub1 (struct pcmcia_socket*) ; 

int pcmcia_suspend_card(struct pcmcia_socket *skt)
{
	int ret;

	cs_dbg(skt, 1, "suspending socket\n");

	mutex_lock(&skt->skt_mutex);
	do {
		if (!(skt->state & SOCKET_PRESENT)) {
			ret = -ENODEV;
			break;
		}
		if (skt->state & SOCKET_CARDBUS) {
			ret = -EPERM;
			break;
		}
		if (skt->callback) {
			ret = skt->callback->suspend(skt);
			if (ret)
				break;
		}
		ret = socket_suspend(skt);
	} while (0);
	mutex_unlock(&skt->skt_mutex);

	return ret;
}