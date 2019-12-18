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
struct tty_struct {struct moxa_port* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct moxa_port {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_NORMAL_ACTIVE ; 
 int /*<<< orphan*/  MoxaPortFlushData (struct moxa_port*,int) ; 
 int /*<<< orphan*/  moxa_shut_down (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_tty_set (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void moxa_close_port(struct tty_struct *tty)
{
	struct moxa_port *ch = tty->driver_data;
	moxa_shut_down(tty);
	MoxaPortFlushData(ch, 2);
	ch->port.flags &= ~ASYNC_NORMAL_ACTIVE;
	tty->driver_data = NULL;
	tty_port_tty_set(&ch->port, NULL);
}