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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int CR0_CD ; 
 int CR0_NW ; 
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 void* FAST_SLAVE_INIT ; 
 void* FULL_SLAVE_INIT ; 
 int /*<<< orphan*/  I386_INIT_SLAVE ; 
 int /*<<< orphan*/  LAPIC_CPU_MAP_DUMP () ; 
 int /*<<< orphan*/  LAPIC_DUMP () ; 
 int /*<<< orphan*/  LAPIC_INIT () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cpu_init () ; 
 int /*<<< orphan*/  cpu_syscall_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_thread_init () ; 
 int /*<<< orphan*/  current_cpu_datap () ; 
 int /*<<< orphan*/  get_cpu_number () ; 
 int /*<<< orphan*/  get_cpu_phys_number () ; 
 int get_cr0 () ; 
 int /*<<< orphan*/  init_fpu () ; 
 int /*<<< orphan*/  lapic_configure () ; 
 int /*<<< orphan*/  mca_cpu_init () ; 
 int /*<<< orphan*/  ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  mtrr_update_cpu () ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pat_init () ; 
 int /*<<< orphan*/  pmap_cpu_init () ; 
 int /*<<< orphan*/  postcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cr0 (int) ; 
 int /*<<< orphan*/  slave_main (void*) ; 
 int /*<<< orphan*/  ucode_update_wake () ; 
 int /*<<< orphan*/  vmx_resume (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_init_slave(boolean_t fast_restart)
{
	void	*init_param	= FULL_SLAVE_INIT;

	postcode(I386_INIT_SLAVE);

	if (!fast_restart) {
		/* Ensure that caching and write-through are enabled */
		set_cr0(get_cr0() & ~(CR0_NW|CR0_CD));
  
		DBG("i386_init_slave() CPU%d: phys (%d) active.\n",
		    get_cpu_number(), get_cpu_phys_number());
  
		assert(!ml_get_interrupts_enabled());
  
		cpu_syscall_init(current_cpu_datap());
		pmap_cpu_init();
  
#if CONFIG_MCA
		mca_cpu_init();
#endif
  
		LAPIC_INIT();
		lapic_configure();
		LAPIC_DUMP();
		LAPIC_CPU_MAP_DUMP();
  
		init_fpu();
  
#if CONFIG_MTRR
		mtrr_update_cpu();
#endif
		/* update CPU microcode */
		ucode_update_wake();
	} else
	    init_param = FAST_SLAVE_INIT;

#if CONFIG_VMX
	/* resume VT operation */
	vmx_resume(FALSE);
#endif

#if CONFIG_MTRR
	if (!fast_restart)
	    pat_init();
#endif

	cpu_thread_init();	/* not strictly necessary */

	cpu_init();	/* Sets cpu_running which starter cpu waits for */
 	slave_main(init_param);
  
 	panic("do_init_slave() returned from slave_main()");
}