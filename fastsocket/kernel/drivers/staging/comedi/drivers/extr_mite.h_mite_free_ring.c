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
struct mite_dma_descriptor_ring {int n_links; int /*<<< orphan*/  hw_dev; int /*<<< orphan*/  descriptors_dma_addr; scalar_t__ descriptors; } ;
struct mite_dma_descriptor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mite_dma_descriptor_ring*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mite_free_ring(struct mite_dma_descriptor_ring *ring)
{
	if (ring) {
		if (ring->descriptors) {
			dma_free_coherent(ring->hw_dev,
					  ring->n_links *
					  sizeof(struct mite_dma_descriptor),
					  ring->descriptors,
					  ring->descriptors_dma_addr);
		}
		put_device(ring->hw_dev);
		kfree(ring);
	}
}