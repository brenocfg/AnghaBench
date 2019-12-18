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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ MSR_IA32_PERF_FIXED_CTR0 ; 
 int RDPMC_FIXED_COUNTER_SELECTOR ; 
 int /*<<< orphan*/  rdmsr64 (scalar_t__) ; 
 int /*<<< orphan*/  rdpmc64 (int) ; 

__attribute__((used)) static uint64_t
IA32_FIXED_CTRx(uint32_t ctr)
{
#ifdef USE_RDPMC
	return rdpmc64(RDPMC_FIXED_COUNTER_SELECTOR | ctr);
#else /* !USE_RDPMC */
	return rdmsr64(MSR_IA32_PERF_FIXED_CTR0 + ctr);
#endif /* !USE_RDPMC */
}