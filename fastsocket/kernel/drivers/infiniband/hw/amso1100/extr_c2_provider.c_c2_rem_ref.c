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
struct ib_qp {int dummy; } ;
struct c2_qp {int /*<<< orphan*/  wait; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 struct c2_qp* to_c2qp (struct ib_qp*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void c2_rem_ref(struct ib_qp *ibqp)
{
	struct c2_qp *qp;
	BUG_ON(!ibqp);
	qp = to_c2qp(ibqp);
	if (atomic_dec_and_test(&qp->refcount))
		wake_up(&qp->wait);
}