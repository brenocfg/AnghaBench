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
struct TYPE_2__ {unsigned long eaddr; unsigned long data; } ;

/* Variables and functions */
 int CPLB_NO_ADDR_MATCH ; 
 int CPLB_RELOADED ; 
 int FAULT_USERSUPV ; 
 unsigned long PAGE_SIZE_1MB ; 
 unsigned long PAGE_SIZE_4MB ; 
 int SIZE_1M ; 
 int SIZE_4M ; 
 unsigned long bfin_read_ICPLB_FAULT_ADDR () ; 
 int bfin_read_ICPLB_STATUS () ; 
 int evict_one_icplb (int) ; 
 TYPE_1__* icplb_bounds ; 
 int icplb_nr_bounds ; 
 int /*<<< orphan*/ * nr_icplb_miss ; 
 int /*<<< orphan*/ * nr_icplb_supv_miss ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  write_icplb_data (int,int,unsigned long,unsigned long) ; 

__attribute__((used)) static int icplb_miss(int cpu)
{
	unsigned long addr = bfin_read_ICPLB_FAULT_ADDR();
	int status = bfin_read_ICPLB_STATUS();
	int idx;
	unsigned long i_data, base, addr1, eaddr;

	nr_icplb_miss[cpu]++;
	if (unlikely(status & FAULT_USERSUPV))
		nr_icplb_supv_miss[cpu]++;

	base = 0;
	idx = 0;
	do {
		eaddr = icplb_bounds[idx].eaddr;
		if (addr < eaddr)
			break;
		base = eaddr;
	} while (++idx < icplb_nr_bounds);

	if (unlikely(idx == icplb_nr_bounds))
		return CPLB_NO_ADDR_MATCH;

	i_data = icplb_bounds[idx].data;
	if (unlikely(i_data == 0))
		return CPLB_NO_ADDR_MATCH;

	addr1 = addr & ~(SIZE_4M - 1);
	addr &= ~(SIZE_1M - 1);
	i_data |= PAGE_SIZE_1MB;
	if (addr1 >= base && (addr1 + SIZE_4M) <= eaddr) {
		/*
		 * This works because
		 * (PAGE_SIZE_4MB & PAGE_SIZE_1MB) == PAGE_SIZE_1MB.
		 */
		i_data |= PAGE_SIZE_4MB;
		addr = addr1;
	}

	/* Pick entry to evict */
	idx = evict_one_icplb(cpu);

	write_icplb_data(cpu, idx, i_data, addr);

	return CPLB_RELOADED;
}