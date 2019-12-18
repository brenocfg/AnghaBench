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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct fst_port_info {int index; scalar_t__ rxpos; struct fst_card_info* card; } ;
struct fst_card_info {int /*<<< orphan*/  card_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  mcnt; int /*<<< orphan*/  bcnt; int /*<<< orphan*/  hadr; int /*<<< orphan*/  ladr; } ;

/* Variables and functions */
 unsigned int BUF_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_OWN ; 
 int /*<<< orphan*/  FST_WRB (struct fst_card_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FST_WRW (struct fst_card_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEN_RX_BUFFER ; 
 int NUM_RX_BUFFER ; 
 int /*<<< orphan*/  cnv_bcnt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ *** rxBuffer ; 
 TYPE_1__** rxDescrRing ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
fst_rx_config(struct fst_port_info *port)
{
	int i;
	int pi;
	unsigned int offset;
	unsigned long flags;
	struct fst_card_info *card;

	pi = port->index;
	card = port->card;
	spin_lock_irqsave(&card->card_lock, flags);
	for (i = 0; i < NUM_RX_BUFFER; i++) {
		offset = BUF_OFFSET(rxBuffer[pi][i][0]);

		FST_WRW(card, rxDescrRing[pi][i].ladr, (u16) offset);
		FST_WRB(card, rxDescrRing[pi][i].hadr, (u8) (offset >> 16));
		FST_WRW(card, rxDescrRing[pi][i].bcnt, cnv_bcnt(LEN_RX_BUFFER));
		FST_WRW(card, rxDescrRing[pi][i].mcnt, LEN_RX_BUFFER);
		FST_WRB(card, rxDescrRing[pi][i].bits, DMA_OWN);
	}
	port->rxpos = 0;
	spin_unlock_irqrestore(&card->card_lock, flags);
}