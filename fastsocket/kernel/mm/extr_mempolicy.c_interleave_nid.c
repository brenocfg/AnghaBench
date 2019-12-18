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
struct vm_area_struct {int vm_pgoff; unsigned long vm_start; } ;
struct mempolicy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PAGE_SHIFT ; 
 int interleave_nodes (struct mempolicy*) ; 
 int offset_il_node (struct mempolicy*,struct vm_area_struct*,unsigned long) ; 

__attribute__((used)) static inline unsigned interleave_nid(struct mempolicy *pol,
		 struct vm_area_struct *vma, unsigned long addr, int shift)
{
	if (vma) {
		unsigned long off;

		/*
		 * for small pages, there is no difference between
		 * shift and PAGE_SHIFT, so the bit-shift is safe.
		 * for huge pages, since vm_pgoff is in units of small
		 * pages, we need to shift off the always 0 bits to get
		 * a useful offset.
		 */
		BUG_ON(shift < PAGE_SHIFT);
		off = vma->vm_pgoff >> (shift - PAGE_SHIFT);
		off += (addr - vma->vm_start) >> shift;
		return offset_il_node(pol, vma, off);
	} else
		return interleave_nodes(pol);
}