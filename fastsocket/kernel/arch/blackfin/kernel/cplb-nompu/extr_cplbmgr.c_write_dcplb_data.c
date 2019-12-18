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
struct TYPE_2__ {unsigned long addr; unsigned long data; } ;

/* Variables and functions */
 scalar_t__ DCPLB_ADDR0 ; 
 scalar_t__ DCPLB_DATA0 ; 
 int /*<<< orphan*/  _disable_dcplb () ; 
 int /*<<< orphan*/  _enable_dcplb () ; 
 int /*<<< orphan*/  bfin_write32 (scalar_t__,unsigned long) ; 
 TYPE_1__** dcplb_tbl ; 

__attribute__((used)) static inline void write_dcplb_data(int cpu, int idx, unsigned long data,
				    unsigned long addr)
{
	_disable_dcplb();
	bfin_write32(DCPLB_DATA0 + idx * 4, data);
	bfin_write32(DCPLB_ADDR0 + idx * 4, addr);
	_enable_dcplb();

#ifdef CONFIG_CPLB_INFO
	dcplb_tbl[cpu][idx].addr = addr;
	dcplb_tbl[cpu][idx].data = data;
#endif
}