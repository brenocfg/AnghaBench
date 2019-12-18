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
struct task_struct {int dummy; } ;
typedef  enum cpuacct_stat_index { ____Placeholder_cpuacct_stat_index } cpuacct_stat_index ;
typedef  int /*<<< orphan*/  cputime_t ;

/* Variables and functions */

__attribute__((used)) static inline void cpuacct_update_stats(struct task_struct *tsk,
		enum cpuacct_stat_index idx, cputime_t val) {}