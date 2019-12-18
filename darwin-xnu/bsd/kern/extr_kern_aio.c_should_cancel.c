#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ user_addr_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {int aio_fildes; } ;
struct TYPE_5__ {scalar_t__ uaiocbp; TYPE_1__ aiocb; } ;
typedef  TYPE_2__ aio_workq_entry ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ USER_ADDR_NULL ; 

__attribute__((used)) static boolean_t
should_cancel(aio_workq_entry *entryp, user_addr_t aiocbp, int fd) 
{
	if ( (aiocbp == USER_ADDR_NULL && fd == 0) ||
			(aiocbp != USER_ADDR_NULL && entryp->uaiocbp == aiocbp) ||
			(aiocbp == USER_ADDR_NULL && fd == entryp->aiocb.aio_fildes) ) {
		return TRUE;
	}

	return FALSE;
}