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
struct pcmcia_socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_EVENT_CARD_REMOVAL ; 
 int /*<<< orphan*/  CS_EVENT_PRI_HIGH ; 
 int /*<<< orphan*/  cs_dbg (struct pcmcia_socket*,int,char*) ; 
 int /*<<< orphan*/  send_event (struct pcmcia_socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void socket_remove_drivers(struct pcmcia_socket *skt)
{
	cs_dbg(skt, 4, "remove_drivers\n");

	send_event(skt, CS_EVENT_CARD_REMOVAL, CS_EVENT_PRI_HIGH);
}