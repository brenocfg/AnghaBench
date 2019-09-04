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
typedef  int /*<<< orphan*/  upl_t ;
typedef  int /*<<< orphan*/  upl_size_t ;
typedef  int /*<<< orphan*/  upl_page_info_t ;
typedef  int /*<<< orphan*/  upl_offset_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int MAX_UPL_SIZE_BYTES ; 
 int PAGE_SHIFT ; 
 int UPL_COMMIT_FREE_ON_EMPTY ; 
 int UPL_COMMIT_KERNEL_ONLY_FLAGS ; 
 int UPL_COMMIT_NOTIFY_EMPTY ; 
 int /*<<< orphan*/ * UPL_GET_INTERNAL_PAGE_LIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upl_commit_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,scalar_t__*) ; 
 int /*<<< orphan*/  upl_deallocate (int /*<<< orphan*/ ) ; 

kern_return_t
ubc_upl_commit_range(
	upl_t 			upl,
	upl_offset_t		offset,
	upl_size_t		size,
	int				flags)
{
	upl_page_info_t	*pl;
	boolean_t		empty;
	kern_return_t 	kr;

	if (flags & UPL_COMMIT_FREE_ON_EMPTY)
		flags |= UPL_COMMIT_NOTIFY_EMPTY;

	if (flags & UPL_COMMIT_KERNEL_ONLY_FLAGS) {
		return KERN_INVALID_ARGUMENT;
	}

	pl = UPL_GET_INTERNAL_PAGE_LIST(upl);

	kr = upl_commit_range(upl, offset, size, flags,
			      pl, MAX_UPL_SIZE_BYTES >> PAGE_SHIFT, &empty);

	if((flags & UPL_COMMIT_FREE_ON_EMPTY) && empty)
		upl_deallocate(upl);

	return kr;
}