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
struct tty_struct {struct moxa_port* driver_data; scalar_t__ stopped; } ;
struct moxa_port {int dummy; } ;

/* Variables and functions */
 int MoxaPortTxFree (struct moxa_port*) ; 

__attribute__((used)) static int moxa_write_room(struct tty_struct *tty)
{
	struct moxa_port *ch;

	if (tty->stopped)
		return 0;
	ch = tty->driver_data;
	if (ch == NULL)
		return 0;
	return MoxaPortTxFree(ch);
}