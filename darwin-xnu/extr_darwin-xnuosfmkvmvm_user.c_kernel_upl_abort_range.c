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
typedef  int /*<<< orphan*/  upl_offset_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int UPL_COMMIT_FREE_ON_EMPTY ; 
 int UPL_COMMIT_NOTIFY_EMPTY ; 
 int /*<<< orphan*/  upl_abort_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  upl_deallocate (int /*<<< orphan*/ ) ; 

kern_return_t
kernel_upl_abort_range(
	upl_t			upl,
	upl_offset_t		offset,
	upl_size_t		size,
	int			abort_flags)
{
	kern_return_t 		kr;
	boolean_t		finished = FALSE;

	if (abort_flags & UPL_COMMIT_FREE_ON_EMPTY)
		abort_flags |= UPL_COMMIT_NOTIFY_EMPTY;

	kr = upl_abort_range(upl, offset, size, abort_flags, &finished);

	if ((abort_flags & UPL_COMMIT_FREE_ON_EMPTY) && finished)
		upl_deallocate(upl);

	return kr;
}