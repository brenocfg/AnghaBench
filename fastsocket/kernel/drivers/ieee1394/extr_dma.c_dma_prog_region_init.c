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
struct dma_prog_region {scalar_t__ bus_addr; scalar_t__ n_pages; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * kvirt; } ;

/* Variables and functions */

void dma_prog_region_init(struct dma_prog_region *prog)
{
	prog->kvirt = NULL;
	prog->dev = NULL;
	prog->n_pages = 0;
	prog->bus_addr = 0;
}