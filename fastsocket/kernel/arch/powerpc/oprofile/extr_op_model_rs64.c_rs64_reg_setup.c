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
struct op_system_config {int dummy; } ;
struct op_counter_config {scalar_t__ count; } ;

/* Variables and functions */
 int num_counters ; 
 scalar_t__* reset_value ; 

__attribute__((used)) static int rs64_reg_setup(struct op_counter_config *ctr,
			   struct op_system_config *sys,
			   int num_ctrs)
{
	int i;

	num_counters = num_ctrs;

	for (i = 0; i < num_counters; ++i)
		reset_value[i] = 0x80000000UL - ctr[i].count;

	/* XXX setup user and kernel profiling */
	return 0;
}