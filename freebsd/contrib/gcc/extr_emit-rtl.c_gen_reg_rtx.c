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
struct function {TYPE_1__* emit; } ;
typedef  char rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_2__ {int regno_pointer_align_length; unsigned char* regno_pointer_align; unsigned char* x_regno_reg_rtx; } ;

/* Variables and functions */
 scalar_t__ GET_MODE_CLASS (int) ; 
 int GET_MODE_INNER (int) ; 
 scalar_t__ MODE_COMPLEX_FLOAT ; 
 scalar_t__ MODE_COMPLEX_INT ; 
 struct function* cfun ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 char gen_raw_REG (int,int) ; 
 char gen_rtx_CONCAT (int,char,char) ; 
 scalar_t__ generating_concat_p ; 
 char* ggc_realloc (unsigned char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  no_new_pseudos ; 
 int reg_rtx_no ; 
 char* regno_reg_rtx ; 

rtx
gen_reg_rtx (enum machine_mode mode)
{
  struct function *f = cfun;
  rtx val;

  /* Don't let anything called after initial flow analysis create new
     registers.  */
  gcc_assert (!no_new_pseudos);

  if (generating_concat_p
      && (GET_MODE_CLASS (mode) == MODE_COMPLEX_FLOAT
	  || GET_MODE_CLASS (mode) == MODE_COMPLEX_INT))
    {
      /* For complex modes, don't make a single pseudo.
	 Instead, make a CONCAT of two pseudos.
	 This allows noncontiguous allocation of the real and imaginary parts,
	 which makes much better code.  Besides, allocating DCmode
	 pseudos overstrains reload on some machines like the 386.  */
      rtx realpart, imagpart;
      enum machine_mode partmode = GET_MODE_INNER (mode);

      realpart = gen_reg_rtx (partmode);
      imagpart = gen_reg_rtx (partmode);
      return gen_rtx_CONCAT (mode, realpart, imagpart);
    }

  /* Make sure regno_pointer_align, and regno_reg_rtx are large
     enough to have an element for this pseudo reg number.  */

  if (reg_rtx_no == f->emit->regno_pointer_align_length)
    {
      int old_size = f->emit->regno_pointer_align_length;
      char *new;
      rtx *new1;

      new = ggc_realloc (f->emit->regno_pointer_align, old_size * 2);
      memset (new + old_size, 0, old_size);
      f->emit->regno_pointer_align = (unsigned char *) new;

      new1 = ggc_realloc (f->emit->x_regno_reg_rtx,
			  old_size * 2 * sizeof (rtx));
      memset (new1 + old_size, 0, old_size * sizeof (rtx));
      regno_reg_rtx = new1;

      f->emit->regno_pointer_align_length = old_size * 2;
    }

  val = gen_raw_REG (mode, reg_rtx_no);
  regno_reg_rtx[reg_rtx_no++] = val;
  return val;
}