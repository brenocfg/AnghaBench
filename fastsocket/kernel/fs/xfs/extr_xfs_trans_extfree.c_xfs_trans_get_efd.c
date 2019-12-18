#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  t_mountp; } ;
typedef  TYPE_1__ xfs_trans_t ;
typedef  int /*<<< orphan*/  xfs_efi_log_item_t ;
struct TYPE_8__ {int /*<<< orphan*/  efd_item; } ;
typedef  TYPE_2__ xfs_efd_log_item_t ;
typedef  scalar_t__ uint ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_2__* xfs_efd_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  xfs_trans_add_item (TYPE_1__*,int /*<<< orphan*/ *) ; 

xfs_efd_log_item_t *
xfs_trans_get_efd(xfs_trans_t		*tp,
		  xfs_efi_log_item_t	*efip,
		  uint			nextents)
{
	xfs_efd_log_item_t	*efdp;

	ASSERT(tp != NULL);
	ASSERT(nextents > 0);

	efdp = xfs_efd_init(tp->t_mountp, efip, nextents);
	ASSERT(efdp != NULL);

	/*
	 * Get a log_item_desc to point at the new item.
	 */
	xfs_trans_add_item(tp, &efdp->efd_item);
	return efdp;
}