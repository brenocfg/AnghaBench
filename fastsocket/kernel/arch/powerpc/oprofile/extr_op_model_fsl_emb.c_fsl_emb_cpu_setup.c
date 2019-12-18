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
struct op_counter_config {int /*<<< orphan*/  kernel; int /*<<< orphan*/  user; int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_pmc_stop (int) ; 
 int num_counters ; 
 int /*<<< orphan*/  pmc_stop_ctrs () ; 
 int /*<<< orphan*/  set_pmc_event (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pmc_user_kernel (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsl_emb_cpu_setup(struct op_counter_config *ctr)
{
	int i;

	/* freeze all counters */
	pmc_stop_ctrs();

	for (i = 0;i < num_counters;i++) {
		init_pmc_stop(i);

		set_pmc_event(i, ctr[i].event);

		set_pmc_user_kernel(i, ctr[i].user, ctr[i].kernel);
	}

	return 0;
}