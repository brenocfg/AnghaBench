#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  int uint32_t ;
struct TYPE_10__ {int kaddr; int ksize; int /*<<< orphan*/  PhysicalMemorySize; int /*<<< orphan*/  MemoryMapSize; int /*<<< orphan*/  MemoryMap; int /*<<< orphan*/  CommandLine; int /*<<< orphan*/  Version; int /*<<< orphan*/  Revision; } ;
typedef  TYPE_1__ boot_args ;
typedef  int boolean_t ;
struct TYPE_11__ {int /*<<< orphan*/  cpu_int_stack_top; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ID ; 
 scalar_t__ ID_MAP_VTOP (void*) ; 
 void* IdlePML4 ; 
 int /*<<< orphan*/  Idle_PTs_init () ; 
 size_t LAPIC_ID_MASK ; 
 size_t LAPIC_ID_SHIFT ; 
 size_t LAPIC_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSR_IA32_GS_BASE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PE_INIT_PLATFORM_D ; 
 int /*<<< orphan*/  PE_init_platform (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VSTART_CPU_DESC_INIT ; 
 int /*<<< orphan*/  VSTART_CPU_MODE_INIT ; 
 int /*<<< orphan*/  VSTART_ENTRY ; 
 int /*<<< orphan*/  VSTART_EXIT ; 
 int /*<<< orphan*/  VSTART_IDLE_PTS_INIT ; 
 int /*<<< orphan*/  VSTART_IDT_INIT ; 
 int /*<<< orphan*/  cpu_data_alloc (int /*<<< orphan*/ ) ; 
 TYPE_5__* cpu_datap (int) ; 
 int /*<<< orphan*/  cpu_desc_init (TYPE_5__*) ; 
 int /*<<< orphan*/  cpu_desc_load (TYPE_5__*) ; 
 int /*<<< orphan*/  cpu_syscall_init (TYPE_5__*) ; 
 scalar_t__ first_avail ; 
 scalar_t__ i386_init ; 
 scalar_t__ i386_init_slave ; 
 int /*<<< orphan*/  kasan_init () ; 
 int /*<<< orphan*/  kasan_notify_stolen (uintptr_t) ; 
 int /*<<< orphan*/  kasan_reserve_memory (TYPE_1__*) ; 
 TYPE_1__* kernelBootArgs ; 
 int* lapic_to_cpu ; 
 scalar_t__ ml_static_ptovirt (scalar_t__) ; 
 int /*<<< orphan*/  mt_early_init () ; 
 int /*<<< orphan*/  pal_serial_init () ; 
 void* physfree ; 
 int /*<<< orphan*/  postcode (int /*<<< orphan*/ ) ; 
 TYPE_1__* rdmsr64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cr3_raw (uintptr_t) ; 
 int /*<<< orphan*/  vstart_idt_init () ; 
 int /*<<< orphan*/  x86_init_wrapper (uintptr_t,int /*<<< orphan*/ ) ; 

__attribute__((noreturn))
void
vstart(vm_offset_t boot_args_start)
{
	boolean_t	is_boot_cpu = !(boot_args_start == 0);
	int		cpu = 0;
	uint32_t	lphysfree;

	postcode(VSTART_ENTRY);

	if (is_boot_cpu) {
		/*
		 * Set-up temporary trap handlers during page-table set-up.
		 */
		vstart_idt_init();
		postcode(VSTART_IDT_INIT);

		/*
		 * Get startup parameters.
		 */
		kernelBootArgs = (boot_args *)boot_args_start;
		lphysfree = kernelBootArgs->kaddr + kernelBootArgs->ksize;
		physfree = (void *)(uintptr_t)((lphysfree + PAGE_SIZE - 1) &~ (PAGE_SIZE - 1));

#if DEVELOPMENT || DEBUG
		pal_serial_init();
#endif
		DBG("revision      0x%x\n", kernelBootArgs->Revision);
		DBG("version       0x%x\n", kernelBootArgs->Version);
		DBG("command line  %s\n", kernelBootArgs->CommandLine);
		DBG("memory map    0x%x\n", kernelBootArgs->MemoryMap);
		DBG("memory map sz 0x%x\n", kernelBootArgs->MemoryMapSize);
		DBG("kaddr         0x%x\n", kernelBootArgs->kaddr);
		DBG("ksize         0x%x\n", kernelBootArgs->ksize);
		DBG("physfree      %p\n", physfree);
		DBG("bootargs: %p, &ksize: %p &kaddr: %p\n",
			kernelBootArgs, 
			&kernelBootArgs->ksize,
			&kernelBootArgs->kaddr);
		DBG("SMBIOS mem sz 0x%llx\n", kernelBootArgs->PhysicalMemorySize);

		/*
		 * Setup boot args given the physical start address.
		 * Note: PE_init_platform needs to be called before Idle_PTs_init
		 * because access to the DeviceTree is required to read the
		 * random seed before generating a random physical map slide.
		 */
		kernelBootArgs = (boot_args *)
		    ml_static_ptovirt(boot_args_start);
		DBG("i386_init(0x%lx) kernelBootArgs=%p\n",
		    (unsigned long)boot_args_start, kernelBootArgs);

#if KASAN
		kasan_reserve_memory(kernelBootArgs);
#endif

		PE_init_platform(FALSE, kernelBootArgs);
		postcode(PE_INIT_PLATFORM_D);

		Idle_PTs_init();
		postcode(VSTART_IDLE_PTS_INIT);

#if KASAN
		/* Init kasan and map whatever was stolen from physfree */
		kasan_init();
		kasan_notify_stolen((uintptr_t)ml_static_ptovirt((vm_offset_t)physfree));
#endif

#if MONOTONIC
		mt_early_init();
#endif /* MONOTONIC */

		first_avail = (vm_offset_t)ID_MAP_VTOP(physfree);

		cpu_data_alloc(TRUE);

		cpu_desc_init(cpu_datap(0));
		postcode(VSTART_CPU_DESC_INIT);
		cpu_desc_load(cpu_datap(0));

		postcode(VSTART_CPU_MODE_INIT);
		cpu_syscall_init(cpu_datap(0)); /* cpu_syscall_init() will be
						 * invoked on the APs
						 * via i386_init_slave()
						 */
	} else {
		/* Switch to kernel's page tables (from the Boot PTs) */
		set_cr3_raw((uintptr_t)ID_MAP_VTOP(IdlePML4));
		/* Find our logical cpu number */
		cpu = lapic_to_cpu[(LAPIC_READ(ID)>>LAPIC_ID_SHIFT) & LAPIC_ID_MASK];
		DBG("CPU: %d, GSBASE initial value: 0x%llx\n", cpu, rdmsr64(MSR_IA32_GS_BASE));
		cpu_desc_load(cpu_datap(cpu));
	}

	postcode(VSTART_EXIT);
	x86_init_wrapper(is_boot_cpu ? (uintptr_t) i386_init
				     : (uintptr_t) i386_init_slave,
			 cpu_datap(cpu)->cpu_int_stack_top);
}