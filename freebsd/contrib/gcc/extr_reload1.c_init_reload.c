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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int FIRST_PSEUDO_REGISTER ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 int HARD_FRAME_POINTER_REGNUM ; 
 int /*<<< orphan*/  INIT_REG_SET (int /*<<< orphan*/ *) ; 
 int LAST_VIRTUAL_REGISTER ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  QImode ; 
 int double_reg_address_ok ; 
 int /*<<< orphan*/  gcc_obstack_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PLUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_rtx_SYMBOL_REF (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ indirect_symref_ok ; 
 scalar_t__ memory_address_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obstack_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pseudos_counted ; 
 int /*<<< orphan*/  reload_obstack ; 
 int /*<<< orphan*/  reload_startobj ; 
 scalar_t__ spill_indirect_levels ; 
 int /*<<< orphan*/  spilled_pseudos ; 

void
init_reload (void)
{
  int i;

  /* Often (MEM (REG n)) is still valid even if (REG n) is put on the stack.
     Set spill_indirect_levels to the number of levels such addressing is
     permitted, zero if it is not permitted at all.  */

  rtx tem
    = gen_rtx_MEM (Pmode,
		   gen_rtx_PLUS (Pmode,
				 gen_rtx_REG (Pmode,
					      LAST_VIRTUAL_REGISTER + 1),
				 GEN_INT (4)));
  spill_indirect_levels = 0;

  while (memory_address_p (QImode, tem))
    {
      spill_indirect_levels++;
      tem = gen_rtx_MEM (Pmode, tem);
    }

  /* See if indirect addressing is valid for (MEM (SYMBOL_REF ...)).  */

  tem = gen_rtx_MEM (Pmode, gen_rtx_SYMBOL_REF (Pmode, "foo"));
  indirect_symref_ok = memory_address_p (QImode, tem);

  /* See if reg+reg is a valid (and offsettable) address.  */

  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    {
      tem = gen_rtx_PLUS (Pmode,
			  gen_rtx_REG (Pmode, HARD_FRAME_POINTER_REGNUM),
			  gen_rtx_REG (Pmode, i));

      /* This way, we make sure that reg+reg is an offsettable address.  */
      tem = plus_constant (tem, 4);

      if (memory_address_p (QImode, tem))
	{
	  double_reg_address_ok = 1;
	  break;
	}
    }

  /* Initialize obstack for our rtl allocation.  */
  gcc_obstack_init (&reload_obstack);
  reload_startobj = obstack_alloc (&reload_obstack, 0);

  INIT_REG_SET (&spilled_pseudos);
  INIT_REG_SET (&pseudos_counted);
}