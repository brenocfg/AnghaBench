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
struct dtr_reg {unsigned int base; } ;

/* Variables and functions */
 int /*<<< orphan*/  _dos_ds ; 
 int _farnspeekl (unsigned long) ; 
 int /*<<< orphan*/  _farsetsel (int /*<<< orphan*/ ) ; 
 int pdbr ; 

__attribute__((used)) static unsigned long
get_cr3 (void)
{
  unsigned offset;
  unsigned taskreg;
  unsigned long taskbase, cr3;
  struct dtr_reg gdtr;

  if (pdbr > 0 && pdbr <= 0xfffff)
    return pdbr;

  /* Get the linear address of GDT and the Task Register.  */
  __asm__ __volatile__ ("sgdt   %0" : "=m" (gdtr) : /* no inputs */ );
  __asm__ __volatile__ ("str    %0" : "=m" (taskreg) : /* no inputs */ );

  /* Task Register is a segment selector for the TSS of the current
     task.  Therefore, it can be used as an index into the GDT to get
     at the segment descriptor for the TSS.  To get the index, reset
     the low 3 bits of the selector (which give the CPL).  Add 2 to the
     offset to point to the 3 low bytes of the base address.  */
  offset = gdtr.base + (taskreg & 0xfff8) + 2;


  /* CWSDPMI's task base is always under the 1MB mark.  */
  if (offset > 0xfffff)
    return 0;

  _farsetsel (_dos_ds);
  taskbase  = _farnspeekl (offset) & 0xffffffU;
  taskbase += _farnspeekl (offset + 2) & 0xff000000U;
  if (taskbase > 0xfffff)
    return 0;

  /* CR3 (a.k.a. PDBR, the Page Directory Base Register) is stored at
     offset 1Ch in the TSS.  */
  cr3 = _farnspeekl (taskbase + 0x1c) & ~0xfff;
  if (cr3 > 0xfffff)
    {
#if 0  /* not fullly supported yet */
      /* The Page Directory is in UMBs.  In that case, CWSDPMI puts
	 the first Page Table right below the Page Directory.  Thus,
	 the first Page Table's entry for its own address and the Page
	 Directory entry for that Page Table will hold the same
	 physical address.  The loop below searches the entire UMB
	 range of addresses for such an occurence.  */
      unsigned long addr, pte_idx;

      for (addr = 0xb0000, pte_idx = 0xb0;
	   pte_idx < 0xff;
	   addr += 0x1000, pte_idx++)
	{
	  if (((_farnspeekl (addr + 4 * pte_idx) & 0xfffff027) ==
	       (_farnspeekl (addr + 0x1000) & 0xfffff027))
	      && ((_farnspeekl (addr + 4 * pte_idx + 4) & 0xfffff000) == cr3))
	    {
	      cr3 = addr + 0x1000;
	      break;
	    }
	}
#endif

      if (cr3 > 0xfffff)
	cr3 = 0;
    }

  return cr3;
}