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
typedef  int /*<<< orphan*/  upl_page_info_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int MAX_UPL_SIZE_BYTES ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/ * UPL_GET_INTERNAL_PAGE_LIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upl_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  upl_deallocate (int /*<<< orphan*/ ) ; 

kern_return_t
ubc_upl_commit(
	upl_t 			upl)
{
	upl_page_info_t	*pl;
	kern_return_t 	kr;

	pl = UPL_GET_INTERNAL_PAGE_LIST(upl);
	kr = upl_commit(upl, pl, MAX_UPL_SIZE_BYTES >> PAGE_SHIFT);
	upl_deallocate(upl);
	return kr;
}