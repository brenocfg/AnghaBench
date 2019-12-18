#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct kimage {int /*<<< orphan*/  control_code_page; int /*<<< orphan*/  start; } ;
struct TYPE_9__ {int /*<<< orphan*/  task; } ;
struct TYPE_6__ {scalar_t__ flags; int /*<<< orphan*/  task; } ;
struct TYPE_8__ {TYPE_1__ thread_info; } ;
struct TYPE_7__ {int /*<<< orphan*/  hpte_clear_all; } ;

/* Variables and functions */
 int crashing_cpu ; 
 TYPE_5__* current_thread_info () ; 
 int /*<<< orphan*/  kexec_prepare_cpus () ; 
 int /*<<< orphan*/  kexec_sequence (TYPE_3__*,int /*<<< orphan*/ ,struct kimage*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ kexec_stack ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ ) ; 
 TYPE_2__ ppc_md ; 

void default_machine_kexec(struct kimage *image)
{
	/* prepare control code if any */

	/*
        * If the kexec boot is the normal one, need to shutdown other cpus
        * into our wait loop and quiesce interrupts.
        * Otherwise, in the case of crashed mode (crashing_cpu >= 0),
        * stopping other CPUs and collecting their pt_regs is done before
        * using debugger IPI.
        */

	if (crashing_cpu == -1)
		kexec_prepare_cpus();

	/* switch to a staticly allocated stack.  Based on irq stack code.
	 * XXX: the task struct will likely be invalid once we do the copy!
	 */
	kexec_stack.thread_info.task = current_thread_info()->task;
	kexec_stack.thread_info.flags = 0;

	/* Some things are best done in assembly.  Finding globals with
	 * a toc is easier in C, so pass in what we can.
	 */
	kexec_sequence(&kexec_stack, image->start, image,
			page_address(image->control_code_page),
			ppc_md.hpte_clear_all);
	/* NOTREACHED */
}