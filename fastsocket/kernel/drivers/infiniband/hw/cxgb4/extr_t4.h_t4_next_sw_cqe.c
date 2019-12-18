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
struct t4_cqe {int dummy; } ;
struct t4_cq {size_t sw_cidx; struct t4_cqe* sw_queue; scalar_t__ sw_in_use; } ;

/* Variables and functions */

__attribute__((used)) static inline struct t4_cqe *t4_next_sw_cqe(struct t4_cq *cq)
{
	if (cq->sw_in_use)
		return &cq->sw_queue[cq->sw_cidx];
	return NULL;
}