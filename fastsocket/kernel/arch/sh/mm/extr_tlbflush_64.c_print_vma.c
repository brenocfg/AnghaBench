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
struct vm_area_struct {int /*<<< orphan*/  vm_flags; int /*<<< orphan*/  vm_page_prot; int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_prots (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void print_vma(struct vm_area_struct *vma)
{
	printk("vma start 0x%08lx\n", vma->vm_start);
	printk("vma end   0x%08lx\n", vma->vm_end);

	print_prots(vma->vm_page_prot);
	printk("vm_flags 0x%08lx\n", vma->vm_flags);
}