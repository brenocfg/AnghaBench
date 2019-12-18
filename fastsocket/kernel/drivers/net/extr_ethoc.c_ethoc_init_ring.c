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
struct ethoc_bd {int stat; int /*<<< orphan*/  addr; } ;
struct ethoc {int num_tx; int num_rx; int /*<<< orphan*/  membase; scalar_t__ cur_rx; scalar_t__ dty_tx; scalar_t__ cur_tx; } ;

/* Variables and functions */
 scalar_t__ ETHOC_BUFSIZ ; 
 int RX_BD_EMPTY ; 
 int RX_BD_IRQ ; 
 int RX_BD_WRAP ; 
 int TX_BD_CRC ; 
 int TX_BD_IRQ ; 
 int TX_BD_WRAP ; 
 int /*<<< orphan*/  ethoc_write_bd (struct ethoc*,int,struct ethoc_bd*) ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ethoc_init_ring(struct ethoc *dev)
{
	struct ethoc_bd bd;
	int i;

	dev->cur_tx = 0;
	dev->dty_tx = 0;
	dev->cur_rx = 0;

	/* setup transmission buffers */
	bd.addr = virt_to_phys(dev->membase);
	bd.stat = TX_BD_IRQ | TX_BD_CRC;

	for (i = 0; i < dev->num_tx; i++) {
		if (i == dev->num_tx - 1)
			bd.stat |= TX_BD_WRAP;

		ethoc_write_bd(dev, i, &bd);
		bd.addr += ETHOC_BUFSIZ;
	}

	bd.stat = RX_BD_EMPTY | RX_BD_IRQ;

	for (i = 0; i < dev->num_rx; i++) {
		if (i == dev->num_rx - 1)
			bd.stat |= RX_BD_WRAP;

		ethoc_write_bd(dev, dev->num_tx + i, &bd);
		bd.addr += ETHOC_BUFSIZ;
	}

	return 0;
}