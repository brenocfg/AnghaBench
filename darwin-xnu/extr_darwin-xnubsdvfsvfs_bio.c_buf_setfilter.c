#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* buf_t ;
struct TYPE_6__ {void (* b_iodone ) (TYPE_1__*,void*) ;int /*<<< orphan*/  b_flags; void* b_transaction; int /*<<< orphan*/  b_lflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BL_BUSY ; 
 int /*<<< orphan*/  B_FILTER ; 
 int /*<<< orphan*/  ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void
buf_setfilter(buf_t bp, void (*filter)(buf_t, void *), void *transaction,
			  void (**old_iodone)(buf_t, void *), void **old_transaction)
{
	assert(ISSET(bp->b_lflags, BL_BUSY));

	if (old_iodone)
		*old_iodone = bp->b_iodone;
	if (old_transaction)
		*old_transaction = bp->b_transaction;

	bp->b_transaction = transaction;
	bp->b_iodone = filter;
	if (filter)
	        bp->b_flags |= B_FILTER;
	else
	        bp->b_flags &= ~B_FILTER;
}