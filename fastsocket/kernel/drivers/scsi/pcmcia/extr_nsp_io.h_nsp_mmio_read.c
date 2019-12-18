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
 scalar_t__ NSP_MMIO_OFFSET ; 
 unsigned char readb (unsigned char*) ; 

__attribute__((used)) static inline unsigned char nsp_mmio_read(unsigned long base,
					  unsigned int  index)
{
	unsigned char *ptr = (unsigned char *)(base + NSP_MMIO_OFFSET + index);

	return readb(ptr);
}