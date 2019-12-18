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
typedef  int /*<<< orphan*/  pmap_paddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MRS (int /*<<< orphan*/ ,char*) ; 

pmap_paddr_t get_mmu_ttb(void)
{
	pmap_paddr_t	value;

	MRS(value, "TTBR0_EL1");
	return value;
}