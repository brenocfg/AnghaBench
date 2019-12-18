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
typedef  scalar_t__ u32 ;
struct cnic_sock {scalar_t__ state; int /*<<< orphan*/  flags; TYPE_1__* dev; } ;
struct cnic_local {int /*<<< orphan*/  (* close_conn ) (struct cnic_sock*,scalar_t__) ;} ;
struct TYPE_2__ {struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 int EALREADY ; 
 int EINVAL ; 
 scalar_t__ L4_KCQE_OPCODE_VALUE_RESET_COMP ; 
 int /*<<< orphan*/  SK_F_PG_OFFLD_COMPLETE ; 
 scalar_t__ cnic_abort_prep (struct cnic_sock*) ; 
 int cnic_cm_abort_req (struct cnic_sock*) ; 
 int /*<<< orphan*/  cnic_in_use (struct cnic_sock*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct cnic_sock*,scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cnic_cm_abort(struct cnic_sock *csk)
{
	struct cnic_local *cp = csk->dev->cnic_priv;
	u32 opcode = L4_KCQE_OPCODE_VALUE_RESET_COMP;

	if (!cnic_in_use(csk))
		return -EINVAL;

	if (cnic_abort_prep(csk))
		return cnic_cm_abort_req(csk);

	/* Getting here means that we haven't started connect, or
	 * connect was not successful, or it has been reset by the target.
	 */

	cp->close_conn(csk, opcode);
	if (csk->state != opcode) {
		/* Wait for remote reset sequence to complete */
		while (test_bit(SK_F_PG_OFFLD_COMPLETE, &csk->flags))
			msleep(1);

		return -EALREADY;
	}

	return 0;
}