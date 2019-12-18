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
typedef  scalar_t__ vm_offset_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  DTEntry ;

/* Variables and functions */
 scalar_t__ DTFindEntry (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DTGetProperty (int /*<<< orphan*/ ,char*,void**,int*) ; 
 scalar_t__ gPicBase ; 
 scalar_t__ gSocPhys ; 
 scalar_t__ gTimerBase ; 
 scalar_t__ kSuccess ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 scalar_t__ ml_io_map (scalar_t__,uintptr_t) ; 
 scalar_t__ pe_arm_get_soc_base_phys () ; 

__attribute__((used)) static uint32_t
pe_arm_map_interrupt_controller(void)
{
	DTEntry		entryP;
	uintptr_t	*reg_prop;
	uint32_t	prop_size;
	vm_offset_t	soc_phys = 0;

	gSocPhys = pe_arm_get_soc_base_phys();

	soc_phys = gSocPhys;
	kprintf("pe_arm_map_interrupt_controller: soc_phys:  0x%lx\n", (unsigned long)soc_phys);
	if (soc_phys == 0)
		return 0;

	if (DTFindEntry("interrupt-controller", "master", &entryP) == kSuccess) {
		kprintf("pe_arm_map_interrupt_controller: found interrupt-controller\n");
		DTGetProperty(entryP, "reg", (void **)&reg_prop, &prop_size);
		gPicBase = ml_io_map(soc_phys + *reg_prop, *(reg_prop + 1));
		kprintf("pe_arm_map_interrupt_controller: gPicBase: 0x%lx\n", (unsigned long)gPicBase);
	}
	if (gPicBase == 0) {
		kprintf("pe_arm_map_interrupt_controller: failed to find the interrupt-controller.\n");
		return 0;
	}

	if (DTFindEntry("device_type", "timer", &entryP) == kSuccess) {
		kprintf("pe_arm_map_interrupt_controller: found timer\n");
		DTGetProperty(entryP, "reg", (void **)&reg_prop, &prop_size);
		gTimerBase = ml_io_map(soc_phys + *reg_prop, *(reg_prop + 1));
		kprintf("pe_arm_map_interrupt_controller: gTimerBase: 0x%lx\n", (unsigned long)gTimerBase);
	}
	if (gTimerBase == 0) {
		kprintf("pe_arm_map_interrupt_controller: failed to find the timer.\n");
		return 0;
	}

	return 1;
}