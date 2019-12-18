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
struct mem_chunk {unsigned long addr; unsigned long size; int type; } ;

/* Variables and functions */
 unsigned long long ADDR2G ; 
 int CHUNK_READ_ONLY ; 
 int CHUNK_READ_WRITE ; 
 int MEMORY_CHUNKS ; 
 unsigned long long min (unsigned long long,unsigned long long) ; 
 unsigned long long sclp_get_rnmax () ; 
 unsigned long long sclp_get_rzm () ; 
 int tprot (unsigned long) ; 

__attribute__((used)) static void find_memory_chunks(struct mem_chunk chunk[])
{
	unsigned long long memsize, rnmax, rzm;
	unsigned long addr = 0, size;
	int i = 0, type;

	rzm = sclp_get_rzm();
	rnmax = sclp_get_rnmax();
	memsize = rzm * rnmax;
	if (!rzm)
		rzm = 1ULL << 17;
	if (sizeof(long) == 4) {
		rzm = min(ADDR2G, rzm);
		memsize = memsize ? min(ADDR2G, memsize) : ADDR2G;
	}
	do {
		size = 0;
		type = tprot(addr);
		do {
			size += rzm;
			if (memsize && addr + size >= memsize)
				break;
		} while (type == tprot(addr + size));
		if (type == CHUNK_READ_WRITE || type == CHUNK_READ_ONLY) {
			chunk[i].addr = addr;
			chunk[i].size = size;
			chunk[i].type = type;
			i++;
		}
		addr += size;
	} while (addr < memsize && i < MEMORY_CHUNKS);
}