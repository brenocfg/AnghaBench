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
typedef  int /*<<< orphan*/  u32 ;
struct csr1212_csr_rom_cache {size_t size; int /*<<< orphan*/ * ext_rom; int /*<<< orphan*/  offset; int /*<<< orphan*/ * layout_tail; int /*<<< orphan*/ * layout_head; int /*<<< orphan*/ * filled_tail; int /*<<< orphan*/ * filled_head; int /*<<< orphan*/ * prev; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 struct csr1212_csr_rom_cache* CSR1212_MALLOC (int) ; 

__attribute__((used)) static inline struct csr1212_csr_rom_cache *
csr1212_rom_cache_malloc(u32 offset, size_t size)
{
	struct csr1212_csr_rom_cache *cache;

	cache = CSR1212_MALLOC(sizeof(*cache) + size);
	if (!cache)
		return NULL;

	cache->next = NULL;
	cache->prev = NULL;
	cache->filled_head = NULL;
	cache->filled_tail = NULL;
	cache->layout_head = NULL;
	cache->layout_tail = NULL;
	cache->offset = offset;
	cache->size = size;
	cache->ext_rom = NULL;

	return cache;
}