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
struct gru_control_block_status {scalar_t__ istatus; } ;

/* Variables and functions */
 scalar_t__ CBS_ACTIVE ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  cpu_relax () ; 

__attribute__((used)) static int gru_wait_idle_or_exception(struct gru_control_block_status *gen)
{
	while (gen->istatus >= CBS_ACTIVE) {
		cpu_relax();
		barrier();
	}
	return gen->istatus;
}