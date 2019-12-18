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
typedef  int vm_size_t ;
typedef  int uint64_t ;
struct TYPE_2__ {int addr; int len; } ;
typedef  TYPE_1__ pmap_io_range_t ;
typedef  int /*<<< orphan*/  DTEntry ;

/* Variables and functions */
 int DTGetProperty (int /*<<< orphan*/ ,char*,void**,unsigned int*) ; 
 int DTLookupEntry (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  assert (int) ; 
 int avail_end ; 
 int gPhysBase ; 
 int io_rgn_end ; 
 int io_rgn_start ; 
 int kSuccess ; 
 int num_io_rgns ; 
 scalar_t__ os_add_overflow (int,int,int*) ; 
 int /*<<< orphan*/  panic (char*,...) ; 

__attribute__((used)) static vm_size_t
pmap_compute_io_rgns(void)
{
	DTEntry entry;
	pmap_io_range_t *ranges;
	uint64_t rgn_end;
	void *prop = NULL;
        int err;
	unsigned int prop_size;

        err = DTLookupEntry(NULL, "/defaults", &entry);
        assert(err == kSuccess);

	if (kSuccess != DTGetProperty(entry, "pmap-io-ranges", &prop, &prop_size))
		return 0;

	ranges = prop;
	for (unsigned int i = 0; i < (prop_size / sizeof(*ranges)); ++i) {
		if (ranges[i].addr & PAGE_MASK)
			panic("pmap I/O region %u addr 0x%llx is not page-aligned", i, ranges[i].addr);
		if (ranges[i].len & PAGE_MASK)
			panic("pmap I/O region %u length 0x%x is not page-aligned", i, ranges[i].len);
		if (os_add_overflow(ranges[i].addr, ranges[i].len, &rgn_end))
			panic("pmap I/O region %u addr 0x%llx length 0x%x wraps around", i, ranges[i].addr, ranges[i].len);
		if ((i == 0) || (ranges[i].addr < io_rgn_start))
			io_rgn_start = ranges[i].addr;
		if ((i == 0) || (rgn_end > io_rgn_end))
			io_rgn_end = rgn_end;
		++num_io_rgns;
	}

	if (io_rgn_start & PAGE_MASK)
		panic("pmap I/O region start is not page-aligned!\n");

	if (io_rgn_end & PAGE_MASK)
		panic("pmap I/O region end is not page-aligned!\n");

	if (((io_rgn_start <= gPhysBase) && (io_rgn_end > gPhysBase)) ||
	    ((io_rgn_start < avail_end) && (io_rgn_end >= avail_end)) ||
	    ((io_rgn_start > gPhysBase) && (io_rgn_end < avail_end)))
		panic("pmap I/O region overlaps physical memory!\n");

	return (num_io_rgns * sizeof(*ranges));
}