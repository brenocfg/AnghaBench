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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  MMU_SEGSIZE_256M ; 
 int /*<<< orphan*/  beat_htab_lock ; 
 unsigned long beat_lpar_hpte_find (unsigned long,int) ; 
 unsigned long beat_write_htab_entry (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long get_kernel_vsid (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void beat_lpar_hpte_updateboltedpp(unsigned long newpp,
					  unsigned long ea,
					  int psize, int ssize)
{
	unsigned long lpar_rc, slot, vsid, va;
	u64 dummy0, dummy1;

	vsid = get_kernel_vsid(ea, MMU_SEGSIZE_256M);
	va = (vsid << 28) | (ea & 0x0fffffff);

	spin_lock(&beat_htab_lock);
	slot = beat_lpar_hpte_find(va, psize);
	BUG_ON(slot == -1);

	lpar_rc = beat_write_htab_entry(0, slot, 0, newpp, 0, 7,
		&dummy0, &dummy1);
	spin_unlock(&beat_htab_lock);

	BUG_ON(lpar_rc != 0);
}