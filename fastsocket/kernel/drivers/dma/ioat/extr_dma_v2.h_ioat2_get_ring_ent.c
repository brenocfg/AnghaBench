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
typedef  size_t u16 ;
struct ioat_ring_ent {int dummy; } ;
struct ioat2_dma_chan {struct ioat_ring_ent** ring; } ;

/* Variables and functions */
 size_t ioat2_ring_mask (struct ioat2_dma_chan*) ; 

__attribute__((used)) static inline struct ioat_ring_ent *
ioat2_get_ring_ent(struct ioat2_dma_chan *ioat, u16 idx)
{
	return ioat->ring[idx & ioat2_ring_mask(ioat)];
}