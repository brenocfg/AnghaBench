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
struct TYPE_2__ {int uart_cmd; int /*<<< orphan*/  uart_overrun; int /*<<< orphan*/  uart_framing; } ;
struct snd_gus_card {TYPE_1__ gf1; int /*<<< orphan*/  midi_substream_input; int /*<<< orphan*/  uart_cmd_lock; } ;

/* Variables and functions */
 unsigned char snd_gf1_uart_get (struct snd_gus_card*) ; 
 unsigned char snd_gf1_uart_stat (struct snd_gus_card*) ; 
 int /*<<< orphan*/  snd_rawmidi_receive (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_gf1_interrupt_midi_in(struct snd_gus_card * gus)
{
	int count;
	unsigned char stat, data, byte;
	unsigned long flags;

	count = 10;
	while (count) {
		spin_lock_irqsave(&gus->uart_cmd_lock, flags);
		stat = snd_gf1_uart_stat(gus);
		if (!(stat & 0x01)) {	/* data in Rx FIFO? */
			spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
			count--;
			continue;
		}
		count = 100;	/* arm counter to new value */
		data = snd_gf1_uart_get(gus);
		if (!(gus->gf1.uart_cmd & 0x80)) {
			spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
			continue;
		}			
		if (stat & 0x10) {	/* framing error */
			gus->gf1.uart_framing++;
			spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
			continue;
		}
		byte = snd_gf1_uart_get(gus);
		spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
		snd_rawmidi_receive(gus->midi_substream_input, &byte, 1);
		if (stat & 0x20) {
			gus->gf1.uart_overrun++;
		}
	}
}