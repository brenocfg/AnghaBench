#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ user_addr_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  TYPE_2__* proc_t ;
struct TYPE_14__ {int aio_fildes; int /*<<< orphan*/  aio_nbytes; int /*<<< orphan*/  aio_offset; } ;
struct TYPE_16__ {int flags; TYPE_1__ aiocb; int /*<<< orphan*/  uaiocbp; int /*<<< orphan*/  procp; } ;
typedef  TYPE_3__ aio_workq_entry ;
struct TYPE_15__ {int p_aio_total_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIO_work_queued ; 
 int BSDDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_BSD_AIO ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int EAGAIN ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,int,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 TYPE_3__* aio_create_queue_entry (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aio_decrement_total_count () ; 
 int /*<<< orphan*/  aio_enqueue_work (TYPE_2__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  aio_free_request (TYPE_3__*) ; 
 scalar_t__ aio_get_process_count (TYPE_2__*) ; 
 int aio_increment_total_count () ; 
 int aio_max_requests ; 
 scalar_t__ aio_max_requests_per_process ; 
 int /*<<< orphan*/  aio_proc_lock_spin (TYPE_2__*) ; 
 int /*<<< orphan*/  aio_proc_mutex (TYPE_2__*) ; 
 int /*<<< orphan*/  aio_proc_unlock (TYPE_2__*) ; 
 scalar_t__ is_already_queued (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_convert_spin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
aio_queue_async_request(proc_t procp, user_addr_t aiocbp, int kindOfIO )
{
	aio_workq_entry	*entryp;
	int		 result;
	int		 old_count;
    uint32_t *paio_offset;
    uint32_t *paio_nbytes;
    
	old_count = aio_increment_total_count();
	if (old_count >= aio_max_requests) {
		result = EAGAIN;
		goto error_noalloc;
	}

	entryp = aio_create_queue_entry( procp, aiocbp, 0, kindOfIO);
	if ( entryp == NULL ) {
		result = EAGAIN;
		goto error_noalloc;
	}


	aio_proc_lock_spin(procp);

	if ( is_already_queued( entryp->procp, entryp->uaiocbp ) == TRUE ) {
		result = EAGAIN; 
		goto error_exit;
	}

	/* check our aio limits to throttle bad or rude user land behavior */
	if (aio_get_process_count( procp ) >= aio_max_requests_per_process) {
		printf("aio_queue_async_request(): too many in flight for proc: %d.\n", procp->p_aio_total_count);
		result = EAGAIN; 
		goto error_exit;
	}
	
	/* Add the IO to proc and work queues, wake up threads as appropriate */
	lck_mtx_convert_spin(aio_proc_mutex(procp));
	aio_enqueue_work(procp, entryp, 1);
	
	aio_proc_unlock(procp);
    
    paio_offset = (uint32_t*) &entryp->aiocb.aio_offset;
    paio_nbytes = (uint32_t*) &entryp->aiocb.aio_nbytes;
    KERNEL_DEBUG_CONSTANT( (BSDDBG_CODE(DBG_BSD_AIO, AIO_work_queued)) | DBG_FUNC_START,
                 (int)procp, (int)aiocbp, entryp->flags, entryp->aiocb.aio_fildes, 0 );
    KERNEL_DEBUG_CONSTANT( (BSDDBG_CODE(DBG_BSD_AIO, AIO_work_queued)) | DBG_FUNC_END,
                          paio_offset[0], (sizeof(entryp->aiocb.aio_offset) == sizeof(uint64_t) ? paio_offset[1] : 0),
                          paio_nbytes[0], (sizeof(entryp->aiocb.aio_nbytes) == sizeof(uint64_t) ? paio_nbytes[1] : 0),
                          0 );
    
	return( 0 );
	
error_exit:
	/*
	 * This entry has not been queued up so no worries about
	 * unlocked state and aio_map
	 */
	aio_proc_unlock(procp);
	aio_free_request(entryp);

error_noalloc:
	aio_decrement_total_count();

	return( result );
	
}