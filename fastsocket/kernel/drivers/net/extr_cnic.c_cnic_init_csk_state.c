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
struct cnic_sock {int /*<<< orphan*/  flags; scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SK_F_CLOSING ; 
 int /*<<< orphan*/  SK_F_OFFLD_SCHED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cnic_init_csk_state(struct cnic_sock *csk)
{
	csk->state = 0;
	clear_bit(SK_F_OFFLD_SCHED, &csk->flags);
	clear_bit(SK_F_CLOSING, &csk->flags);
}