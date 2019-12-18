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
typedef  enum reg_class { ____Placeholder_reg_class } reg_class ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int REGNO ;

/* Variables and functions */
 int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ HARD_REGNO_MODE_OK (int,int) ; 
 scalar_t__ MAX_MACHINE_MODE ; 
 int N_REG_CLASSES ; 
 int /*<<< orphan*/  POST_INC ; 
 int /*<<< orphan*/  PUT_MODE (int,int) ; 
 int /*<<< orphan*/  SCRATCH ; 
 scalar_t__ TEST_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 int VOIDmode ; 
 int /*<<< orphan*/  auto_inc_dec_reg_p (int,int) ; 
 int base_reg_class (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* forbidden_inc_dec_class ; 
 int /*<<< orphan*/  gen_rtx_raw_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * reg_class_contents ; 
 scalar_t__ secondary_reload_class (int,int,int,int) ; 

__attribute__((used)) static void
init_reg_autoinc (void)
{
#ifdef FORBIDDEN_INC_DEC_CLASSES
  int i;

  for (i = 0; i < N_REG_CLASSES; i++)
    {
      rtx r = gen_rtx_raw_REG (VOIDmode, 0);
      enum machine_mode m;
      int j;

      for (j = 0; j < FIRST_PSEUDO_REGISTER; j++)
	if (TEST_HARD_REG_BIT (reg_class_contents[i], j))
	  {
	    REGNO (r) = j;

	    for (m = VOIDmode; (int) m < (int) MAX_MACHINE_MODE;
		 m = (enum machine_mode) ((int) m + 1))
	      if (HARD_REGNO_MODE_OK (j, m))
		{
		  /* ??? There are two assumptions here; that the base class does not
		     depend on the exact outer code (POST_INC vs. PRE_INC etc.), and
		     that it does not depend on the machine mode of the memory
		     reference.  */
		  enum reg_class base_class
		    = base_reg_class (VOIDmode, POST_INC, SCRATCH);

		  PUT_MODE (r, m);

		  /* If a register is not directly suitable for an
		     auto-increment or decrement addressing mode and
		     requires secondary reloads, disallow its class from
		     being used in such addresses.  */

		  if ((secondary_reload_class (1, base_class, m, r)
		       || secondary_reload_class (1, base_class, m, r))
		      && ! auto_inc_dec_reg_p (r, m))
		    forbidden_inc_dec_class[i] = 1;
		}
	  }
    }
#endif /* FORBIDDEN_INC_DEC_CLASSES */
}