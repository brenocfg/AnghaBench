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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct omap_ep {TYPE_1__ ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dma_error(int lch, u16 ch_status, void *data)
{
	struct omap_ep	*ep = data;

	/* if ch_status & OMAP_DMA_DROP_IRQ ... */
	/* if ch_status & OMAP1_DMA_TOUT_IRQ ... */
	ERR("%s dma error, lch %d status %02x\n", ep->ep.name, lch, ch_status);

	/* complete current transfer ... */
}