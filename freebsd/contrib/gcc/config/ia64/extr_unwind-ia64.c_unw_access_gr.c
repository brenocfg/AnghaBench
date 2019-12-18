#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int off; int type; } ;
struct unw_ireg {unsigned long* loc; TYPE_1__ nat; } ;
struct _Unwind_Context {unsigned long regstk_top; unsigned long rnat; scalar_t__ bsp; struct unw_ireg* ireg; } ;

/* Variables and functions */
#define  UNW_NAT_MEMSTK 131 
#define  UNW_NAT_NONE 130 
#define  UNW_NAT_REGSTK 129 
#define  UNW_NAT_VAL 128 
 int /*<<< orphan*/  abort () ; 
 unsigned long* ia64_rse_rnat_addr (unsigned long*) ; 
 unsigned long* ia64_rse_skip_regs (unsigned long*,int) ; 
 unsigned long ia64_rse_slot_num (unsigned long*) ; 

__attribute__((used)) static void
unw_access_gr (struct _Unwind_Context *info, int regnum,
	       unsigned long *val, char *nat, int write)
{
  unsigned long *addr, *nat_addr = 0, nat_mask = 0, dummy_nat;
  struct unw_ireg *ireg;

  if ((unsigned) regnum - 1 >= 127)
    abort ();

  if (regnum < 1)
    {
      nat_addr = addr = &dummy_nat;
      dummy_nat = 0;
    }
  else if (regnum < 32)
    {
      /* Access a non-stacked register.  */
      ireg = &info->ireg[regnum - 2];
      addr = ireg->loc;
      if (addr)
	{
	  nat_addr = addr + ireg->nat.off;
	  switch (ireg->nat.type)
	    {
	    case UNW_NAT_VAL:
	      /* Simulate getf.sig/setf.sig.  */
	      if (write)
		{
		  if (*nat)
		    {
		      /* Write NaTVal and be done with it.  */
		      addr[0] = 0;
		      addr[1] = 0x1fffe;
		      return;
		    }
		  addr[1] = 0x1003e;
		}
	      else if (addr[0] == 0 && addr[1] == 0x1ffe)
		{
		  /* Return NaT and be done with it.  */
		  *val = 0;
		  *nat = 1;
		  return;
		}
	      /* FALLTHRU */

	    case UNW_NAT_NONE:
	      dummy_nat = 0;
	      nat_addr = &dummy_nat;
	      break;

	    case UNW_NAT_MEMSTK:
	      nat_mask = 1UL << ((long) addr & 0x1f8)/8;
	      break;

	    case UNW_NAT_REGSTK:
	      if ((unsigned long) addr >= info->regstk_top)
		nat_addr = &info->rnat;
	      else
		nat_addr = ia64_rse_rnat_addr (addr);
	      nat_mask = 1UL << ia64_rse_slot_num (addr);
	      break;
	    }
	}
    }
  else
    {
      /* Access a stacked register.  */
      addr = ia64_rse_skip_regs ((unsigned long *) info->bsp, regnum - 32);
      if ((unsigned long) addr >= info->regstk_top)
	nat_addr = &info->rnat;
      else
	nat_addr = ia64_rse_rnat_addr (addr);
      nat_mask = 1UL << ia64_rse_slot_num (addr);
    }

  if (write)
    {
      *addr = *val;
      if (*nat)
	*nat_addr |= nat_mask;
      else
	*nat_addr &= ~nat_mask;
    }
  else
    {
      *val = *addr;
      *nat = (*nat_addr & nat_mask) != 0;
    }
}