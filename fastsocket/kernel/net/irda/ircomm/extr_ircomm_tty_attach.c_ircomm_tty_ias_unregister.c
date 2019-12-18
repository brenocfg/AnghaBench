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
struct ircomm_tty_cb {int /*<<< orphan*/ * ckey; int /*<<< orphan*/ * obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  irias_delete_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irlmp_unregister_client (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ircomm_tty_ias_unregister(struct ircomm_tty_cb *self)
{
	/* Remove LM-IAS object now so it is not reused.
	 * IrCOMM deals very poorly with multiple incoming connections.
	 * It should looks a lot more like IrNET, and "dup" a server TSAP
	 * to the application TSAP (based on various rules).
	 * This is a cheap workaround allowing multiple clients to
	 * connect to us. It will not always work.
	 * Each IrCOMM socket has an IAS entry. Incoming connection will
	 * pick the first one found. So, when we are fully connected,
	 * we remove our IAS entries so that the next IAS entry is used.
	 * We do that for *both* client and server, because a server
	 * can also create client instances.
	 * Jean II */
	if (self->obj) {
		irias_delete_object(self->obj);
		self->obj = NULL;
	}

#if 0
	/* Remove discovery handler.
	 * While we are connected, we no longer need to receive
	 * discovery events. This would be the case if there is
	 * multiple IrLAP interfaces. Jean II */
	if (self->ckey) {
		irlmp_unregister_client(self->ckey);
		self->ckey = NULL;
	}
#endif
}