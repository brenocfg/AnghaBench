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
typedef  int uint64_t ;
struct TYPE_2__ {int reset_counter1; scalar_t__ reset_counter2; } ;

/* Variables and functions */
 TYPE_1__ reg ; 
 int /*<<< orphan*/  write_c0_perfcount (int) ; 

__attribute__((used)) static void rm9000_cpu_setup(void *args)
{
	uint64_t perfcount;

	perfcount = ((uint64_t) reg.reset_counter2 << 32) | reg.reset_counter1;
	write_c0_perfcount(perfcount);
}