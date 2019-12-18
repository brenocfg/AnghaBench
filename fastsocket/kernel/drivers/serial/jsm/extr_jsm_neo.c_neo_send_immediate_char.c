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
struct jsm_channel {int /*<<< orphan*/  ch_bd; TYPE_1__* ch_neo_uart; } ;
struct TYPE_2__ {int /*<<< orphan*/  txrx; } ;

/* Variables and functions */
 int /*<<< orphan*/  neo_pci_posting_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (unsigned char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void neo_send_immediate_char(struct jsm_channel *ch, unsigned char c)
{
	if (!ch)
		return;

	writeb(c, &ch->ch_neo_uart->txrx);

	/* flush write operation */
	neo_pci_posting_flush(ch->ch_bd);
}