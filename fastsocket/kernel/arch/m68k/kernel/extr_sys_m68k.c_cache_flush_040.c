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
#define  FLUSH_CACHE_BOTH 133 
#define  FLUSH_CACHE_DATA 132 
#define  FLUSH_CACHE_INSN 131 
#define  FLUSH_SCOPE_ALL 130 
#define  FLUSH_SCOPE_LINE 129 
#define  FLUSH_SCOPE_PAGE 128 
 int PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 unsigned long virt_to_phys_040 (unsigned long) ; 

__attribute__((used)) static inline int
cache_flush_040 (unsigned long addr, int scope, int cache, unsigned long len)
{
  unsigned long paddr, i;

  switch (scope)
    {
    case FLUSH_SCOPE_ALL:
      switch (cache)
	{
	case FLUSH_CACHE_DATA:
	  /* This nop is needed for some broken versions of the 68040.  */
	  __asm__ __volatile__ ("nop\n\t"
				".chip 68040\n\t"
				"cpusha %dc\n\t"
				".chip 68k");
	  break;
	case FLUSH_CACHE_INSN:
	  __asm__ __volatile__ ("nop\n\t"
				".chip 68040\n\t"
				"cpusha %ic\n\t"
				".chip 68k");
	  break;
	default:
	case FLUSH_CACHE_BOTH:
	  __asm__ __volatile__ ("nop\n\t"
				".chip 68040\n\t"
				"cpusha %bc\n\t"
				".chip 68k");
	  break;
	}
      break;

    case FLUSH_SCOPE_LINE:
      /* Find the physical address of the first mapped page in the
	 address range.  */
      if ((paddr = virt_to_phys_040(addr))) {
        paddr += addr & ~(PAGE_MASK | 15);
        len = (len + (addr & 15) + 15) >> 4;
      } else {
	unsigned long tmp = PAGE_SIZE - (addr & ~PAGE_MASK);

	if (len <= tmp)
	  return 0;
	addr += tmp;
	len -= tmp;
	tmp = PAGE_SIZE;
	for (;;)
	  {
	    if ((paddr = virt_to_phys_040(addr)))
	      break;
	    if (len <= tmp)
	      return 0;
	    addr += tmp;
	    len -= tmp;
	  }
	len = (len + 15) >> 4;
      }
      i = (PAGE_SIZE - (paddr & ~PAGE_MASK)) >> 4;
      while (len--)
	{
	  switch (cache)
	    {
	    case FLUSH_CACHE_DATA:
	      __asm__ __volatile__ ("nop\n\t"
				    ".chip 68040\n\t"
				    "cpushl %%dc,(%0)\n\t"
				    ".chip 68k"
				    : : "a" (paddr));
	      break;
	    case FLUSH_CACHE_INSN:
	      __asm__ __volatile__ ("nop\n\t"
				    ".chip 68040\n\t"
				    "cpushl %%ic,(%0)\n\t"
				    ".chip 68k"
				    : : "a" (paddr));
	      break;
	    default:
	    case FLUSH_CACHE_BOTH:
	      __asm__ __volatile__ ("nop\n\t"
				    ".chip 68040\n\t"
				    "cpushl %%bc,(%0)\n\t"
				    ".chip 68k"
				    : : "a" (paddr));
	      break;
	    }
	  if (!--i && len)
	    {
	      /*
	       * No need to page align here since it is done by
	       * virt_to_phys_040().
	       */
	      addr += PAGE_SIZE;
	      i = PAGE_SIZE / 16;
	      /* Recompute physical address when crossing a page
	         boundary. */
	      for (;;)
		{
		  if ((paddr = virt_to_phys_040(addr)))
		    break;
		  if (len <= i)
		    return 0;
		  len -= i;
		  addr += PAGE_SIZE;
		}
	    }
	  else
	    paddr += 16;
	}
      break;

    default:
    case FLUSH_SCOPE_PAGE:
      len += (addr & ~PAGE_MASK) + (PAGE_SIZE - 1);
      for (len >>= PAGE_SHIFT; len--; addr += PAGE_SIZE)
	{
	  if (!(paddr = virt_to_phys_040(addr)))
	    continue;
	  switch (cache)
	    {
	    case FLUSH_CACHE_DATA:
	      __asm__ __volatile__ ("nop\n\t"
				    ".chip 68040\n\t"
				    "cpushp %%dc,(%0)\n\t"
				    ".chip 68k"
				    : : "a" (paddr));
	      break;
	    case FLUSH_CACHE_INSN:
	      __asm__ __volatile__ ("nop\n\t"
				    ".chip 68040\n\t"
				    "cpushp %%ic,(%0)\n\t"
				    ".chip 68k"
				    : : "a" (paddr));
	      break;
	    default:
	    case FLUSH_CACHE_BOTH:
	      __asm__ __volatile__ ("nop\n\t"
				    ".chip 68040\n\t"
				    "cpushp %%bc,(%0)\n\t"
				    ".chip 68k"
				    : : "a" (paddr));
	      break;
	    }
	}
      break;
    }
  return 0;
}