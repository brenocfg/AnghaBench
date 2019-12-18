#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct som_exec_auxhdr {int /*<<< orphan*/  exec_bsize; int /*<<< orphan*/  exec_dfile; int /*<<< orphan*/  exec_dsize; int /*<<< orphan*/  exec_dmem; int /*<<< orphan*/  exec_tfile; int /*<<< orphan*/  exec_tsize; int /*<<< orphan*/  exec_tmem; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  mm_segment_t ;
struct TYPE_4__ {TYPE_1__* mm; } ;
struct TYPE_3__ {unsigned long start_code; unsigned long end_code; unsigned long start_data; unsigned long end_data; unsigned long start_brk; unsigned long brk; int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int MAP_DENYWRITE ; 
 int MAP_EXECUTABLE ; 
 int MAP_FIXED ; 
 int MAP_PRIVATE ; 
 int PROT_EXEC ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 unsigned long SOM_PAGEALIGN (int /*<<< orphan*/ ) ; 
 unsigned long SOM_PAGESTART (int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int do_mmap (struct file*,unsigned long,unsigned long,int,int,unsigned long) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ds () ; 
 int /*<<< orphan*/  get_fs () ; 
 int /*<<< orphan*/  set_fs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int map_som_binary(struct file *file,
		const struct som_exec_auxhdr *hpuxhdr)
{
	unsigned long code_start, code_size, data_start, data_size;
	unsigned long bss_start, som_brk;
	int retval;
	int prot = PROT_READ | PROT_EXEC;
	int flags = MAP_FIXED|MAP_PRIVATE|MAP_DENYWRITE|MAP_EXECUTABLE;

	mm_segment_t old_fs = get_fs();
	set_fs(get_ds());

	code_start = SOM_PAGESTART(hpuxhdr->exec_tmem);
	code_size = SOM_PAGEALIGN(hpuxhdr->exec_tsize);
	current->mm->start_code = code_start;
	current->mm->end_code = code_start + code_size;
	down_write(&current->mm->mmap_sem);
	retval = do_mmap(file, code_start, code_size, prot,
			flags, SOM_PAGESTART(hpuxhdr->exec_tfile));
	up_write(&current->mm->mmap_sem);
	if (retval < 0 && retval > -1024)
		goto out;

	data_start = SOM_PAGESTART(hpuxhdr->exec_dmem);
	data_size = SOM_PAGEALIGN(hpuxhdr->exec_dsize);
	current->mm->start_data = data_start;
	current->mm->end_data = bss_start = data_start + data_size;
	down_write(&current->mm->mmap_sem);
	retval = do_mmap(file, data_start, data_size,
			prot | PROT_WRITE, flags,
			SOM_PAGESTART(hpuxhdr->exec_dfile));
	up_write(&current->mm->mmap_sem);
	if (retval < 0 && retval > -1024)
		goto out;

	som_brk = bss_start + SOM_PAGEALIGN(hpuxhdr->exec_bsize);
	current->mm->start_brk = current->mm->brk = som_brk;
	down_write(&current->mm->mmap_sem);
	retval = do_mmap(NULL, bss_start, som_brk - bss_start,
			prot | PROT_WRITE, MAP_FIXED | MAP_PRIVATE, 0);
	up_write(&current->mm->mmap_sem);
	if (retval > 0 || retval < -1024)
		retval = 0;
out:
	set_fs(old_fs);
	return retval;
}