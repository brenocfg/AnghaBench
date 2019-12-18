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
struct csr1212_keyval {int /*<<< orphan*/  valid; } ;
struct csr1212_csr {int dummy; } ;

/* Variables and functions */
 scalar_t__ CSR1212_SUCCESS ; 
 scalar_t__ csr1212_read_keyval (struct csr1212_csr*,struct csr1212_keyval*) ; 

struct csr1212_keyval *
csr1212_get_keyval(struct csr1212_csr *csr, struct csr1212_keyval *kv)
{
	if (!kv)
		return NULL;
	if (!kv->valid)
		if (csr1212_read_keyval(csr, kv) != CSR1212_SUCCESS)
			return NULL;
	return kv;
}