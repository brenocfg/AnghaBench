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
struct xt_counters {int /*<<< orphan*/  pcnt; int /*<<< orphan*/  bcnt; } ;
struct ipt_entry {int /*<<< orphan*/  counters; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_COUNTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
add_counter_to_entry(struct ipt_entry *e,
		     const struct xt_counters addme[],
		     unsigned int *i)
{
	ADD_COUNTER(e->counters, addme[*i].bcnt, addme[*i].pcnt);

	(*i)++;
	return 0;
}