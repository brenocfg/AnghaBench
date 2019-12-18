#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_4__ {size_t size; size_t pidx; TYPE_1__* oldest_read; TYPE_1__* sw_sq; } ;
struct t4_wq {TYPE_2__ sq; } ;
struct TYPE_3__ {scalar_t__ opcode; } ;

/* Variables and functions */
 scalar_t__ FW_RI_READ_REQ ; 

__attribute__((used)) static void advance_oldest_read(struct t4_wq *wq)
{

	u32 rptr = wq->sq.oldest_read - wq->sq.sw_sq + 1;

	if (rptr == wq->sq.size)
		rptr = 0;
	while (rptr != wq->sq.pidx) {
		wq->sq.oldest_read = &wq->sq.sw_sq[rptr];

		if (wq->sq.oldest_read->opcode == FW_RI_READ_REQ)
			return;
		if (++rptr == wq->sq.size)
			rptr = 0;
	}
	wq->sq.oldest_read = NULL;
}