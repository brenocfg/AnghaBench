#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/  proc_t ;
struct TYPE_6__ {scalar_t__ aio_lio_opcode; } ;
struct TYPE_7__ {TYPE_1__ aiocb; } ;
typedef  TYPE_2__ aio_workq_entry ;

/* Variables and functions */
 int /*<<< orphan*/  AIO_LIO ; 
 int EAGAIN ; 
 scalar_t__ LIO_NOP ; 
 TYPE_2__* aio_create_queue_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_free_request (TYPE_2__*) ; 

__attribute__((used)) static int
lio_create_entry(proc_t procp, user_addr_t aiocbp, void *group_tag,
		aio_workq_entry **entrypp )
{
	aio_workq_entry	*entryp;
	int		result;

	entryp = aio_create_queue_entry( procp, aiocbp, group_tag, AIO_LIO);
	if ( entryp == NULL ) {
		result = EAGAIN; 
		goto error_exit;
	}

	/*
	 * Look for lio_listio LIO_NOP requests and ignore them; this is
	 * not really an error, but we need to free our aio_workq_entry.
	 */
	if ( entryp->aiocb.aio_lio_opcode == LIO_NOP ) {
		result = 0;
		goto error_exit;
	}

	*entrypp = entryp;
	return( 0 );
	
error_exit:

	if ( entryp != NULL ) {
		/*
		 * This entry has not been queued up so no worries about
		 * unlocked state and aio_map
		 */
		aio_free_request(entryp);
	}
		
	return( result );
	
}