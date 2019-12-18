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
typedef  unsigned long phys_addr_t ;
struct TYPE_4__ {int MAS0; int MAS1; unsigned long MAS2; unsigned long MAS3; } ;
struct TYPE_3__ {unsigned long start; unsigned long limit; unsigned long phys; } ;

/* Variables and functions */
 int MAS0_ESEL (int) ; 
 int MAS0_NV (int) ; 
 int MAS0_TLBSEL (int) ; 
 int MAS1_IPROT ; 
 int MAS1_TID (unsigned int) ; 
 int MAS1_TSIZE (unsigned int) ; 
 int MAS1_VALID ; 
 unsigned long MAS2_E ; 
 unsigned long MAS2_G ; 
 unsigned long MAS2_I ; 
 unsigned long MAS2_M ; 
 unsigned long MAS2_W ; 
 unsigned long MAS3_SR ; 
 unsigned long MAS3_SW ; 
 unsigned long MAS3_SX ; 
 int MAS3_UR ; 
 int MAS3_UW ; 
 int MAS3_UX ; 
 unsigned long PAGE_MASK ; 
 TYPE_2__* TLBCAM ; 
 int _PAGE_COHERENT ; 
 int _PAGE_ENDIAN ; 
 int _PAGE_GUARDED ; 
 int _PAGE_NO_CACHE ; 
 int _PAGE_RW ; 
 int _PAGE_USER ; 
 int _PAGE_WRITETHRU ; 
 int /*<<< orphan*/  loadcam_entry (int) ; 
 TYPE_1__* tlbcam_addrs ; 

void settlbcam(int index, unsigned long virt, phys_addr_t phys,
		unsigned int size, int flags, unsigned int pid)
{
	unsigned int tsize, lz;

	asm ("cntlzw %0,%1" : "=r" (lz) : "r" (size));
	tsize = 21 - lz;

#ifdef CONFIG_SMP
	if ((flags & _PAGE_NO_CACHE) == 0)
		flags |= _PAGE_COHERENT;
#endif

	TLBCAM[index].MAS0 = MAS0_TLBSEL(1) | MAS0_ESEL(index) | MAS0_NV(index+1);
	TLBCAM[index].MAS1 = MAS1_VALID | MAS1_IPROT | MAS1_TSIZE(tsize) | MAS1_TID(pid);
	TLBCAM[index].MAS2 = virt & PAGE_MASK;

	TLBCAM[index].MAS2 |= (flags & _PAGE_WRITETHRU) ? MAS2_W : 0;
	TLBCAM[index].MAS2 |= (flags & _PAGE_NO_CACHE) ? MAS2_I : 0;
	TLBCAM[index].MAS2 |= (flags & _PAGE_COHERENT) ? MAS2_M : 0;
	TLBCAM[index].MAS2 |= (flags & _PAGE_GUARDED) ? MAS2_G : 0;
	TLBCAM[index].MAS2 |= (flags & _PAGE_ENDIAN) ? MAS2_E : 0;

	TLBCAM[index].MAS3 = (phys & PAGE_MASK) | MAS3_SX | MAS3_SR;
	TLBCAM[index].MAS3 |= ((flags & _PAGE_RW) ? MAS3_SW : 0);

	if (flags & _PAGE_USER) {
	   TLBCAM[index].MAS3 |= MAS3_UX | MAS3_UR;
	   TLBCAM[index].MAS3 |= ((flags & _PAGE_RW) ? MAS3_UW : 0);
	}

	tlbcam_addrs[index].start = virt;
	tlbcam_addrs[index].limit = virt + size - 1;
	tlbcam_addrs[index].phys = phys;

	loadcam_entry(index);
}