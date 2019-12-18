#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct csr1212_dentry {TYPE_6__* kv; struct csr1212_dentry* next; } ;
struct csr1212_csr {int max_rom; TYPE_6__* root_kv; scalar_t__ bus_info_len; TYPE_2__* cache_head; TYPE_1__* ops; } ;
struct TYPE_11__ {scalar_t__ id; } ;
struct TYPE_9__ {struct csr1212_dentry* dentries_head; } ;
struct TYPE_10__ {TYPE_3__ directory; } ;
struct TYPE_12__ {scalar_t__ valid; TYPE_5__ key; TYPE_4__ value; struct TYPE_12__* prev; struct TYPE_12__* next; scalar_t__ offset; } ;
struct TYPE_8__ {TYPE_6__* layout_tail; TYPE_6__* layout_head; } ;
struct TYPE_7__ {int /*<<< orphan*/  bus_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CSR1212_CONFIG_ROM_SPACE_BASE ; 
 scalar_t__ CSR1212_KV_ID_EXTENDED_ROM ; 
 int CSR1212_SUCCESS ; 
 int csr1212_parse_bus_info_block (struct csr1212_csr*) ; 
 int csr1212_read_keyval (struct csr1212_csr*,TYPE_6__*) ; 

int csr1212_parse_csr(struct csr1212_csr *csr)
{
	struct csr1212_dentry *dentry;
	int ret;

	BUG_ON(!csr || !csr->ops || !csr->ops->bus_read);

	ret = csr1212_parse_bus_info_block(csr);
	if (ret != CSR1212_SUCCESS)
		return ret;

	/*
	 * There has been a buggy firmware with bus_info_block.max_rom > 0
	 * spotted which actually only supported quadlet read requests to the
	 * config ROM.  Therefore read everything quadlet by quadlet regardless
	 * of what the bus info block says.
	 */
	csr->max_rom = 4;

	csr->cache_head->layout_head = csr->root_kv;
	csr->cache_head->layout_tail = csr->root_kv;

	csr->root_kv->offset = (CSR1212_CONFIG_ROM_SPACE_BASE & 0xffff) +
		csr->bus_info_len;

	csr->root_kv->valid = 0;
	csr->root_kv->next = csr->root_kv;
	csr->root_kv->prev = csr->root_kv;
	ret = csr1212_read_keyval(csr, csr->root_kv);
	if (ret != CSR1212_SUCCESS)
		return ret;

	/* Scan through the Root directory finding all extended ROM regions
	 * and make cache regions for them */
	for (dentry = csr->root_kv->value.directory.dentries_head;
	     dentry; dentry = dentry->next) {
		if (dentry->kv->key.id == CSR1212_KV_ID_EXTENDED_ROM &&
			!dentry->kv->valid) {
			ret = csr1212_read_keyval(csr, dentry->kv);
			if (ret != CSR1212_SUCCESS)
				return ret;
		}
	}

	return CSR1212_SUCCESS;
}