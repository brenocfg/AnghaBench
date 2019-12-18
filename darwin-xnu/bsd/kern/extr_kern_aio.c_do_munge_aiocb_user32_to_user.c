#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sival_int; } ;
struct TYPE_7__ {TYPE_1__ size_equivalent; } ;
struct TYPE_9__ {void* sigev_notify_attributes; void* sigev_notify_function; TYPE_2__ sigev_value; int /*<<< orphan*/  sigev_signo; int /*<<< orphan*/  sigev_notify; } ;
struct user_aiocb {TYPE_4__ aio_sigevent; int /*<<< orphan*/  aio_lio_opcode; int /*<<< orphan*/  aio_reqprio; int /*<<< orphan*/  aio_nbytes; void* aio_buf; int /*<<< orphan*/  aio_offset; int /*<<< orphan*/  aio_fildes; } ;
struct TYPE_8__ {int /*<<< orphan*/  sival_int; } ;
struct TYPE_10__ {int /*<<< orphan*/  sigev_notify_attributes; int /*<<< orphan*/  sigev_notify_function; TYPE_3__ sigev_value; int /*<<< orphan*/  sigev_signo; int /*<<< orphan*/  sigev_notify; } ;
struct user32_aiocb {TYPE_5__ aio_sigevent; int /*<<< orphan*/  aio_lio_opcode; int /*<<< orphan*/  aio_reqprio; int /*<<< orphan*/  aio_nbytes; int /*<<< orphan*/  aio_buf; int /*<<< orphan*/  aio_offset; int /*<<< orphan*/  aio_fildes; } ;

/* Variables and functions */
 void* CAST_USER_ADDR_T (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void 
do_munge_aiocb_user32_to_user( struct user32_aiocb *my_aiocbp, struct user_aiocb *the_user_aiocbp ) 
{
	the_user_aiocbp->aio_fildes = my_aiocbp->aio_fildes;
	the_user_aiocbp->aio_offset = my_aiocbp->aio_offset;
	the_user_aiocbp->aio_buf = CAST_USER_ADDR_T(my_aiocbp->aio_buf);
	the_user_aiocbp->aio_nbytes = my_aiocbp->aio_nbytes;
	the_user_aiocbp->aio_reqprio = my_aiocbp->aio_reqprio;
	the_user_aiocbp->aio_lio_opcode = my_aiocbp->aio_lio_opcode;

	/* special case here.  since we do not know if sigev_value is an */
	/* int or a ptr we do NOT cast the ptr to a user_addr_t.   This  */
	/* means if we send this info back to user space we need to remember */
	/* sigev_value was not expanded for the 32-bit case.  */
	/* NOTE - this does NOT affect us since we don't support sigev_value */
	/* yet in the aio context.  */
	//LP64
	the_user_aiocbp->aio_sigevent.sigev_notify = my_aiocbp->aio_sigevent.sigev_notify;
	the_user_aiocbp->aio_sigevent.sigev_signo = my_aiocbp->aio_sigevent.sigev_signo;
	the_user_aiocbp->aio_sigevent.sigev_value.size_equivalent.sival_int = 
		my_aiocbp->aio_sigevent.sigev_value.sival_int;
	the_user_aiocbp->aio_sigevent.sigev_notify_function = 
		CAST_USER_ADDR_T(my_aiocbp->aio_sigevent.sigev_notify_function);
	the_user_aiocbp->aio_sigevent.sigev_notify_attributes = 
		CAST_USER_ADDR_T(my_aiocbp->aio_sigevent.sigev_notify_attributes);
}