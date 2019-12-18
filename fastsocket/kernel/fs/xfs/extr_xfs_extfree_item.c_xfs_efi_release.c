#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  efi_flags; int /*<<< orphan*/  efi_next_extent; } ;
typedef  TYPE_1__ xfs_efi_log_item_t ;
typedef  scalar_t__ uint ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_EFI_RECOVERED ; 
 int /*<<< orphan*/  __xfs_efi_release (TYPE_1__*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_sub_and_test (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
xfs_efi_release(xfs_efi_log_item_t	*efip,
		uint			nextents)
{
	ASSERT(atomic_read(&efip->efi_next_extent) >= nextents);
	if (atomic_sub_and_test(nextents, &efip->efi_next_extent)) {
		/* recovery needs us to drop the EFI reference, too */
		if (test_bit(XFS_EFI_RECOVERED, &efip->efi_flags))
			__xfs_efi_release(efip);

		__xfs_efi_release(efip);
		/* efip may now have been freed, do not reference it again. */
	}
}