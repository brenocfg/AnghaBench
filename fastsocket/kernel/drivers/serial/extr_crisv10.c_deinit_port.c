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
struct e100_serial {int /*<<< orphan*/  dma_in_irq_nbr; int /*<<< orphan*/  dma_in_irq_description; int /*<<< orphan*/  dma_in_nbr; scalar_t__ dma_in_enabled; int /*<<< orphan*/  dma_out_irq_nbr; int /*<<< orphan*/  dma_out_irq_description; int /*<<< orphan*/  dma_out_nbr; scalar_t__ dma_out_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  cris_free_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct e100_serial*) ; 

__attribute__((used)) static void
deinit_port(struct e100_serial *info)
{
	if (info->dma_out_enabled) {
		cris_free_dma(info->dma_out_nbr, info->dma_out_irq_description);
		free_irq(info->dma_out_irq_nbr, info);
	}
	if (info->dma_in_enabled) {
		cris_free_dma(info->dma_in_nbr, info->dma_in_irq_description);
		free_irq(info->dma_in_irq_nbr, info);
	}
}