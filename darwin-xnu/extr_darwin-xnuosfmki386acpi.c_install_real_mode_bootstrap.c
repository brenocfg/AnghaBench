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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  addr64_t ;

/* Variables and functions */
 scalar_t__ PROT_MODE_START ; 
 scalar_t__ REAL_MODE_BOOTSTRAP_OFFSET ; 
 int /*<<< orphan*/  bcopy_phys (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ kvtophys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ml_phys_write_word (scalar_t__,unsigned int) ; 
 scalar_t__ real_mode_bootstrap_base ; 
 scalar_t__ real_mode_bootstrap_end ; 

void
install_real_mode_bootstrap(void *prot_entry)
{
	/*
	 * Copy the boot entry code to the real-mode vector area REAL_MODE_BOOTSTRAP_OFFSET.
	 * This is in page 1 which has been reserved for this purpose by
	 * machine_startup() from the boot processor.
	 * The slave boot code is responsible for switching to protected
	 * mode and then jumping to the common startup, _start().
	 */
	bcopy_phys(kvtophys((vm_offset_t) real_mode_bootstrap_base),
		   (addr64_t) REAL_MODE_BOOTSTRAP_OFFSET,
		   real_mode_bootstrap_end-real_mode_bootstrap_base);

	/*
	 * Set the location at the base of the stack to point to the
	 * common startup entry.
	 */
	ml_phys_write_word(
		PROT_MODE_START+REAL_MODE_BOOTSTRAP_OFFSET,
		(unsigned int)kvtophys((vm_offset_t)prot_entry));
	
	/* Flush caches */
	__asm__("wbinvd");
}