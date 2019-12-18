#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ Config; scalar_t__ AssignedIRQ; } ;
struct pcmcia_socket {int state; int /*<<< orphan*/  dev; TYPE_2__* ops; scalar_t__ functions; scalar_t__ lock_count; TYPE_1__ irq; int /*<<< orphan*/  socket; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_status ) (struct pcmcia_socket*,int*) ;int /*<<< orphan*/  (* set_socket ) (struct pcmcia_socket*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* init ) (struct pcmcia_socket*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int SOCKET_INUSE ; 
 int SOCKET_PRESENT ; 
 int SS_POWERON ; 
 int /*<<< orphan*/  cb_free (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  cs_dbg (struct pcmcia_socket*,int,char*) ; 
 int /*<<< orphan*/  cs_socket_put (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  dead_socket ; 
 int /*<<< orphan*/  destroy_cis_cache (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int shutdown_delay ; 
 int /*<<< orphan*/  socket_remove_drivers (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  stub1 (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  stub2 (struct pcmcia_socket*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct pcmcia_socket*,int*) ; 

__attribute__((used)) static void socket_shutdown(struct pcmcia_socket *s)
{
	int status;

	cs_dbg(s, 4, "shutdown\n");

	socket_remove_drivers(s);
	s->state &= SOCKET_INUSE | SOCKET_PRESENT;
	msleep(shutdown_delay * 10);
	s->state &= SOCKET_INUSE;

	/* Blank out the socket state */
	s->socket = dead_socket;
	s->ops->init(s);
	s->ops->set_socket(s, &s->socket);
	s->irq.AssignedIRQ = s->irq.Config = 0;
	s->lock_count = 0;
	destroy_cis_cache(s);
#ifdef CONFIG_CARDBUS
	cb_free(s);
#endif
	s->functions = 0;

	/* give socket some time to power down */
	msleep(100);

	s->ops->get_status(s, &status);
	if (status & SS_POWERON) {
		dev_printk(KERN_ERR, &s->dev,
			   "*** DANGER *** unable to remove socket power\n");
	}

	cs_socket_put(s);
}