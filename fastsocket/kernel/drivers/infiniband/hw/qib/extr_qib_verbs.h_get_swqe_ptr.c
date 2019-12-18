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
struct qib_swqe {int dummy; } ;
struct qib_sge {int dummy; } ;
struct qib_qp {int s_max_sge; scalar_t__ s_wq; } ;

/* Variables and functions */

__attribute__((used)) static inline struct qib_swqe *get_swqe_ptr(struct qib_qp *qp,
					      unsigned n)
{
	return (struct qib_swqe *)((char *)qp->s_wq +
				     (sizeof(struct qib_swqe) +
				      qp->s_max_sge *
				      sizeof(struct qib_sge)) * n);
}