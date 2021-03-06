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
struct sport_device {int dummy_count; TYPE_1__* dummy_rx_desc; TYPE_1__* curr_rx_desc; int /*<<< orphan*/  dma_rx_chan; } ;
struct dmasg {int x_count; TYPE_1__* next_desc_addr; scalar_t__ y_count; } ;
struct TYPE_2__ {struct TYPE_2__* next_desc_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_1__* get_dma_curr_desc_ptr (int /*<<< orphan*/ ) ; 
 struct dmasg* get_dma_next_desc_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static inline int sport_hook_rx_dummy(struct sport_device *sport)
{
	struct dmasg *desc, temp_desc;
	unsigned long flags;

	BUG_ON(sport->dummy_rx_desc == NULL);
	BUG_ON(sport->curr_rx_desc == sport->dummy_rx_desc);

	/* Maybe the dummy buffer descriptor ring is damaged */
	sport->dummy_rx_desc->next_desc_addr = sport->dummy_rx_desc + 1;

	local_irq_save(flags);
	desc = get_dma_next_desc_ptr(sport->dma_rx_chan);
	/* Copy the descriptor which will be damaged to backup */
	temp_desc = *desc;
	desc->x_count = sport->dummy_count / 2;
	desc->y_count = 0;
	desc->next_desc_addr = sport->dummy_rx_desc;
	local_irq_restore(flags);
	/* Waiting for dummy buffer descriptor is already hooked*/
	while ((get_dma_curr_desc_ptr(sport->dma_rx_chan) -
			sizeof(struct dmasg)) != sport->dummy_rx_desc)
		continue;
	sport->curr_rx_desc = sport->dummy_rx_desc;
	/* Restore the damaged descriptor */
	*desc = temp_desc;

	return 0;
}