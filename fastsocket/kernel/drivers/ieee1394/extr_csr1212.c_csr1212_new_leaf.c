#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {TYPE_1__ leaf; } ;
struct csr1212_keyval {int valid; scalar_t__ offset; TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR1212_FREE (struct csr1212_keyval*) ; 
 int /*<<< orphan*/  CSR1212_KV_TYPE_LEAF ; 
 int /*<<< orphan*/ * CSR1212_MALLOC (size_t) ; 
 int /*<<< orphan*/  bytes_to_quads (size_t) ; 
 struct csr1212_keyval* csr1212_new_keyval (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 

__attribute__((used)) static struct csr1212_keyval *
csr1212_new_leaf(u8 key, const void *data, size_t data_len)
{
	struct csr1212_keyval *kv;

	kv = csr1212_new_keyval(CSR1212_KV_TYPE_LEAF, key);
	if (!kv)
		return NULL;

	if (data_len > 0) {
		kv->value.leaf.data = CSR1212_MALLOC(data_len);
		if (!kv->value.leaf.data) {
			CSR1212_FREE(kv);
			return NULL;
		}

		if (data)
			memcpy(kv->value.leaf.data, data, data_len);
	} else {
		kv->value.leaf.data = NULL;
	}

	kv->value.leaf.len = bytes_to_quads(data_len);
	kv->offset = 0;
	kv->valid = 1;

	return kv;
}