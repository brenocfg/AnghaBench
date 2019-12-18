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
struct rsxx_cardinfo {scalar_t__ regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_QUEUE_RESET ; 
 scalar_t__ RESET ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

void rsxx_dma_queue_reset(struct rsxx_cardinfo *card)
{
	/* Reset all DMA Command/Status Queues */
	iowrite32(DMA_QUEUE_RESET, card->regmap + RESET);
}