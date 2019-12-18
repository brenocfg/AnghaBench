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
struct cnic_sock {int /*<<< orphan*/  state; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  L4_KCQE_OPCODE_VALUE_RESET_COMP ; 
 int /*<<< orphan*/  SK_F_CONNECT_START ; 
 int /*<<< orphan*/  SK_F_OFFLD_COMPLETE ; 
 int /*<<< orphan*/  SK_F_OFFLD_SCHED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  smp_mb__after_clear_bit () ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cnic_abort_prep(struct cnic_sock *csk)
{
	clear_bit(SK_F_CONNECT_START, &csk->flags);
	smp_mb__after_clear_bit();

	while (test_and_set_bit(SK_F_OFFLD_SCHED, &csk->flags))
		msleep(1);

	if (test_and_clear_bit(SK_F_OFFLD_COMPLETE, &csk->flags)) {
		csk->state = L4_KCQE_OPCODE_VALUE_RESET_COMP;
		return 1;
	}

	return 0;
}