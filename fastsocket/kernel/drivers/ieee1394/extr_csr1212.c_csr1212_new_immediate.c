#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  immediate; } ;
struct csr1212_keyval {int valid; TYPE_1__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR1212_KV_TYPE_IMMEDIATE ; 
 struct csr1212_keyval* csr1212_new_keyval (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct csr1212_keyval *csr1212_new_immediate(u8 key, u32 value)
{
	struct csr1212_keyval *kv;

	kv = csr1212_new_keyval(CSR1212_KV_TYPE_IMMEDIATE, key);
	if (!kv)
		return NULL;

	kv->value.immediate = value;
	kv->valid = 1;
	return kv;
}