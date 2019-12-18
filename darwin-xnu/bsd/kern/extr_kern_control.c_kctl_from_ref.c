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
struct kctl {scalar_t__ kctlref; } ;
typedef  scalar_t__ kern_ctl_ref ;
struct TYPE_2__ {int /*<<< orphan*/  kcs_bad_kctlref; } ;

/* Variables and functions */
 uintptr_t KCTLREF_INDEX_MASK ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  ctl_mtx ; 
 struct kctl** kctl_table ; 
 uintptr_t kctl_tbl_size ; 
 TYPE_1__ kctlstat ; 
 int /*<<< orphan*/  lck_mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct kctl *
kctl_from_ref(kern_ctl_ref kctlref)
{
	/*
	 * Reference is index plus one
	 */
	uintptr_t i = (((uintptr_t)kctlref) & KCTLREF_INDEX_MASK) - 1;
	struct kctl *kctl = NULL;

	lck_mtx_assert(ctl_mtx, LCK_MTX_ASSERT_OWNED);

	if (i >= kctl_tbl_size) {
		kctlstat.kcs_bad_kctlref++;
		return (NULL);
	}
	kctl = kctl_table[i];
	if (kctl->kctlref != kctlref) {
		kctlstat.kcs_bad_kctlref++;
		return (NULL);
	}
	return (kctl);
}