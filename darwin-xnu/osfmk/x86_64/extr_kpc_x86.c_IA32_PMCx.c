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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ MSR_IA32_PERFCTR0 ; 
 int /*<<< orphan*/  rdmsr64 (scalar_t__) ; 
 int /*<<< orphan*/  rdpmc64 (scalar_t__) ; 

__attribute__((used)) static uint64_t
IA32_PMCx(uint32_t ctr)
{
#ifdef USE_RDPMC
	return rdpmc64(ctr);
#else /* !USE_RDPMC */
	return rdmsr64(MSR_IA32_PERFCTR0 + ctr);
#endif /* !USE_RDPMC */
}