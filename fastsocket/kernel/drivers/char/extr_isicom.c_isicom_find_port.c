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
struct tty_struct {int index; int /*<<< orphan*/  name; } ;
struct tty_port {int dummy; } ;
struct isi_port {struct tty_port port; } ;
struct isi_board {int status; unsigned int port_count; } ;

/* Variables and functions */
 unsigned int BOARD (int) ; 
 int FIRMWARE_LOADED ; 
 int PORT_COUNT ; 
 struct isi_board* isi_card ; 
 struct isi_port* isi_ports ; 
 scalar_t__ isicom_paranoia_check (struct isi_port*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct tty_port *isicom_find_port(struct tty_struct *tty)
{
	struct isi_port *port;
	struct isi_board *card;
	unsigned int board;
	int line = tty->index;

	if (line < 0 || line > PORT_COUNT-1)
		return NULL;
	board = BOARD(line);
	card = &isi_card[board];

	if (!(card->status & FIRMWARE_LOADED))
		return NULL;

	/*  open on a port greater than the port count for the card !!! */
	if (line > ((board * 16) + card->port_count - 1))
		return NULL;

	port = &isi_ports[line];
	if (isicom_paranoia_check(port, tty->name, "isicom_open"))
		return NULL;

	return &port->port;
}