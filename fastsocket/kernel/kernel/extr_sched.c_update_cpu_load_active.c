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
struct rq {int /*<<< orphan*/  calc_load_update; } ;

/* Variables and functions */
 scalar_t__ LOAD_FREQ ; 
 int /*<<< orphan*/  calc_load_account_active (struct rq*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_after_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_cpu_load (struct rq*) ; 

__attribute__((used)) static void update_cpu_load_active(struct rq *this_rq)
{
	update_cpu_load(this_rq);

	if (time_after_eq(jiffies, this_rq->calc_load_update)) {
		this_rq->calc_load_update += LOAD_FREQ;
		calc_load_account_active(this_rq);
	}
}