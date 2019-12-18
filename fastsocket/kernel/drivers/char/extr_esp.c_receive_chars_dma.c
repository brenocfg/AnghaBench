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
struct esp_struct {int /*<<< orphan*/  stat_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MODE_READ ; 
 int /*<<< orphan*/  ESI_START_DMA_RX ; 
 int /*<<< orphan*/  ESP_STAT_DMA_RX ; 
 int /*<<< orphan*/  ESP_STAT_RX_TIMEOUT ; 
 int /*<<< orphan*/  UART_ESI_CMD1 ; 
 int /*<<< orphan*/  dma ; 
 int /*<<< orphan*/  dma_buffer ; 
 int dma_bytes ; 
 int /*<<< orphan*/  isa_virt_to_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  program_isa_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  serial_out (struct esp_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void receive_chars_dma(struct esp_struct *info, int num_bytes)
{
	info->stat_flags &= ~ESP_STAT_RX_TIMEOUT;
	dma_bytes = num_bytes;
	info->stat_flags |= ESP_STAT_DMA_RX;

	program_isa_dma(dma, DMA_MODE_READ, isa_virt_to_bus(dma_buffer),
								dma_bytes);
	serial_out(info, UART_ESI_CMD1, ESI_START_DMA_RX);
}