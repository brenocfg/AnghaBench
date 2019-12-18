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
struct xt_counters {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcnt; int /*<<< orphan*/  bcnt; } ;
struct ipt_entry {TYPE_1__ counters; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_COUNTER (struct xt_counters,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
add_entry_to_counter(const struct ipt_entry *e,
		     struct xt_counters total[],
		     unsigned int *i)
{
	ADD_COUNTER(total[*i], e->counters.bcnt, e->counters.pcnt);

	(*i)++;
	return 0;
}