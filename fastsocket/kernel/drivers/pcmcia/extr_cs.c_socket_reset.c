#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; } ;
struct pcmcia_socket {TYPE_1__* ops; TYPE_2__ socket; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_status ) (struct pcmcia_socket*,int*) ;int /*<<< orphan*/  (* set_socket ) (struct pcmcia_socket*,TYPE_2__*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int ETIMEDOUT ; 
 int SS_DETECT ; 
 int SS_OUTPUT_ENA ; 
 int SS_READY ; 
 int SS_RESET ; 
 int /*<<< orphan*/  cs_dbg (struct pcmcia_socket*,int,char*) ; 
 int /*<<< orphan*/  cs_err (struct pcmcia_socket*,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ reset_time ; 
 int /*<<< orphan*/  stub1 (struct pcmcia_socket*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (struct pcmcia_socket*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (struct pcmcia_socket*,int*) ; 
 int /*<<< orphan*/  udelay (long) ; 
 int unreset_check ; 
 int unreset_delay ; 
 int unreset_limit ; 

__attribute__((used)) static int socket_reset(struct pcmcia_socket *skt)
{
	int status, i;

	cs_dbg(skt, 4, "reset\n");

	skt->socket.flags |= SS_OUTPUT_ENA | SS_RESET;
	skt->ops->set_socket(skt, &skt->socket);
	udelay((long)reset_time);

	skt->socket.flags &= ~SS_RESET;
	skt->ops->set_socket(skt, &skt->socket);

	msleep(unreset_delay * 10);
	for (i = 0; i < unreset_limit; i++) {
		skt->ops->get_status(skt, &status);

		if (!(status & SS_DETECT))
			return -ENODEV;

		if (status & SS_READY)
			return 0;

		msleep(unreset_check * 10);
	}

	cs_err(skt, "time out after reset.\n");
	return -ETIMEDOUT;
}