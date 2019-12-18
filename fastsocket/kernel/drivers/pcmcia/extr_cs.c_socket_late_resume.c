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
struct pcmcia_socket {int state; scalar_t__ resume_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_EVENT_CARD_INSERTION ; 
 int /*<<< orphan*/  CS_EVENT_PM_RESUME ; 
 int /*<<< orphan*/  CS_EVENT_PRI_LOW ; 
 int SOCKET_PRESENT ; 
 int SOCKET_SUSPEND ; 
 int /*<<< orphan*/  cs_dbg (struct pcmcia_socket*,int,char*) ; 
 int /*<<< orphan*/  destroy_cis_cache (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  send_event (struct pcmcia_socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int socket_insert (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  socket_remove_drivers (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  socket_shutdown (struct pcmcia_socket*) ; 
 scalar_t__ verify_cis_cache (struct pcmcia_socket*) ; 

__attribute__((used)) static int socket_late_resume(struct pcmcia_socket *skt)
{
	if (!(skt->state & SOCKET_PRESENT)) {
		skt->state &= ~SOCKET_SUSPEND;
		return socket_insert(skt);
	}

	if (skt->resume_status == 0) {
		/*
		 * FIXME: need a better check here for cardbus cards.
		 */
		if (verify_cis_cache(skt) != 0) {
			cs_dbg(skt, 4, "cis mismatch - different card\n");
			socket_remove_drivers(skt);
			destroy_cis_cache(skt);
			/*
			 * Workaround: give DS time to schedule removal.
			 * Remove me once the 100ms delay is eliminated
			 * in ds.c
			 */
			msleep(200);
			send_event(skt, CS_EVENT_CARD_INSERTION, CS_EVENT_PRI_LOW);
		} else {
			cs_dbg(skt, 4, "cis matches cache\n");
			send_event(skt, CS_EVENT_PM_RESUME, CS_EVENT_PRI_LOW);
		}
	} else {
		socket_shutdown(skt);
	}

	skt->state &= ~SOCKET_SUSPEND;

	return 0;
}