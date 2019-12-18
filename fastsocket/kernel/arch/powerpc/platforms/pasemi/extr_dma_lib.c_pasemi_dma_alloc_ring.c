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
typedef  int /*<<< orphan*/  u64 ;
struct pasemi_dmachan {int ring_size; int /*<<< orphan*/  ring_virt; int /*<<< orphan*/  ring_dma; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* dma_pdev ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int pasemi_dma_alloc_ring(struct pasemi_dmachan *chan, int ring_size)
{
	BUG_ON(chan->ring_virt);

	chan->ring_size = ring_size;

	chan->ring_virt = dma_alloc_coherent(&dma_pdev->dev,
					     ring_size * sizeof(u64),
					     &chan->ring_dma, GFP_KERNEL);

	if (!chan->ring_virt)
		return -ENOMEM;

	memset(chan->ring_virt, 0, ring_size * sizeof(u64));

	return 0;
}