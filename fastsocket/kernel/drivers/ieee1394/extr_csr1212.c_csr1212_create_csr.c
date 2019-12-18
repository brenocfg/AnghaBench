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
struct csr1212_csr {size_t bus_info_len; size_t crc_len; struct csr1212_csr* cache_head; struct csr1212_csr* cache_tail; void* private; struct csr1212_bus_ops* ops; int /*<<< orphan*/  data; int /*<<< orphan*/  bus_info_data; int /*<<< orphan*/  root_kv; } ;
struct csr1212_bus_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR1212_CONFIG_ROM_SPACE_OFFSET ; 
 int /*<<< orphan*/  CSR1212_CONFIG_ROM_SPACE_SIZE ; 
 int /*<<< orphan*/  CSR1212_FREE (struct csr1212_csr*) ; 
 int /*<<< orphan*/  CSR1212_KV_ID_VENDOR ; 
 struct csr1212_csr* CSR1212_MALLOC (int) ; 
 int /*<<< orphan*/  csr1212_new_directory (int /*<<< orphan*/ ) ; 
 struct csr1212_csr* csr1212_rom_cache_malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct csr1212_csr *csr1212_create_csr(struct csr1212_bus_ops *ops,
				       size_t bus_info_size, void *private)
{
	struct csr1212_csr *csr;

	csr = CSR1212_MALLOC(sizeof(*csr));
	if (!csr)
		return NULL;

	csr->cache_head =
		csr1212_rom_cache_malloc(CSR1212_CONFIG_ROM_SPACE_OFFSET,
					 CSR1212_CONFIG_ROM_SPACE_SIZE);
	if (!csr->cache_head) {
		CSR1212_FREE(csr);
		return NULL;
	}

	/* The keyval key id is not used for the root node, but a valid key id
	 * that can be used for a directory needs to be passed to
	 * csr1212_new_directory(). */
	csr->root_kv = csr1212_new_directory(CSR1212_KV_ID_VENDOR);
	if (!csr->root_kv) {
		CSR1212_FREE(csr->cache_head);
		CSR1212_FREE(csr);
		return NULL;
	}

	csr->bus_info_data = csr->cache_head->data;
	csr->bus_info_len = bus_info_size;
	csr->crc_len = bus_info_size;
	csr->ops = ops;
	csr->private = private;
	csr->cache_tail = csr->cache_head;

	return csr;
}