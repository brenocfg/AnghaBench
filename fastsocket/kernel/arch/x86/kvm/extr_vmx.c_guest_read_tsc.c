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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int /*<<< orphan*/  TSC_OFFSET ; 
 int /*<<< orphan*/  rdtscll (scalar_t__) ; 
 scalar_t__ vmcs_read64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 guest_read_tsc(void)
{
	u64 host_tsc, tsc_offset;

	rdtscll(host_tsc);
	tsc_offset = vmcs_read64(TSC_OFFSET);
	return host_tsc + tsc_offset;
}