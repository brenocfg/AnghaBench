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
struct stripe_head {int /*<<< orphan*/  state; scalar_t__ reconstruct_state; scalar_t__ check_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  STRIPE_BIOFILL_RUN ; 
 int /*<<< orphan*/  STRIPE_COMPUTE_RUN ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stripe_operations_active(struct stripe_head *sh)
{
	return sh->check_state || sh->reconstruct_state ||
	       test_bit(STRIPE_BIOFILL_RUN, &sh->state) ||
	       test_bit(STRIPE_COMPUTE_RUN, &sh->state);
}