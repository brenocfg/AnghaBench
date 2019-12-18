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
struct el_subpacket {int dummy; } ;

/* Variables and functions */
 char* KERN_CRIT ; 
 unsigned long SCB_Q_PROCERR ; 
 int /*<<< orphan*/  draina () ; 
 int /*<<< orphan*/  el_process_subpacket (struct el_subpacket*) ; 
 char* err_print_prefix ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  printk (char*,char*,char*,unsigned int,int) ; 
 scalar_t__ smp_processor_id () ; 
 int /*<<< orphan*/  wrmces (int) ; 

void
ev7_machine_check(unsigned long vector, unsigned long la_ptr)
{
	struct el_subpacket *el_ptr = (struct el_subpacket *)la_ptr;
	char *saved_err_prefix = err_print_prefix;

	/*
	 * Sync the processor
	 */
	mb();
	draina();

	err_print_prefix = KERN_CRIT;
	printk("%s*CPU %s Error (Vector 0x%x) reported on CPU %d\n",
	       err_print_prefix, 
	       (vector == SCB_Q_PROCERR) ? "Correctable" : "Uncorrectable",
	       (unsigned int)vector, (int)smp_processor_id());
	el_process_subpacket(el_ptr);
	err_print_prefix = saved_err_prefix;

	/* 
	 * Release the logout frame 
	 */
	wrmces(0x7);
	mb();
}