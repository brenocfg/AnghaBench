#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int id; int type; } ;
struct TYPE_4__ {struct csr1212_dentry* dentries_head; } ;
struct TYPE_5__ {scalar_t__ immediate; int csr_offset; TYPE_1__ directory; } ;
struct csr1212_keyval {int offset; TYPE_3__ key; TYPE_2__ value; struct csr1212_keyval* associate; } ;
struct csr1212_dentry {struct csr1212_keyval* kv; struct csr1212_dentry* next; } ;

/* Variables and functions */
 int CSR1212_KV_ID_EXTENDED_KEY ; 
 int CSR1212_KV_ID_EXTENDED_KEY_SPECIFIER_ID ; 
 int CSR1212_KV_KEY_ID_MASK ; 
 int CSR1212_KV_KEY_SHIFT ; 
 int CSR1212_KV_KEY_TYPE_MASK ; 
 int CSR1212_KV_KEY_TYPE_SHIFT ; 
#define  CSR1212_KV_TYPE_CSR_OFFSET 131 
#define  CSR1212_KV_TYPE_DIRECTORY 130 
#define  CSR1212_KV_TYPE_IMMEDIATE 129 
#define  CSR1212_KV_TYPE_LEAF 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int bytes_to_quads (int) ; 
 int cpu_to_be32 (int) ; 
 int quads_to_bytes (int) ; 

__attribute__((used)) static void
csr1212_generate_tree_subdir(struct csr1212_keyval *dir, u32 *data_buffer)
{
	struct csr1212_dentry *dentry;
	struct csr1212_keyval *last_extkey_spec = NULL;
	struct csr1212_keyval *last_extkey = NULL;
	int index = 0;

	for (dentry = dir->value.directory.dentries_head;
	     dentry;
	     dentry = dentry->next) {
		struct csr1212_keyval *a;

		for (a = dentry->kv; a; a = a->associate) {
			u32 value = 0;

			/* Special Case: Extended Key Specifier_ID */
			if (a->key.id ==
			    CSR1212_KV_ID_EXTENDED_KEY_SPECIFIER_ID) {
				if (last_extkey_spec == NULL)
					last_extkey_spec = a;
				else if (a->value.immediate !=
					 last_extkey_spec->value.immediate)
					last_extkey_spec = a;
				else
					continue;

			/* Special Case: Extended Key */
			} else if (a->key.id == CSR1212_KV_ID_EXTENDED_KEY) {
				if (last_extkey == NULL)
					last_extkey = a;
				else if (a->value.immediate !=
					 last_extkey->value.immediate)
					last_extkey = a;
				else
					continue;
			}

			switch (a->key.type) {
			case CSR1212_KV_TYPE_IMMEDIATE:
				value = a->value.immediate;
				break;
			case CSR1212_KV_TYPE_CSR_OFFSET:
				value = a->value.csr_offset;
				break;
			case CSR1212_KV_TYPE_LEAF:
				value = a->offset;
				value -= dir->offset + quads_to_bytes(1+index);
				value = bytes_to_quads(value);
				break;
			case CSR1212_KV_TYPE_DIRECTORY:
				value = a->offset;
				value -= dir->offset + quads_to_bytes(1+index);
				value = bytes_to_quads(value);
				break;
			default:
				/* Should never get here */
				WARN_ON(1);
				break;
			}

			value |= (a->key.id & CSR1212_KV_KEY_ID_MASK) <<
				 CSR1212_KV_KEY_SHIFT;
			value |= (a->key.type & CSR1212_KV_KEY_TYPE_MASK) <<
				 (CSR1212_KV_KEY_SHIFT +
				  CSR1212_KV_KEY_TYPE_SHIFT);
			data_buffer[index] = cpu_to_be32(value);
			index++;
		}
	}
}