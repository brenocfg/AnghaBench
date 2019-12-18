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
struct tty_struct {struct moxa_port* driver_data; } ;
struct moxa_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MoxaPortFlushData (struct moxa_port*,int) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 

__attribute__((used)) static void moxa_flush_buffer(struct tty_struct *tty)
{
	struct moxa_port *ch = tty->driver_data;

	if (ch == NULL)
		return;
	MoxaPortFlushData(ch, 1);
	tty_wakeup(tty);
}