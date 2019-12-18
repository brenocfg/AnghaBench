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
struct mite_struct {TYPE_1__* pcidev; } ;
struct mite_dma_descriptor_ring {scalar_t__ descriptors_dma_addr; int /*<<< orphan*/ * descriptors; scalar_t__ n_links; int /*<<< orphan*/ * hw_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mite_dma_descriptor_ring*) ; 
 struct mite_dma_descriptor_ring* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct mite_dma_descriptor_ring *mite_alloc_ring(struct
							       mite_struct
							       *mite)
{
	struct mite_dma_descriptor_ring *ring =
	    kmalloc(sizeof(struct mite_dma_descriptor_ring), GFP_KERNEL);
	if (ring == NULL)
		return ring;
	ring->hw_dev = get_device(&mite->pcidev->dev);
	if (ring->hw_dev == NULL) {
		kfree(ring);
		return NULL;
	}
	ring->n_links = 0;
	ring->descriptors = NULL;
	ring->descriptors_dma_addr = 0;
	return ring;
}