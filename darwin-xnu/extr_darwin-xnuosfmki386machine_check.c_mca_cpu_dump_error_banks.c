#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mca_is_valid; } ;
typedef  TYPE_1__ mca_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  mca_dump_bank (TYPE_1__*,unsigned int) ; 
 unsigned int mca_error_bank_count ; 

__attribute__((used)) static void
mca_cpu_dump_error_banks(mca_state_t *state)
{
	unsigned int 		i;

	if (!state->mca_is_valid)
		return;

	for (i = 0; i < mca_error_bank_count; i++ ) {
		mca_dump_bank(state, i);
	}
}