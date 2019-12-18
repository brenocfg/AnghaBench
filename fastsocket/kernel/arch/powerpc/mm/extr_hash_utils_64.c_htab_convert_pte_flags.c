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

/* Variables and functions */
 unsigned long HPTE_R_C ; 
 unsigned long HPTE_R_N ; 
 unsigned long _PAGE_DIRTY ; 
 unsigned long _PAGE_EXEC ; 
 unsigned long _PAGE_RW ; 
 unsigned long _PAGE_USER ; 

__attribute__((used)) static unsigned long htab_convert_pte_flags(unsigned long pteflags)
{
	unsigned long rflags = pteflags & 0x1fa;

	/* _PAGE_EXEC -> NOEXEC */
	if ((pteflags & _PAGE_EXEC) == 0)
		rflags |= HPTE_R_N;

	/* PP bits. PAGE_USER is already PP bit 0x2, so we only
	 * need to add in 0x1 if it's a read-only user page
	 */
	if ((pteflags & _PAGE_USER) && !((pteflags & _PAGE_RW) &&
					 (pteflags & _PAGE_DIRTY)))
		rflags |= 1;

	/* Always add C */
	return rflags | HPTE_R_C;
}