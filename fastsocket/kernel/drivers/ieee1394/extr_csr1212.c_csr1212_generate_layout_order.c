#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  len; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; } ;
struct TYPE_8__ {TYPE_3__ directory; TYPE_2__ leaf; } ;
struct TYPE_5__ {int type; } ;
struct csr1212_keyval {struct csr1212_keyval* next; TYPE_4__ value; TYPE_1__ key; } ;

/* Variables and functions */
#define  CSR1212_KV_TYPE_DIRECTORY 129 
#define  CSR1212_KV_TYPE_LEAF 128 
 int /*<<< orphan*/  csr1212_generate_layout_subdir (struct csr1212_keyval*,struct csr1212_keyval**) ; 
 size_t quads_to_bytes (size_t) ; 

__attribute__((used)) static size_t csr1212_generate_layout_order(struct csr1212_keyval *kv)
{
	struct csr1212_keyval *ltail = kv;
	size_t agg_size = 0;

	while (kv) {
		switch (kv->key.type) {
		case CSR1212_KV_TYPE_LEAF:
			/* Add 1 quadlet for crc/len field */
			agg_size += kv->value.leaf.len + 1;
			break;

		case CSR1212_KV_TYPE_DIRECTORY:
			kv->value.directory.len =
				csr1212_generate_layout_subdir(kv, &ltail);
			/* Add 1 quadlet for crc/len field */
			agg_size += kv->value.directory.len + 1;
			break;
		}
		kv = kv->next;
	}
	return quads_to_bytes(agg_size);
}