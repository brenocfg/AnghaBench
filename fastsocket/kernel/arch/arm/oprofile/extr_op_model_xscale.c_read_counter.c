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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ PMU_XSC1 ; 
 int /*<<< orphan*/  __xsc1_read_counter (int) ; 
 int /*<<< orphan*/  __xsc2_read_counter (int) ; 
 TYPE_1__* pmu ; 

__attribute__((used)) static u32 read_counter(int counter)
{
	u32 val;

	if (pmu->id == PMU_XSC1)
		val = __xsc1_read_counter(counter);
	else
		val = __xsc2_read_counter(counter);

	return val;
}