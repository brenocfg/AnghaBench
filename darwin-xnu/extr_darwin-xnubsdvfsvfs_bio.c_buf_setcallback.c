#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  errno_t ;
typedef  TYPE_1__* buf_t ;
struct TYPE_5__ {int b_flags; int b_lflags; void (* b_iodone ) (TYPE_1__*,void*) ;void* b_transaction; } ;

/* Variables and functions */
 int /*<<< orphan*/  BL_BUSY ; 
 int B_ASYNC ; 
 int B_CALL ; 
 int /*<<< orphan*/  B_FILTER ; 
 scalar_t__ ISSET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

errno_t
buf_setcallback(buf_t bp, void (*callback)(buf_t, void *), void *transaction)
{
	assert(!ISSET(bp->b_flags, B_FILTER) && ISSET(bp->b_lflags, BL_BUSY));

	if (callback)
	        bp->b_flags |= (B_CALL | B_ASYNC);
	else
	        bp->b_flags &= ~B_CALL;
	bp->b_transaction = transaction;
	bp->b_iodone = callback;

	return (0);
}