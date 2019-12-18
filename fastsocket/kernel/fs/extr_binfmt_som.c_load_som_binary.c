#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct som_hdr {unsigned int aux_header_size; int /*<<< orphan*/  aux_header_location; } ;
struct som_exec_auxhdr {unsigned long exec_entry; } ;
struct pt_regs {int dummy; } ;
struct linux_binprm {scalar_t__ p; int /*<<< orphan*/  file; scalar_t__ buf; } ;
struct TYPE_7__ {scalar_t__ brk; scalar_t__ start_stack; scalar_t__ end_data; scalar_t__ start_code; scalar_t__ end_code; scalar_t__ start_brk; } ;
struct TYPE_5__ {int task_size; int map_base; } ;
struct TYPE_6__ {TYPE_3__* mm; TYPE_1__ thread; int /*<<< orphan*/  personality; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EXSTACK_DEFAULT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PER_HPUX ; 
 int /*<<< orphan*/  PF_FORKNOEXEC ; 
 unsigned int SOM_PAGESIZE ; 
 int /*<<< orphan*/  STACK_TOP ; 
 int check_som_header (struct som_hdr*) ; 
 int /*<<< orphan*/  create_som_tables (struct linux_binprm*) ; 
 TYPE_2__* current ; 
 int flush_old_exec (struct linux_binprm*) ; 
 int /*<<< orphan*/  install_exec_creds (struct linux_binprm*) ; 
 int kernel_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct som_exec_auxhdr*) ; 
 struct som_exec_auxhdr* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_hpux_gateway_page (TYPE_2__*,TYPE_3__*) ; 
 int map_som_binary (int /*<<< orphan*/ ,struct som_exec_auxhdr*) ; 
 int /*<<< orphan*/  printk (char*,unsigned long) ; 
 int /*<<< orphan*/  set_binfmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_arg_pages (struct linux_binprm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_new_exec (struct linux_binprm*) ; 
 int /*<<< orphan*/  som_format ; 
 int /*<<< orphan*/  start_thread_som (struct pt_regs*,unsigned long,scalar_t__) ; 

__attribute__((used)) static int
load_som_binary(struct linux_binprm * bprm, struct pt_regs * regs)
{
	int retval;
	unsigned int size;
	unsigned long som_entry;
	struct som_hdr *som_ex;
	struct som_exec_auxhdr *hpuxhdr;

	/* Get the exec-header */
	som_ex = (struct som_hdr *) bprm->buf;

	retval = check_som_header(som_ex);
	if (retval != 0)
		goto out;

	/* Now read in the auxiliary header information */

	retval = -ENOMEM;
	size = som_ex->aux_header_size;
	if (size > SOM_PAGESIZE)
		goto out;
	hpuxhdr = kmalloc(size, GFP_KERNEL);
	if (!hpuxhdr)
		goto out;

	retval = kernel_read(bprm->file, som_ex->aux_header_location,
			(char *) hpuxhdr, size);
	if (retval != size) {
		if (retval >= 0)
			retval = -EIO;
		goto out_free;
	}

	/* Flush all traces of the currently running executable */
	retval = flush_old_exec(bprm);
	if (retval)
		goto out_free;

	/* OK, This is the point of no return */
	current->flags &= ~PF_FORKNOEXEC;
	current->personality = PER_HPUX;
	setup_new_exec(bprm);

	/* Set the task size for HP-UX processes such that
	 * the gateway page is outside the address space.
	 * This can be fixed later, but for now, this is much
	 * easier.
	 */

	current->thread.task_size = 0xc0000000;

	/* Set map base to allow enough room for hp-ux heap growth */

	current->thread.map_base = 0x80000000;

	retval = map_som_binary(bprm->file, hpuxhdr);
	if (retval < 0)
		goto out_free;

	som_entry = hpuxhdr->exec_entry;
	kfree(hpuxhdr);

	set_binfmt(&som_format);
	install_exec_creds(bprm);
	setup_arg_pages(bprm, STACK_TOP, EXSTACK_DEFAULT);

	create_som_tables(bprm);

	current->mm->start_stack = bprm->p;

#if 0
	printk("(start_brk) %08lx\n" , (unsigned long) current->mm->start_brk);
	printk("(end_code) %08lx\n" , (unsigned long) current->mm->end_code);
	printk("(start_code) %08lx\n" , (unsigned long) current->mm->start_code);
	printk("(end_data) %08lx\n" , (unsigned long) current->mm->end_data);
	printk("(start_stack) %08lx\n" , (unsigned long) current->mm->start_stack);
	printk("(brk) %08lx\n" , (unsigned long) current->mm->brk);
#endif

	map_hpux_gateway_page(current,current->mm);

	start_thread_som(regs, som_entry, bprm->p);
	return 0;

	/* error cleanup */
out_free:
	kfree(hpuxhdr);
out:
	return retval;
}