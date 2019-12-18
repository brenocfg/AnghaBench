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

/* Variables and functions */
 int /*<<< orphan*/  ia64_fc (void*) ; 
 int /*<<< orphan*/  ia64_srlz_i () ; 
 int /*<<< orphan*/  ia64_sync_i () ; 

__attribute__((used)) static void kvm_flush_icache(unsigned long start, unsigned long len)
{
	int l;

	for (l = 0; l < (len + 32); l += 32)
		ia64_fc((void *)(start + l));

	ia64_sync_i();
	ia64_srlz_i();
}