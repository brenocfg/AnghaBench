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
typedef  scalar_t__ rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int CCFPEmode ; 
 int CCFPmode ; 
 int CCX_NOOVmode ; 
 int CCXmode ; 
 int CC_NOOVmode ; 
#define  EQ 145 
#define  GE 144 
 int GET_CODE (scalar_t__) ; 
 int GET_MODE (scalar_t__) ; 
#define  GEU 143 
#define  GT 142 
#define  GTU 141 
 int INSN_ADDRESSES (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN_ADDRESSES_SET_P () ; 
 int /*<<< orphan*/  INSN_UID (scalar_t__) ; 
 int INTVAL (scalar_t__) ; 
#define  LE 140 
#define  LEU 139 
#define  LT 138 
#define  LTGT 137 
#define  LTU 136 
#define  NE 135 
 int /*<<< orphan*/  NULL_RTX ; 
#define  ORDERED 134 
 scalar_t__ REGNO (scalar_t__) ; 
 int /*<<< orphan*/  REG_BR_PROB ; 
 int REG_BR_PROB_BASE ; 
 scalar_t__ SPARC_FCC_REG ; 
 scalar_t__ SPARC_FIRST_V9_FCC_REG ; 
 scalar_t__ TARGET_V9 ; 
#define  UNEQ 133 
#define  UNGE 132 
#define  UNGT 131 
#define  UNLE 130 
#define  UNLT 129 
#define  UNORDERED 128 
 scalar_t__ XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  final_sequence ; 
 scalar_t__ find_reg_note (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int get_attr_length (scalar_t__) ; 
 int reverse_condition (int) ; 
 int reverse_condition_maybe_unordered (int) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

const char *
output_cbranch (rtx op, rtx dest, int label, int reversed, int annul,
		rtx insn)
{
  static char string[64];
  enum rtx_code code = GET_CODE (op);
  rtx cc_reg = XEXP (op, 0);
  enum machine_mode mode = GET_MODE (cc_reg);
  const char *labelno, *branch;
  int spaces = 8, far;
  char *p;

  /* v9 branches are limited to +-1MB.  If it is too far away,
     change

     bne,pt %xcc, .LC30

     to

     be,pn %xcc, .+12
      nop
     ba .LC30

     and

     fbne,a,pn %fcc2, .LC29

     to

     fbe,pt %fcc2, .+16
      nop
     ba .LC29  */

  far = TARGET_V9 && (get_attr_length (insn) >= 3);
  if (reversed ^ far)
    {
      /* Reversal of FP compares takes care -- an ordered compare
	 becomes an unordered compare and vice versa.  */
      if (mode == CCFPmode || mode == CCFPEmode)
	code = reverse_condition_maybe_unordered (code);
      else
	code = reverse_condition (code);
    }

  /* Start by writing the branch condition.  */
  if (mode == CCFPmode || mode == CCFPEmode)
    {
      switch (code)
	{
	case NE:
	  branch = "fbne";
	  break;
	case EQ:
	  branch = "fbe";
	  break;
	case GE:
	  branch = "fbge";
	  break;
	case GT:
	  branch = "fbg";
	  break;
	case LE:
	  branch = "fble";
	  break;
	case LT:
	  branch = "fbl";
	  break;
	case UNORDERED:
	  branch = "fbu";
	  break;
	case ORDERED:
	  branch = "fbo";
	  break;
	case UNGT:
	  branch = "fbug";
	  break;
	case UNLT:
	  branch = "fbul";
	  break;
	case UNEQ:
	  branch = "fbue";
	  break;
	case UNGE:
	  branch = "fbuge";
	  break;
	case UNLE:
	  branch = "fbule";
	  break;
	case LTGT:
	  branch = "fblg";
	  break;

	default:
	  gcc_unreachable ();
	}

      /* ??? !v9: FP branches cannot be preceded by another floating point
	 insn.  Because there is currently no concept of pre-delay slots,
	 we can fix this only by always emitting a nop before a floating
	 point branch.  */

      string[0] = '\0';
      if (! TARGET_V9)
	strcpy (string, "nop\n\t");
      strcat (string, branch);
    }
  else
    {
      switch (code)
	{
	case NE:
	  branch = "bne";
	  break;
	case EQ:
	  branch = "be";
	  break;
	case GE:
	  if (mode == CC_NOOVmode || mode == CCX_NOOVmode)
	    branch = "bpos";
	  else
	    branch = "bge";
	  break;
	case GT:
	  branch = "bg";
	  break;
	case LE:
	  branch = "ble";
	  break;
	case LT:
	  if (mode == CC_NOOVmode || mode == CCX_NOOVmode)
	    branch = "bneg";
	  else
	    branch = "bl";
	  break;
	case GEU:
	  branch = "bgeu";
	  break;
	case GTU:
	  branch = "bgu";
	  break;
	case LEU:
	  branch = "bleu";
	  break;
	case LTU:
	  branch = "blu";
	  break;

	default:
	  gcc_unreachable ();
	}
      strcpy (string, branch);
    }
  spaces -= strlen (branch);
  p = strchr (string, '\0');

  /* Now add the annulling, the label, and a possible noop.  */
  if (annul && ! far)
    {
      strcpy (p, ",a");
      p += 2;
      spaces -= 2;
    }

  if (TARGET_V9)
    {
      rtx note;
      int v8 = 0;

      if (! far && insn && INSN_ADDRESSES_SET_P ())
	{
	  int delta = (INSN_ADDRESSES (INSN_UID (dest))
		       - INSN_ADDRESSES (INSN_UID (insn)));
	  /* Leave some instructions for "slop".  */
	  if (delta < -260000 || delta >= 260000)
	    v8 = 1;
	}

      if (mode == CCFPmode || mode == CCFPEmode)
	{
	  static char v9_fcc_labelno[] = "%%fccX, ";
	  /* Set the char indicating the number of the fcc reg to use.  */
	  v9_fcc_labelno[5] = REGNO (cc_reg) - SPARC_FIRST_V9_FCC_REG + '0';
	  labelno = v9_fcc_labelno;
	  if (v8)
	    {
	      gcc_assert (REGNO (cc_reg) == SPARC_FCC_REG);
	      labelno = "";
	    }
	}
      else if (mode == CCXmode || mode == CCX_NOOVmode)
	{
	  labelno = "%%xcc, ";
	  gcc_assert (! v8);
	}
      else
	{
	  labelno = "%%icc, ";
	  if (v8)
	    labelno = "";
	}

      if (*labelno && insn && (note = find_reg_note (insn, REG_BR_PROB, NULL_RTX)))
	{
	  strcpy (p,
		  ((INTVAL (XEXP (note, 0)) >= REG_BR_PROB_BASE / 2) ^ far)
		  ? ",pt" : ",pn");
	  p += 3;
	  spaces -= 3;
	}
    }
  else
    labelno = "";

  if (spaces > 0)
    *p++ = '\t';
  else
    *p++ = ' ';
  strcpy (p, labelno);
  p = strchr (p, '\0');
  if (far)
    {
      strcpy (p, ".+12\n\t nop\n\tb\t");
      /* Skip the next insn if requested or
	 if we know that it will be a nop.  */
      if (annul || ! final_sequence)
        p[3] = '6';
      p += 14;
    }
  *p++ = '%';
  *p++ = 'l';
  *p++ = label + '0';
  *p++ = '%';
  *p++ = '#';
  *p = '\0';

  return string;
}