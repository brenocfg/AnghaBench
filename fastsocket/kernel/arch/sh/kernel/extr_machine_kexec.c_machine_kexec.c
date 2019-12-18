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
struct kimage {unsigned long head; unsigned long start; scalar_t__ preserve_context; int /*<<< orphan*/  control_code_page; } ;
typedef  int /*<<< orphan*/  (* relocate_new_kernel_t ) (unsigned long,unsigned long,unsigned long) ;

/* Variables and functions */
 unsigned long IND_DESTINATION ; 
 unsigned long IND_DONE ; 
 unsigned long IND_INDIRECTION ; 
 unsigned long IND_SOURCE ; 
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  __ftrace_enabled_restore (int) ; 
 int __ftrace_enabled_save () ; 
 int /*<<< orphan*/  flush_cache_all () ; 
 int /*<<< orphan*/  kexec_info (struct kimage*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (int /*<<< orphan*/ ) ; 
 unsigned long* phys_to_virt (unsigned long) ; 
 int /*<<< orphan*/  relocate_new_kernel ; 
 int /*<<< orphan*/  relocate_new_kernel_size ; 
 int /*<<< orphan*/  restore_processor_state () ; 
 int /*<<< orphan*/  save_processor_state () ; 
 int /*<<< orphan*/  stub1 (unsigned long,unsigned long,unsigned long) ; 
 unsigned long virt_to_phys (unsigned long) ; 

void machine_kexec(struct kimage *image)
{
	unsigned long page_list;
	unsigned long reboot_code_buffer;
	relocate_new_kernel_t rnk;
	unsigned long entry;
	unsigned long *ptr;
	int save_ftrace_enabled;

	/*
	 * Nicked from the mips version of machine_kexec():
	 * The generic kexec code builds a page list with physical
	 * addresses. Use phys_to_virt() to convert them to virtual.
	 */
	for (ptr = &image->head; (entry = *ptr) && !(entry & IND_DONE);
	     ptr = (entry & IND_INDIRECTION) ?
	       phys_to_virt(entry & PAGE_MASK) : ptr + 1) {
		if (*ptr & IND_SOURCE || *ptr & IND_INDIRECTION ||
		    *ptr & IND_DESTINATION)
			*ptr = (unsigned long) phys_to_virt(*ptr);
	}

#ifdef CONFIG_KEXEC_JUMP
	if (image->preserve_context)
		save_processor_state();
#endif

	save_ftrace_enabled = __ftrace_enabled_save();

	/* Interrupts aren't acceptable while we reboot */
	local_irq_disable();

	page_list = image->head;

	/* we need both effective and real address here */
	reboot_code_buffer =
			(unsigned long)page_address(image->control_code_page);

	/* copy our kernel relocation code to the control code page */
	memcpy((void *)reboot_code_buffer, relocate_new_kernel,
						relocate_new_kernel_size);

	kexec_info(image);
	flush_cache_all();

#if defined(CONFIG_SH_STANDARD_BIOS)
	asm volatile("ldc %0, vbr" :
		     : "r" (((unsigned long) gdb_vbr_vector) - 0x100)
		     : "memory");
#endif

	/* now call it */
	rnk = (relocate_new_kernel_t) reboot_code_buffer;
	(*rnk)(page_list, reboot_code_buffer,
	       (unsigned long)phys_to_virt(image->start));

#ifdef CONFIG_KEXEC_JUMP
	asm volatile("ldc %0, vbr" : : "r" (&vbr_base) : "memory");

	if (image->preserve_context)
		restore_processor_state();

	/* Convert page list back to physical addresses, what a mess. */
	for (ptr = &image->head; (entry = *ptr) && !(entry & IND_DONE);
	     ptr = (*ptr & IND_INDIRECTION) ?
	       phys_to_virt(*ptr & PAGE_MASK) : ptr + 1) {
		if (*ptr & IND_SOURCE || *ptr & IND_INDIRECTION ||
		    *ptr & IND_DESTINATION)
			*ptr = virt_to_phys(*ptr);
	}
#endif

	__ftrace_enabled_restore(save_ftrace_enabled);
}