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
struct csr1212_csr_rom_cache {scalar_t__ ext_rom; struct csr1212_csr_rom_cache* prev; struct csr1212_csr_rom_cache* next; } ;
struct csr1212_csr {int /*<<< orphan*/  root_kv; struct csr1212_csr_rom_cache* cache_tail; struct csr1212_csr_rom_cache* cache_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR1212_FREE (struct csr1212_csr_rom_cache*) ; 
 int /*<<< orphan*/  csr1212_detach_keyval_from_directory (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  csr1212_release_keyval (scalar_t__) ; 

__attribute__((used)) static void csr1212_remove_cache(struct csr1212_csr *csr,
				 struct csr1212_csr_rom_cache *cache)
{
	if (csr->cache_head == cache)
		csr->cache_head = cache->next;
	if (csr->cache_tail == cache)
		csr->cache_tail = cache->prev;

	if (cache->prev)
		cache->prev->next = cache->next;
	if (cache->next)
		cache->next->prev = cache->prev;

	if (cache->ext_rom) {
		csr1212_detach_keyval_from_directory(csr->root_kv,
						     cache->ext_rom);
		csr1212_release_keyval(cache->ext_rom);
	}

	CSR1212_FREE(cache);
}