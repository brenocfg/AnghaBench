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
struct pcmcia_socket {int state; int /*<<< orphan*/  skt_mutex; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int SOCKET_PRESENT ; 
 int /*<<< orphan*/  cs_dbg (struct pcmcia_socket*,int,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int socket_insert (struct pcmcia_socket*) ; 

int pcmcia_insert_card(struct pcmcia_socket *skt)
{
	int ret;

	cs_dbg(skt, 1, "user insert request\n");

	mutex_lock(&skt->skt_mutex);
	do {
		if (skt->state & SOCKET_PRESENT) {
			ret = -EBUSY;
			break;
		}
		if (socket_insert(skt) == -ENODEV) {
			ret = -ENODEV;
			break;
		}
		ret = 0;
	} while (0);
	mutex_unlock(&skt->skt_mutex);

	return ret;
}