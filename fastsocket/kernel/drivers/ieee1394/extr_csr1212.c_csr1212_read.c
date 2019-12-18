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
typedef  scalar_t__ u32 ;
struct csr1212_csr_rom_cache {scalar_t__ offset; scalar_t__ size; int /*<<< orphan*/ * data; struct csr1212_csr_rom_cache* next; } ;
struct csr1212_csr {struct csr1212_csr_rom_cache* cache_head; } ;

/* Variables and functions */
 int CSR1212_SUCCESS ; 
 int ENOENT ; 
 size_t bytes_to_quads (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,scalar_t__) ; 

int csr1212_read(struct csr1212_csr *csr, u32 offset, void *buffer, u32 len)
{
	struct csr1212_csr_rom_cache *cache;

	for (cache = csr->cache_head; cache; cache = cache->next)
		if (offset >= cache->offset &&
		    (offset + len) <= (cache->offset + cache->size)) {
			memcpy(buffer, &cache->data[
					bytes_to_quads(offset - cache->offset)],
			       len);
			return CSR1212_SUCCESS;
		}

	return -ENOENT;
}