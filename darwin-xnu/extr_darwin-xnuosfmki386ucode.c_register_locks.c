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
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_NO_SPACE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_attr_free (scalar_t__) ; 
 scalar_t__ lck_grp_alloc_init (char*,scalar_t__) ; 
 scalar_t__ lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_attr_free (scalar_t__) ; 
 int /*<<< orphan*/  lck_grp_attr_setstat (scalar_t__) ; 
 int /*<<< orphan*/  lck_grp_free (scalar_t__) ; 
 scalar_t__ lck_spin_alloc_init (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lck_spin_free (scalar_t__,scalar_t__) ; 
 scalar_t__ ucode_slock ; 
 scalar_t__ ucode_slock_attr ; 
 scalar_t__ ucode_slock_grp ; 
 scalar_t__ ucode_slock_grp_attr ; 

__attribute__((used)) static kern_return_t
register_locks(void)
{
	/* already allocated? */
	if (ucode_slock_grp_attr && ucode_slock_grp && ucode_slock_attr && ucode_slock)
		return KERN_SUCCESS;

	/* allocate lock group attribute and group */
	if (!(ucode_slock_grp_attr = lck_grp_attr_alloc_init()))
		goto nomem_out;

	lck_grp_attr_setstat(ucode_slock_grp_attr);

	if (!(ucode_slock_grp = lck_grp_alloc_init("uccode_lock", ucode_slock_grp_attr)))
		goto nomem_out;

	/* Allocate lock attribute */
	if (!(ucode_slock_attr = lck_attr_alloc_init()))
		goto nomem_out;

	/* Allocate the spin lock */
	/* We keep one global spin-lock. We could have one per update
	 * request... but srsly, why would you update microcode like that?
	 */
	if (!(ucode_slock = lck_spin_alloc_init(ucode_slock_grp, ucode_slock_attr)))
		goto nomem_out;

	return KERN_SUCCESS;

nomem_out:
	/* clean up */
	if (ucode_slock)
		lck_spin_free(ucode_slock, ucode_slock_grp);
	if (ucode_slock_attr)
		lck_attr_free(ucode_slock_attr);
	if (ucode_slock_grp)
		lck_grp_free(ucode_slock_grp);
	if (ucode_slock_grp_attr)
		lck_grp_attr_free(ucode_slock_grp_attr);

	return KERN_NO_SPACE;
}