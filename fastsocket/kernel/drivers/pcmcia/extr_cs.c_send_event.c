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
struct pcmcia_socket {int state; TYPE_1__* callback; } ;
typedef  int /*<<< orphan*/  event_t ;
struct TYPE_2__ {int (* event ) (struct pcmcia_socket*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int SOCKET_CARDBUS ; 
 int /*<<< orphan*/  cs_dbg (struct pcmcia_socket*,int,char*,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int stub1 (struct pcmcia_socket*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_event(struct pcmcia_socket *s, event_t event, int priority)
{
	int ret;

	if (s->state & SOCKET_CARDBUS)
		return 0;

	cs_dbg(s, 1, "send_event(event %d, pri %d, callback 0x%p)\n",
	   event, priority, s->callback);

	if (!s->callback)
		return 0;
	if (!try_module_get(s->callback->owner))
		return 0;

	ret = s->callback->event(s, event, priority);

	module_put(s->callback->owner);

	return ret;
}