#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int max_cnt; } ;
struct ocrdma_srq {int bit_fields_len; TYPE_1__ rq; scalar_t__* idx_bit_fields; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int ffs (scalar_t__) ; 
 int /*<<< orphan*/  ocrdma_srq_toggle_bit (struct ocrdma_srq*,int) ; 

__attribute__((used)) static int ocrdma_srq_get_idx(struct ocrdma_srq *srq)
{
	int row = 0;
	int indx = 0;

	for (row = 0; row < srq->bit_fields_len; row++) {
		if (srq->idx_bit_fields[row]) {
			indx = ffs(srq->idx_bit_fields[row]);
			indx = (row * 32) + (indx - 1);
			if (indx >= srq->rq.max_cnt)
				BUG();
			ocrdma_srq_toggle_bit(srq, indx);
			break;
		}
	}

	if (row == srq->bit_fields_len)
		BUG();
	return indx;
}