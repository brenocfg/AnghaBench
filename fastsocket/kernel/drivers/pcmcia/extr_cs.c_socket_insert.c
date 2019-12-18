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
struct pcmcia_socket {int state; int /*<<< orphan*/  sock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_EVENT_CARD_INSERTION ; 
 int /*<<< orphan*/  CS_EVENT_PRI_LOW ; 
 int ENODEV ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 int SOCKET_CARDBUS ; 
 int SOCKET_CARDBUS_CONFIG ; 
 int SOCKET_PRESENT ; 
 int /*<<< orphan*/  cb_alloc (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  cs_dbg (struct pcmcia_socket*,int,char*) ; 
 int /*<<< orphan*/  cs_socket_get (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_event (struct pcmcia_socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_delay ; 
 int socket_setup (struct pcmcia_socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_shutdown (struct pcmcia_socket*) ; 

__attribute__((used)) static int socket_insert(struct pcmcia_socket *skt)
{
	int ret;

	cs_dbg(skt, 4, "insert\n");

	if (!cs_socket_get(skt))
		return -ENODEV;

	ret = socket_setup(skt, setup_delay);
	if (ret == 0) {
		skt->state |= SOCKET_PRESENT;

		dev_printk(KERN_NOTICE, &skt->dev,
			   "pccard: %s card inserted into slot %d\n",
			   (skt->state & SOCKET_CARDBUS) ? "CardBus" : "PCMCIA",
			   skt->sock);

#ifdef CONFIG_CARDBUS
		if (skt->state & SOCKET_CARDBUS) {
			cb_alloc(skt);
			skt->state |= SOCKET_CARDBUS_CONFIG;
		}
#endif
		cs_dbg(skt, 4, "insert done\n");

		send_event(skt, CS_EVENT_CARD_INSERTION, CS_EVENT_PRI_LOW);
	} else {
		socket_shutdown(skt);
	}

	return ret;
}