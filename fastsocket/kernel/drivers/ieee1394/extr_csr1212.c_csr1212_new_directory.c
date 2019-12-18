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
struct TYPE_4__ {int /*<<< orphan*/ * dentries_tail; int /*<<< orphan*/ * dentries_head; scalar_t__ len; } ;
struct TYPE_3__ {TYPE_2__ directory; } ;
struct csr1212_keyval {int valid; TYPE_1__ value; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR1212_KV_TYPE_DIRECTORY ; 
 struct csr1212_keyval* csr1212_new_keyval (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct csr1212_keyval *csr1212_new_directory(u8 key)
{
	struct csr1212_keyval *kv;

	kv = csr1212_new_keyval(CSR1212_KV_TYPE_DIRECTORY, key);
	if (!kv)
		return NULL;

	kv->value.directory.len = 0;
	kv->offset = 0;
	kv->value.directory.dentries_head = NULL;
	kv->value.directory.dentries_tail = NULL;
	kv->valid = 1;
	return kv;
}