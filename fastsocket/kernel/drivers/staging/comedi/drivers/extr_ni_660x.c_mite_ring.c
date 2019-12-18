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
struct ni_gpct {size_t chip_index; size_t counter_index; } ;
struct ni_660x_private {struct mite_dma_descriptor_ring*** mite_rings; } ;
struct mite_dma_descriptor_ring {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct mite_dma_descriptor_ring *mite_ring(struct ni_660x_private
							 *priv,
							 struct ni_gpct
							 *counter)
{
	return priv->mite_rings[counter->chip_index][counter->counter_index];
}