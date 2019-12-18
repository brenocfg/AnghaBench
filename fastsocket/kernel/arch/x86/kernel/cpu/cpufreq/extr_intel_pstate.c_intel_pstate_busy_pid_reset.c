#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpudata {TYPE_1__* pstate_policy; int /*<<< orphan*/  pid; } ;
struct TYPE_2__ {int /*<<< orphan*/  deadband; int /*<<< orphan*/  setpoint; int /*<<< orphan*/  i_gain_pct; int /*<<< orphan*/  d_gain_pct; int /*<<< orphan*/  p_gain_pct; } ;

/* Variables and functions */
 int /*<<< orphan*/  pid_d_gain_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_i_gain_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_p_gain_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void intel_pstate_busy_pid_reset(struct cpudata *cpu)
{
	pid_p_gain_set(&cpu->pid, cpu->pstate_policy->p_gain_pct);
	pid_d_gain_set(&cpu->pid, cpu->pstate_policy->d_gain_pct);
	pid_i_gain_set(&cpu->pid, cpu->pstate_policy->i_gain_pct);

	pid_reset(&cpu->pid,
		cpu->pstate_policy->setpoint,
		100,
		cpu->pstate_policy->deadband,
		0);
}