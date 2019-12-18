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
struct vm_area_struct {struct mm_struct* vm_mm; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int EASI_BASE ; 
 int EASI_SIZE ; 
 int EASI_START ; 
 scalar_t__ IO_BASE ; 
 int IO_SIZE ; 
 int IO_START ; 
 int PGDIR_SIZE ; 
 int /*<<< orphan*/  flush_tlb_range (struct vm_area_struct*,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,int) ; 

__attribute__((used)) static void ecard_init_pgtables(struct mm_struct *mm)
{
	struct vm_area_struct vma;

	/* We want to set up the page tables for the following mapping:
	 *  Virtual	Physical
	 *  0x03000000	0x03000000
	 *  0x03010000	unmapped
	 *  0x03210000	0x03210000
	 *  0x03400000	unmapped
	 *  0x08000000	0x08000000
	 *  0x10000000	unmapped
	 *
	 * FIXME: we don't follow this 100% yet.
	 */
	pgd_t *src_pgd, *dst_pgd;

	src_pgd = pgd_offset(mm, (unsigned long)IO_BASE);
	dst_pgd = pgd_offset(mm, IO_START);

	memcpy(dst_pgd, src_pgd, sizeof(pgd_t) * (IO_SIZE / PGDIR_SIZE));

	src_pgd = pgd_offset(mm, EASI_BASE);
	dst_pgd = pgd_offset(mm, EASI_START);

	memcpy(dst_pgd, src_pgd, sizeof(pgd_t) * (EASI_SIZE / PGDIR_SIZE));

	vma.vm_mm = mm;

	flush_tlb_range(&vma, IO_START, IO_START + IO_SIZE);
	flush_tlb_range(&vma, EASI_START, EASI_START + EASI_SIZE);
}