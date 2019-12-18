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
 int /*<<< orphan*/  writel (unsigned long,unsigned long*) ; 

__attribute__((used)) static inline void nsp_mmio_multi_write_4(unsigned long  base,
					  unsigned int   Register,
					  void          *buf,
					  unsigned long  count)
{
	unsigned long *ptr = (unsigned long *)(base + Register);
	unsigned long *tmp = (unsigned long *)buf;
	int i;

	//nsp_dbg(NSP_DEBUG_DATA_IO, "base 0x%0lx ptr 0x%p",base,ptr);

	for (i = 0; i < count; i++) {
		writel(*tmp, ptr);
		//nsp_dbg(NSP_DEBUG_DATA_IO, "<%d,%p,%p,%lx>", i, ptr, tmp, *tmp);
		tmp++;
	}
}