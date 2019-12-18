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
typedef  int /*<<< orphan*/  physid_mask_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_id ; 
 int /*<<< orphan*/  physid_mask_of_physid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static physid_mask_t es7000_apicid_to_cpu_present(int phys_apicid)
{
	physid_mask_t mask;

	mask = physid_mask_of_physid(cpu_id);
	++cpu_id;

	return mask;
}