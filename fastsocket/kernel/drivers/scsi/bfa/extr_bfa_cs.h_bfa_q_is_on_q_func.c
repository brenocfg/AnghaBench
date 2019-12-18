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
struct list_head {int dummy; } ;

/* Variables and functions */
 struct list_head* bfa_q_next (struct list_head*) ; 

__attribute__((used)) static inline int
bfa_q_is_on_q_func(struct list_head *q, struct list_head *qe)
{
	struct list_head        *tqe;

	tqe = bfa_q_next(q);
	while (tqe != q) {
		if (tqe == qe)
			return 1;
		tqe = bfa_q_next(tqe);
		if (tqe == NULL)
			break;
	}
	return 0;
}