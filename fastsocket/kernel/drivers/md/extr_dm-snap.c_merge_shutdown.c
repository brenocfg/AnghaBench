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
struct dm_snapshot {int /*<<< orphan*/  state_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  RUNNING_MERGE ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_clear_bit () ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void merge_shutdown(struct dm_snapshot *s)
{
	clear_bit_unlock(RUNNING_MERGE, &s->state_bits);
	smp_mb__after_clear_bit();
	wake_up_bit(&s->state_bits, RUNNING_MERGE);
}