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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_DIAG ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kalloc_tag (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ kpc_get_counterbuf_size () ; 
 int /*<<< orphan*/  sysctl_lock ; 

__attribute__((used)) static uint64_t *
kpc_get_bigarray(uint32_t *size_out)
{
	static uint64_t *bigarray = NULL;

	LCK_MTX_ASSERT(&sysctl_lock, LCK_MTX_ASSERT_OWNED);

	uint32_t size = kpc_get_counterbuf_size() + sizeof(uint64_t);
	*size_out = size;

	if (bigarray) {
		return bigarray;
	}

	/*
	 * Another element is needed to hold the CPU number when getting counter
	 * values.
	 */
	bigarray = kalloc_tag(size, VM_KERN_MEMORY_DIAG);
	assert(bigarray != NULL);
	return bigarray;
}