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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long PUD_MASK ; 
 unsigned long PUD_SIZE ; 
 int /*<<< orphan*/  io_remap_pmd_range (struct mm_struct*,int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pmd_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline int io_remap_pud_range(struct mm_struct *mm, pud_t * pud, unsigned long address, unsigned long size,
	unsigned long offset, pgprot_t prot, int space)
{
	unsigned long end;

	address &= ~PUD_MASK;
	end = address + size;
	if (end > PUD_SIZE)
		end = PUD_SIZE;
	offset -= address;
	do {
		pmd_t *pmd = pmd_alloc(mm, pud, address);
		if (!pud)
			return -ENOMEM;
		io_remap_pmd_range(mm, pmd, address, end - address, address + offset, prot, space);
		address = (address + PUD_SIZE) & PUD_MASK;
		pud++;
	} while (address < end);
	return 0;
}