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
 scalar_t__ ICPLB_ADDR0 ; 
 scalar_t__ ICPLB_DATA0 ; 
 int /*<<< orphan*/  _disable_icplb () ; 
 int /*<<< orphan*/  _enable_icplb () ; 
 int /*<<< orphan*/  bfin_write32 (scalar_t__,unsigned long) ; 
 TYPE_1__** icplb_tbl ; 

__attribute__((used)) static inline void write_icplb_data(int cpu, int idx, unsigned long data,
				    unsigned long addr)
{
	_disable_icplb();
	bfin_write32(ICPLB_DATA0 + idx * 4, data);
	bfin_write32(ICPLB_ADDR0 + idx * 4, addr);
	_enable_icplb();

#ifdef CONFIG_CPLB_INFO
	icplb_tbl[cpu][idx].addr = addr;
	icplb_tbl[cpu][idx].data = data;
#endif
}