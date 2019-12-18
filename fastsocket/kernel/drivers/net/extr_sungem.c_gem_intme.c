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

/* Variables and functions */
 int TX_RING_SIZE ; 

__attribute__((used)) static __inline__ int gem_intme(int entry)
{
	/* Algorithm: IRQ every 1/2 of descriptors. */
	if (!(entry & ((TX_RING_SIZE>>1)-1)))
		return 1;

	return 0;
}