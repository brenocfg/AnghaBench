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
struct op_counter_config {scalar_t__ enabled; } ;

/* Variables and functions */
 scalar_t__ PM_NUM_COUNTERS ; 
 int /*<<< orphan*/  oprofile_add_pc (unsigned long,int,unsigned long) ; 

__attribute__((used)) static inline void
op_add_pm(unsigned long pc, int kern, unsigned long counter,
	  struct op_counter_config *ctr, unsigned long event)
{
	unsigned long fake_counter = 2 + event;
	if (counter == 1)
		fake_counter += PM_NUM_COUNTERS;
	if (ctr[fake_counter].enabled)
		oprofile_add_pc(pc, kern, fake_counter);
}