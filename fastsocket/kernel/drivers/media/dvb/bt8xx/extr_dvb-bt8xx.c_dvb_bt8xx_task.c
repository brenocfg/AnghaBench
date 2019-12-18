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
struct dvb_bt8xx_card {TYPE_1__* bt; int /*<<< orphan*/  demux; } ;
struct TYPE_2__ {size_t last_block; size_t finished_block; size_t block_bytes; int block_count; int /*<<< orphan*/ * buf_cpu; scalar_t__ TS_Size; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_dmx_swfilter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  dvb_dmx_swfilter_204 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void dvb_bt8xx_task(unsigned long data)
{
	struct dvb_bt8xx_card *card = (struct dvb_bt8xx_card *)data;

	//printk("%d ", card->bt->finished_block);

	while (card->bt->last_block != card->bt->finished_block) {
		(card->bt->TS_Size ? dvb_dmx_swfilter_204 : dvb_dmx_swfilter)
			(&card->demux,
			 &card->bt->buf_cpu[card->bt->last_block *
					    card->bt->block_bytes],
			 card->bt->block_bytes);
		card->bt->last_block = (card->bt->last_block + 1) %
					card->bt->block_count;
	}
}