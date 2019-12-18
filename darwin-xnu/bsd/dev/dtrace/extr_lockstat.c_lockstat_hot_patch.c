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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  void* uint8_t ;
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  instr ;
typedef  scalar_t__ boolean_t ;
struct TYPE_2__ {int lsap_probe; int /*<<< orphan*/ * lsap_patch_point; } ;

/* Variables and functions */
 void* BXLR ; 
 void* NOP ; 
 void* RET ; 
 TYPE_1__* assembly_probes ; 
 int /*<<< orphan*/  ml_nofault_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
void lockstat_hot_patch(boolean_t active, int ls_probe)
{
#pragma unused(active)
	int i;

	/*
	 * Loop through entire table, in case there are
	 * multiple patch points per probe. 
	 */
	for (i = 0; assembly_probes[i].lsap_patch_point; i++) {
		if (ls_probe == assembly_probes[i].lsap_probe)
#if defined(__x86_64__)
		{			
			uint8_t instr;
			instr = (active ? NOP : RET );
			(void) ml_nofault_copy( (vm_offset_t)&instr, *(assembly_probes[i].lsap_patch_point), 
								sizeof(instr));
		}
#elif defined (__arm__)
		{
			uint32_t instr;
			instr = (active ? NOP : BXLR );
			(void) ml_nofault_copy( (vm_offset_t)&instr, *(assembly_probes[i].lsap_patch_point), 
								sizeof(instr));
		}
#elif defined (__arm64__)
		{
			uint32_t instr;
			instr = (active ? NOP : RET );
			(void) ml_nofault_copy( (vm_offset_t)&instr, *(assembly_probes[i].lsap_patch_point), 
								sizeof(instr));
		}
#endif
	} /* for */
}