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
struct TYPE_2__ {unsigned long long clock_comparator; } ;

/* Variables and functions */
 TYPE_1__ S390_lowcore ; 
 int /*<<< orphan*/  set_clock_comparator (unsigned long long) ; 

__attribute__((used)) static void fixup_clock_comparator(unsigned long long delta)
{
	/* If nobody is waiting there's nothing to fix. */
	if (S390_lowcore.clock_comparator == -1ULL)
		return;
	S390_lowcore.clock_comparator += delta;
	set_clock_comparator(S390_lowcore.clock_comparator);
}