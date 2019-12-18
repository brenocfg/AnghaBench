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
struct csr1212_keyval {struct csr1212_keyval* next; struct csr1212_keyval* prev; scalar_t__ offset; int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR1212_KV_KEY_ID (scalar_t__) ; 
 int CSR1212_KV_KEY_TYPE (scalar_t__) ; 
#define  CSR1212_KV_TYPE_CSR_OFFSET 129 
 int CSR1212_KV_TYPE_DIRECTORY ; 
#define  CSR1212_KV_TYPE_IMMEDIATE 128 
 int /*<<< orphan*/  CSR1212_KV_VAL (scalar_t__) ; 
 int CSR1212_SUCCESS ; 
 int EIO ; 
 int ENOMEM ; 
 int __csr1212_attach_keyval_to_directory (struct csr1212_keyval*,struct csr1212_keyval*,int) ; 
 struct csr1212_keyval* csr1212_find_keyval_offset (struct csr1212_keyval*,scalar_t__) ; 
 struct csr1212_keyval* csr1212_new_csr_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct csr1212_keyval* csr1212_new_directory (int /*<<< orphan*/ ) ; 
 struct csr1212_keyval* csr1212_new_immediate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct csr1212_keyval* csr1212_new_leaf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_keyval (struct csr1212_keyval*) ; 
 scalar_t__ quads_to_bytes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
csr1212_parse_dir_entry(struct csr1212_keyval *dir, u32 ki, u32 kv_pos)
{
	int ret = CSR1212_SUCCESS;
	struct csr1212_keyval *k = NULL;
	u32 offset;
	bool keep_keyval = true;

	switch (CSR1212_KV_KEY_TYPE(ki)) {
	case CSR1212_KV_TYPE_IMMEDIATE:
		k = csr1212_new_immediate(CSR1212_KV_KEY_ID(ki),
					  CSR1212_KV_VAL(ki));
		if (!k) {
			ret = -ENOMEM;
			goto out;
		}
		/* Don't keep local reference when parsing. */
		keep_keyval = false;
		break;

	case CSR1212_KV_TYPE_CSR_OFFSET:
		k = csr1212_new_csr_offset(CSR1212_KV_KEY_ID(ki),
					   CSR1212_KV_VAL(ki));
		if (!k) {
			ret = -ENOMEM;
			goto out;
		}
		/* Don't keep local reference when parsing. */
		keep_keyval = false;
		break;

	default:
		/* Compute the offset from 0xffff f000 0000. */
		offset = quads_to_bytes(CSR1212_KV_VAL(ki)) + kv_pos;
		if (offset == kv_pos) {
			/* Uh-oh.  Can't have a relative offset of 0 for Leaves
			 * or Directories.  The Config ROM image is most likely
			 * messed up, so we'll just abort here. */
			ret = -EIO;
			goto out;
		}

		k = csr1212_find_keyval_offset(dir, offset);

		if (k)
			break;		/* Found it. */

		if (CSR1212_KV_KEY_TYPE(ki) == CSR1212_KV_TYPE_DIRECTORY)
			k = csr1212_new_directory(CSR1212_KV_KEY_ID(ki));
		else
			k = csr1212_new_leaf(CSR1212_KV_KEY_ID(ki), NULL, 0);

		if (!k) {
			ret = -ENOMEM;
			goto out;
		}
		/* Don't keep local reference when parsing. */
		keep_keyval = false;
		/* Contents not read yet so it's not valid. */
		k->valid = 0;
		k->offset = offset;

		k->prev = dir;
		k->next = dir->next;
		dir->next->prev = k;
		dir->next = k;
	}
	ret = __csr1212_attach_keyval_to_directory(dir, k, keep_keyval);
out:
	if (ret != CSR1212_SUCCESS && k != NULL)
		free_keyval(k);
	return ret;
}