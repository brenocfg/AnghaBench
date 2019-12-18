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
struct task_struct {int dummy; } ;
struct pages {int dummy; } ;
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;
struct iovec {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SIZE ; 
 int PVM_MAX_KMALLOC_PAGES ; 
 unsigned long min (unsigned long,unsigned long) ; 
 scalar_t__ process_vm_rw_pages (struct task_struct*,struct mm_struct*,struct page**,unsigned long,unsigned long,unsigned long,struct iovec const*,unsigned long,unsigned long*,size_t*,int,unsigned long,scalar_t__*) ; 

__attribute__((used)) static int process_vm_rw_single_vec(unsigned long addr,
				    unsigned long len,
				    const struct iovec *lvec,
				    unsigned long lvec_cnt,
				    unsigned long *lvec_current,
				    size_t *lvec_offset,
				    struct page **process_pages,
				    struct mm_struct *mm,
				    struct task_struct *task,
				    int vm_write,
				    ssize_t *bytes_copied)
{
	unsigned long pa = addr & PAGE_MASK;
	unsigned long start_offset = addr - pa;
	unsigned long nr_pages;
	ssize_t bytes_copied_loop;
	ssize_t rc = 0;
	unsigned long nr_pages_copied = 0;
	unsigned long nr_pages_to_copy;
	unsigned long max_pages_per_loop = PVM_MAX_KMALLOC_PAGES
		/ sizeof(struct pages *);

	*bytes_copied = 0;

	/* Work out address and page range required */
	if (len == 0)
		return 0;
	nr_pages = (addr + len - 1) / PAGE_SIZE - addr / PAGE_SIZE + 1;

	while ((nr_pages_copied < nr_pages) && (*lvec_current < lvec_cnt)) {
		nr_pages_to_copy = min(nr_pages - nr_pages_copied,
				       max_pages_per_loop);

		rc = process_vm_rw_pages(task, mm, process_pages, pa,
					 start_offset, len,
					 lvec, lvec_cnt,
					 lvec_current, lvec_offset,
					 vm_write, nr_pages_to_copy,
					 &bytes_copied_loop);
		start_offset = 0;
		*bytes_copied += bytes_copied_loop;

		if (rc < 0) {
			return rc;
		} else {
			len -= bytes_copied_loop;
			nr_pages_copied += nr_pages_to_copy;
			pa += nr_pages_to_copy * PAGE_SIZE;
		}
	}

	return rc;
}