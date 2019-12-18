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
struct TYPE_2__ {scalar_t__ tty; } ;
struct esp_struct {int xmit_tail; scalar_t__ xmit_cnt; int /*<<< orphan*/  stat_flags; int /*<<< orphan*/  IER; TYPE_1__ port; int /*<<< orphan*/ * xmit_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MODE_WRITE ; 
 int /*<<< orphan*/  ESI_SET_SRV_MASK ; 
 int /*<<< orphan*/  ESI_START_DMA_TX ; 
 int /*<<< orphan*/  ESP_STAT_DMA_TX ; 
 int ESP_XMIT_SIZE ; 
 int /*<<< orphan*/  UART_ESI_CMD1 ; 
 int /*<<< orphan*/  UART_ESI_CMD2 ; 
 int /*<<< orphan*/  UART_IER_THRI ; 
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  dma ; 
 int /*<<< orphan*/ * dma_buffer ; 
 int dma_bytes ; 
 int /*<<< orphan*/  isa_virt_to_bus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  program_isa_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  serial_out (struct esp_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_wakeup (scalar_t__) ; 

__attribute__((used)) static inline void transmit_chars_dma(struct esp_struct *info, int num_bytes)
{
	dma_bytes = num_bytes;

	if (info->xmit_tail + dma_bytes <= ESP_XMIT_SIZE) {
		memcpy(dma_buffer, &(info->xmit_buf[info->xmit_tail]),
		       dma_bytes);
	} else {
		int i = ESP_XMIT_SIZE - info->xmit_tail;
		memcpy(dma_buffer, &(info->xmit_buf[info->xmit_tail]),
			i);
		memcpy(&(dma_buffer[i]), info->xmit_buf, dma_bytes - i);
	}

	info->xmit_cnt -= dma_bytes;
	info->xmit_tail = (info->xmit_tail + dma_bytes) & (ESP_XMIT_SIZE - 1);

	if (info->xmit_cnt < WAKEUP_CHARS) {
		if (info->port.tty)
			tty_wakeup(info->port.tty);

#ifdef SERIAL_DEBUG_INTR
		printk("THRE...");
#endif

		if (info->xmit_cnt <= 0) {
			info->IER &= ~UART_IER_THRI;
			serial_out(info, UART_ESI_CMD1, ESI_SET_SRV_MASK);
			serial_out(info, UART_ESI_CMD2, info->IER);
		}
	}

	info->stat_flags |= ESP_STAT_DMA_TX;

	program_isa_dma(dma, DMA_MODE_WRITE, isa_virt_to_bus(dma_buffer),
								dma_bytes);
	serial_out(info, UART_ESI_CMD1, ESI_START_DMA_TX);
}