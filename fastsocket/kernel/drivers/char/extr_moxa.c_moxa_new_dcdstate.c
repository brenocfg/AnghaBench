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
typedef  int u8 ;
struct tty_struct {int dummy; } ;
struct moxa_port {int DCDState; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 scalar_t__ C_CLOCAL (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_hangup (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void moxa_new_dcdstate(struct moxa_port *p, u8 dcd)
{
	struct tty_struct *tty;
	dcd = !!dcd;

	if (dcd != p->DCDState) {
		tty = tty_port_tty_get(&p->port);
		if (tty && C_CLOCAL(tty) && !dcd)
			tty_hangup(tty);
		tty_kref_put(tty);
	}
	p->DCDState = dcd;
}