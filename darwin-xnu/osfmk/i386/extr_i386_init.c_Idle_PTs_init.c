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

/* Variables and functions */
 scalar_t__ ALLOCPAGES (int) ; 
 scalar_t__ ID_MAP_VTOP (scalar_t__) ; 
 int /*<<< orphan*/  INTEL_PTE_WRITE ; 
 scalar_t__ IdlePDPT ; 
 scalar_t__ IdlePML4 ; 
 scalar_t__ IdlePTD ; 
 scalar_t__ KERNEL_PML4_INDEX ; 
 scalar_t__ KPTphys ; 
 int NKPT ; 
 int NPGPTD ; 
 uintptr_t PAGE_SHIFT ; 
 int /*<<< orphan*/  VSTART_PHYSMAP_INIT ; 
 int /*<<< orphan*/  VSTART_SET_CR3 ; 
 int /*<<< orphan*/  doublemap_init () ; 
 int /*<<< orphan*/  fillkpt (scalar_t__,int /*<<< orphan*/ ,uintptr_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  idt64_remap () ; 
 scalar_t__ physfree ; 
 int /*<<< orphan*/  physmap_init () ; 
 int /*<<< orphan*/  postcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cr3_raw (uintptr_t) ; 

__attribute__((used)) static void
Idle_PTs_init(void)
{
	/* Allocate the "idle" kernel page tables: */
	KPTphys  = ALLOCPAGES(NKPT);		/* level 1 */
	IdlePTD  = ALLOCPAGES(NPGPTD);		/* level 2 */
	IdlePDPT = ALLOCPAGES(1);		/* level 3 */
	IdlePML4 = ALLOCPAGES(1);		/* level 4 */

	// Fill the lowest level with everything up to physfree
	fillkpt(KPTphys,
		INTEL_PTE_WRITE, 0, 0, (int)(((uintptr_t)physfree) >> PAGE_SHIFT));

	/* IdlePTD */
	fillkpt(IdlePTD,
		INTEL_PTE_WRITE, (uintptr_t)ID_MAP_VTOP(KPTphys), 0, NKPT);

	// IdlePDPT entries
	fillkpt(IdlePDPT,
		INTEL_PTE_WRITE, (uintptr_t)ID_MAP_VTOP(IdlePTD), 0, NPGPTD);

	// IdlePML4 single entry for kernel space.
	fillkpt(IdlePML4 + KERNEL_PML4_INDEX,
		INTEL_PTE_WRITE, (uintptr_t)ID_MAP_VTOP(IdlePDPT), 0, 1);
	
	postcode(VSTART_PHYSMAP_INIT);

	physmap_init();
	doublemap_init();
	idt64_remap();

	postcode(VSTART_SET_CR3);

	// Switch to the page tables..
	set_cr3_raw((uintptr_t)ID_MAP_VTOP(IdlePML4));

}