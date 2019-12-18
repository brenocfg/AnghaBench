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
struct dma_descr_data {scalar_t__ next; scalar_t__ eol; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_dma_descr (struct dma_descr_data*,int) ; 
 struct dma_descr_data* phys_to_virt (unsigned int) ; 

void flush_dma_list(struct dma_descr_data *descr)
{
	while (1) {
		flush_dma_descr(descr, 1);
		if (descr->eol)
			break;
		descr = phys_to_virt((unsigned)descr->next);
	}
}