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
typedef  scalar_t__ rtx ;
typedef  enum reload_type { ____Placeholder_reload_type } reload_type ;
typedef  enum reg_class { ____Placeholder_reg_class } reg_class ;
struct TYPE_2__ {int class; scalar_t__ reg_rtx; scalar_t__ in; scalar_t__ out; int /*<<< orphan*/  opnum; int /*<<< orphan*/  when_needed; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_CODE (scalar_t__) ; 
 scalar_t__ GET_RTX_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ MATCHES (scalar_t__,scalar_t__) ; 
 scalar_t__ MERGABLE_RELOADS (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ RTX_AUTOINC ; 
 scalar_t__ SMALL_REGISTER_CLASSES ; 
 scalar_t__ SMALL_REGISTER_CLASS_P (int) ; 
 scalar_t__ TEST_HARD_REG_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ earlyclobber_operand_p (scalar_t__) ; 
 int n_reloads ; 
 int /*<<< orphan*/ * reg_class_contents ; 
 scalar_t__ reg_class_subset_p (int,int) ; 
 TYPE_1__* rld ; 
 int /*<<< orphan*/  true_regnum (scalar_t__) ; 

__attribute__((used)) static int
find_reusable_reload (rtx *p_in, rtx out, enum reg_class class,
		      enum reload_type type, int opnum, int dont_share)
{
  rtx in = *p_in;
  int i;
  /* We can't merge two reloads if the output of either one is
     earlyclobbered.  */

  if (earlyclobber_operand_p (out))
    return n_reloads;

  /* We can use an existing reload if the class is right
     and at least one of IN and OUT is a match
     and the other is at worst neutral.
     (A zero compared against anything is neutral.)

     If SMALL_REGISTER_CLASSES, don't use existing reloads unless they are
     for the same thing since that can cause us to need more reload registers
     than we otherwise would.  */

  for (i = 0; i < n_reloads; i++)
    if ((reg_class_subset_p (class, rld[i].class)
	 || reg_class_subset_p (rld[i].class, class))
	/* If the existing reload has a register, it must fit our class.  */
	&& (rld[i].reg_rtx == 0
	    || TEST_HARD_REG_BIT (reg_class_contents[(int) class],
				  true_regnum (rld[i].reg_rtx)))
	&& ((in != 0 && MATCHES (rld[i].in, in) && ! dont_share
	     && (out == 0 || rld[i].out == 0 || MATCHES (rld[i].out, out)))
	    || (out != 0 && MATCHES (rld[i].out, out)
		&& (in == 0 || rld[i].in == 0 || MATCHES (rld[i].in, in))))
	&& (rld[i].out == 0 || ! earlyclobber_operand_p (rld[i].out))
	&& (SMALL_REGISTER_CLASS_P (class) || SMALL_REGISTER_CLASSES)
	&& MERGABLE_RELOADS (type, rld[i].when_needed, opnum, rld[i].opnum))
      return i;

  /* Reloading a plain reg for input can match a reload to postincrement
     that reg, since the postincrement's value is the right value.
     Likewise, it can match a preincrement reload, since we regard
     the preincrementation as happening before any ref in this insn
     to that register.  */
  for (i = 0; i < n_reloads; i++)
    if ((reg_class_subset_p (class, rld[i].class)
	 || reg_class_subset_p (rld[i].class, class))
	/* If the existing reload has a register, it must fit our
	   class.  */
	&& (rld[i].reg_rtx == 0
	    || TEST_HARD_REG_BIT (reg_class_contents[(int) class],
				  true_regnum (rld[i].reg_rtx)))
	&& out == 0 && rld[i].out == 0 && rld[i].in != 0
	&& ((REG_P (in)
	     && GET_RTX_CLASS (GET_CODE (rld[i].in)) == RTX_AUTOINC
	     && MATCHES (XEXP (rld[i].in, 0), in))
	    || (REG_P (rld[i].in)
		&& GET_RTX_CLASS (GET_CODE (in)) == RTX_AUTOINC
		&& MATCHES (XEXP (in, 0), rld[i].in)))
	&& (rld[i].out == 0 || ! earlyclobber_operand_p (rld[i].out))
	&& (SMALL_REGISTER_CLASS_P (class) || SMALL_REGISTER_CLASSES)
	&& MERGABLE_RELOADS (type, rld[i].when_needed,
			     opnum, rld[i].opnum))
      {
	/* Make sure reload_in ultimately has the increment,
	   not the plain register.  */
	if (REG_P (in))
	  *p_in = rld[i].in;
	return i;
      }
  return n_reloads;
}