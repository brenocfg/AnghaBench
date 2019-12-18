#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct linux_binprm {long loader; int taso; struct file* file; TYPE_2__* vma; scalar_t__ buf; } ;
struct file {int dummy; } ;
struct TYPE_6__ {int entry; } ;
struct TYPE_4__ {int f_magic; int f_flags; } ;
struct exec {TYPE_3__ ah; TYPE_1__ fh; } ;
struct TYPE_5__ {int vm_end; } ;

/* Variables and functions */
 int ENOEXEC ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int PTR_ERR (struct file*) ; 
 int /*<<< orphan*/  allow_write_access (struct file*) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 struct file* open_exec (char*) ; 
 int prepare_binprm (struct linux_binprm*) ; 
 int search_binary_handler (struct linux_binprm*,struct pt_regs*) ; 

__attribute__((used)) static int load_binary(struct linux_binprm *bprm, struct pt_regs *regs)
{
	struct exec *eh = (struct exec *)bprm->buf;
	unsigned long loader;
	struct file *file;
	int retval;

	if (eh->fh.f_magic != 0x183 || (eh->fh.f_flags & 0x3000) != 0x3000)
		return -ENOEXEC;

	if (bprm->loader)
		return -ENOEXEC;

	allow_write_access(bprm->file);
	fput(bprm->file);
	bprm->file = NULL;

	loader = bprm->vma->vm_end - sizeof(void *);

	file = open_exec("/sbin/loader");
	retval = PTR_ERR(file);
	if (IS_ERR(file))
		return retval;

	/* Remember if the application is TASO.  */
	bprm->taso = eh->ah.entry < 0x100000000UL;

	bprm->file = file;
	bprm->loader = loader;
	retval = prepare_binprm(bprm);
	if (retval < 0)
		return retval;
	return search_binary_handler(bprm,regs);
}