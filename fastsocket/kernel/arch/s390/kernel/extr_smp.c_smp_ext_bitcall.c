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
typedef  int /*<<< orphan*/  ec_bit_sig ;
struct TYPE_2__ {int /*<<< orphan*/  ext_call_fast; } ;

/* Variables and functions */
 TYPE_1__** lowcore_ptr ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 scalar_t__ signal_processor (int,int /*<<< orphan*/ ) ; 
 scalar_t__ sigp_busy ; 
 int /*<<< orphan*/  sigp_emergency_signal ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void smp_ext_bitcall(int cpu, ec_bit_sig sig)
{
	/*
	 * Set signaling bit in lowcore of target cpu and kick it
	 */
	set_bit(sig, (unsigned long *) &lowcore_ptr[cpu]->ext_call_fast);
	while (signal_processor(cpu, sigp_emergency_signal) == sigp_busy)
		udelay(10);
}