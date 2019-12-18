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
 scalar_t__ NSP32_MMIO_OFFSET ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned short) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,unsigned short volatile*) ; 

__attribute__((used)) static inline void nsp32_mmio_write2(unsigned long  base,
				     unsigned int   index,
				     unsigned short val)
{
	volatile unsigned short *ptr;

	ptr = (unsigned short *)(base + NSP32_MMIO_OFFSET + index);

	writew(cpu_to_le16(val), ptr);
}