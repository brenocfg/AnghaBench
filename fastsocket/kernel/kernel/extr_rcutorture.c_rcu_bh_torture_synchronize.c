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
struct rcu_bh_torture_synchronize {int /*<<< orphan*/  completion; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_bh_torture_wakeme_after_cb ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rcu_bh_torture_synchronize(void)
{
	struct rcu_bh_torture_synchronize rcu;

	init_completion(&rcu.completion);
	call_rcu_bh(&rcu.head, rcu_bh_torture_wakeme_after_cb);
	wait_for_completion(&rcu.completion);
}