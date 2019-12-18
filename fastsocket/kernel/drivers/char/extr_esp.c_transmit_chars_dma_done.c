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
struct TYPE_2__ {int tx; } ;
struct esp_struct {int /*<<< orphan*/  stat_flags; TYPE_1__ icount; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MODE_WRITE ; 
 int /*<<< orphan*/  ESI_START_DMA_TX ; 
 int /*<<< orphan*/  ESP_STAT_DMA_TX ; 
 int /*<<< orphan*/  UART_ESI_CMD1 ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma ; 
 scalar_t__ dma_buffer ; 
 int dma_bytes ; 
 int get_dma_residue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_virt_to_bus (scalar_t__) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  program_isa_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  serial_out (struct esp_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void transmit_chars_dma_done(struct esp_struct *info)
{
	int num_bytes;
	unsigned long flags;

	flags = claim_dma_lock();
	disable_dma(dma);
	clear_dma_ff(dma);

	num_bytes = dma_bytes - get_dma_residue(dma);
	info->icount.tx += dma_bytes;
	release_dma_lock(flags);

	if (dma_bytes != num_bytes) {
		dma_bytes -= num_bytes;
		memmove(dma_buffer, dma_buffer + num_bytes, dma_bytes);

		program_isa_dma(dma, DMA_MODE_WRITE,
				isa_virt_to_bus(dma_buffer), dma_bytes);

		serial_out(info, UART_ESI_CMD1, ESI_START_DMA_TX);
	} else {
		dma_bytes = 0;
		info->stat_flags &= ~ESP_STAT_DMA_TX;
	}
}