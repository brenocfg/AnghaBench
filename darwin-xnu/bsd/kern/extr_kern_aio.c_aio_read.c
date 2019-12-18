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
struct aio_read_args {scalar_t__ aiocbp; } ;
typedef  scalar_t__ proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  AIO_READ ; 
 int /*<<< orphan*/  AIO_read ; 
 int BSDDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_BSD_AIO ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int aio_queue_async_request (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

int
aio_read(proc_t p, struct aio_read_args *uap, int *retval )
{
	int			error;

	KERNEL_DEBUG( (BSDDBG_CODE(DBG_BSD_AIO, AIO_read)) | DBG_FUNC_START,
		     	  (int)p, (int)uap->aiocbp, 0, 0, 0 );
	
	*retval = 0;

	error = aio_queue_async_request( p, uap->aiocbp, AIO_READ );
	if ( error != 0 )
		*retval = -1;

	KERNEL_DEBUG( (BSDDBG_CODE(DBG_BSD_AIO, AIO_read)) | DBG_FUNC_END,
		     	  (int)p, (int)uap->aiocbp, error, 0, 0 );
		
	return( error );

}