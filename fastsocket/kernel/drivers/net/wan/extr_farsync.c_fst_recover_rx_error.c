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
struct fst_port_info {int index; int rxpos; } ;
struct fst_card_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ASS ; 
 unsigned char DMA_OWN ; 
 unsigned char FST_RDB (struct fst_card_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FST_WRB (struct fst_card_info*,int /*<<< orphan*/ ,unsigned char) ; 
 int NUM_RX_BUFFER ; 
 unsigned char RX_STP ; 
 int /*<<< orphan*/  dbg (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__** rxDescrRing ; 

__attribute__((used)) static void
fst_recover_rx_error(struct fst_card_info *card, struct fst_port_info *port,
		     unsigned char dmabits, int rxp, unsigned short len)
{
	int i;
	int pi;

	pi = port->index;
	/* 
	 * Discard buffer descriptors until we see the start of the
	 * next frame.  Note that for long frames this could be in
	 * a subsequent interrupt. 
	 */
	i = 0;
	while ((dmabits & (DMA_OWN | RX_STP)) == 0) {
		FST_WRB(card, rxDescrRing[pi][rxp].bits, DMA_OWN);
		rxp = (rxp+1) % NUM_RX_BUFFER;
		if (++i > NUM_RX_BUFFER) {
			dbg(DBG_ASS, "intr_rx: Discarding more bufs"
			    " than we have\n");
			break;
		}
		dmabits = FST_RDB(card, rxDescrRing[pi][rxp].bits);
		dbg(DBG_ASS, "DMA Bits of next buffer was %x\n", dmabits);
	}
	dbg(DBG_ASS, "There were %d subsequent buffers in error\n", i);

	/* Discard the terminal buffer */
	if (!(dmabits & DMA_OWN)) {
		FST_WRB(card, rxDescrRing[pi][rxp].bits, DMA_OWN);
		rxp = (rxp+1) % NUM_RX_BUFFER;
	}
	port->rxpos = rxp;
	return;

}