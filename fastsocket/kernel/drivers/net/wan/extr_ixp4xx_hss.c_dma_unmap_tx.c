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
struct port {TYPE_1__* netdev; } ;
struct desc {int data; scalar_t__ buf_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dma_unmap_tx(struct port *port, struct desc *desc)
{
#ifdef __ARMEB__
	dma_unmap_single(&port->netdev->dev, desc->data,
			 desc->buf_len, DMA_TO_DEVICE);
#else
	dma_unmap_single(&port->netdev->dev, desc->data & ~3,
			 ALIGN((desc->data & 3) + desc->buf_len, 4),
			 DMA_TO_DEVICE);
#endif
}