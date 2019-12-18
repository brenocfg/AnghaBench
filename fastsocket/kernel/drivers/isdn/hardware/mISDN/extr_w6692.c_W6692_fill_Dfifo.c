#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {scalar_t__ expires; } ;
struct dchannel {int tx_idx; TYPE_2__ timer; int /*<<< orphan*/  Flags; TYPE_1__* tx_skb; } ;
struct w6692_hw {char* name; int /*<<< orphan*/  log; scalar_t__ addr; struct dchannel dch; } ;
struct TYPE_5__ {int len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int DBUSY_TIMER_VALUE ; 
 int DEBUG_HW_DFIFO ; 
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  FLG_BUSY_TIMER ; 
 int HZ ; 
 int /*<<< orphan*/  W_D_CMDR ; 
 int /*<<< orphan*/  W_D_CMDR_XME ; 
 int /*<<< orphan*/  W_D_CMDR_XMS ; 
 int W_D_FIFO_THRESH ; 
 scalar_t__ W_D_XFIFO ; 
 int /*<<< orphan*/  WriteW6692 (struct w6692_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int debug ; 
 int /*<<< orphan*/  del_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  outsb (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
W6692_fill_Dfifo(struct w6692_hw *card)
{
	struct dchannel *dch = &card->dch;
	int count;
	u8 *ptr;
	u8 cmd = W_D_CMDR_XMS;

	pr_debug("%s: fill_Dfifo\n", card->name);
	if (!dch->tx_skb)
		return;
	count = dch->tx_skb->len - dch->tx_idx;
	if (count <= 0)
		return;
	if (count > W_D_FIFO_THRESH)
		count = W_D_FIFO_THRESH;
	else
		cmd |= W_D_CMDR_XME;
	ptr = dch->tx_skb->data + dch->tx_idx;
	dch->tx_idx += count;
	outsb(card->addr + W_D_XFIFO, ptr, count);
	WriteW6692(card, W_D_CMDR, cmd);
	if (test_and_set_bit(FLG_BUSY_TIMER, &dch->Flags)) {
		pr_debug("%s: fill_Dfifo dbusytimer running\n", card->name);
		del_timer(&dch->timer);
	}
	init_timer(&dch->timer);
	dch->timer.expires = jiffies + ((DBUSY_TIMER_VALUE * HZ)/1000);
	add_timer(&dch->timer);
	if (debug & DEBUG_HW_DFIFO) {
		snprintf(card->log, 63, "D-send %s %d ",
			card->name, count);
		print_hex_dump_bytes(card->log, DUMP_PREFIX_OFFSET, ptr, count);
	}
}