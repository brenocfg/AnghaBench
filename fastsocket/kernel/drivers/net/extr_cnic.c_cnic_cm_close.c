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
struct cnic_sock {int /*<<< orphan*/  flags; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EALREADY ; 
 int EINVAL ; 
 int /*<<< orphan*/  L4_KCQE_OPCODE_VALUE_CLOSE_COMP ; 
 int /*<<< orphan*/  SK_F_PG_OFFLD_COMPLETE ; 
 scalar_t__ cnic_close_prep (struct cnic_sock*) ; 
 int cnic_cm_close_req (struct cnic_sock*) ; 
 int /*<<< orphan*/  cnic_in_use (struct cnic_sock*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cnic_cm_close(struct cnic_sock *csk)
{
	if (!cnic_in_use(csk))
		return -EINVAL;

	if (cnic_close_prep(csk)) {
		csk->state = L4_KCQE_OPCODE_VALUE_CLOSE_COMP;
		return cnic_cm_close_req(csk);
	} else {
		/* Wait for remote reset sequence to complete */
		while (test_bit(SK_F_PG_OFFLD_COMPLETE, &csk->flags))
			msleep(1);

		return -EALREADY;
	}
	return 0;
}