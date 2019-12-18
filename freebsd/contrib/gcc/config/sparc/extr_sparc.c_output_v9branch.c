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
 int DImode ; 
#define  EQ 133 
#define  GE 132 
 int GET_CODE (scalar_t__) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
#define  GT 131 
 int INSN_ADDRESSES (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN_ADDRESSES_SET_P () ; 
 int /*<<< orphan*/  INSN_UID (scalar_t__) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
#define  LE 130 
#define  LT 129 
#define  NE 128 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  REG_BR_PROB ; 
 int REG_BR_PROB_BASE ; 
 int /*<<< orphan*/  XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  final_sequence ; 
 scalar_t__ find_reg_note (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int get_attr_length (scalar_t__) ; 
 int reverse_condition (int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

const char *
output_v9branch (rtx op, rtx dest, int reg, int label, int reversed,
		 int annul, rtx insn)
{
  static char string[64];
  enum rtx_code code = GET_CODE (op);
  enum machine_mode mode = GET_MODE (XEXP (op, 0));
  rtx note;
  int far;
  char *p;

  /* branch on register are limited to +-128KB.  If it is too far away,
     change
     
     brnz,pt %g1, .LC30
     
     to
     
     brz,pn %g1, .+12
      nop
     ba,pt %xcc, .LC30
     
     and
     
     brgez,a,pn %o1, .LC29
     
     to
     
     brlz,pt %o1, .+16
      nop
     ba,pt %xcc, .LC29  */

  far = get_attr_length (insn) >= 3;

  /* If not floating-point or if EQ or NE, we can just reverse the code.  */
  if (reversed ^ far)
    code = reverse_condition (code);

  /* Only 64 bit versions of these instructions exist.  */
  gcc_assert (mode == DImode);

  /* Start by writing the branch condition.  */

  switch (code)
    {
    case NE:
      strcpy (string, "brnz");
      break;

    case EQ:
      strcpy (string, "brz");
      break;

    case GE:
      strcpy (string, "brgez");
      break;

    case LT:
      strcpy (string, "brlz");
      break;

    case LE:
      strcpy (string, "brlez");
      break;

    case GT:
      strcpy (string, "brgz");
      break;

    default:
      gcc_unreachable ();
    }

  p = strchr (string, '\0');

  /* Now add the annulling, reg, label, and nop.  */
  if (annul && ! far)
    {
      strcpy (p, ",a");
      p += 2;
    }

  if (insn && (note = find_reg_note (insn, REG_BR_PROB, NULL_RTX)))
    {
      strcpy (p,
	      ((INTVAL (XEXP (note, 0)) >= REG_BR_PROB_BASE / 2) ^ far)
	      ? ",pt" : ",pn");
      p += 3;
    }

  *p = p < string + 8 ? '\t' : ' ';
  p++;
  *p++ = '%';
  *p++ = '0' + reg;
  *p++ = ',';
  *p++ = ' ';
  if (far)
    {
      int veryfar = 1, delta;

      if (INSN_ADDRESSES_SET_P ())
	{
	  delta = (INSN_ADDRESSES (INSN_UID (dest))
		   - INSN_ADDRESSES (INSN_UID (insn)));
	  /* Leave some instructions for "slop".  */
	  if (delta >= -260000 && delta < 260000)
	    veryfar = 0;
	}

      strcpy (p, ".+12\n\t nop\n\t");
      /* Skip the next insn if requested or
	 if we know that it will be a nop.  */
      if (annul || ! final_sequence)
        p[3] = '6';
      p += 12;
      if (veryfar)
	{
	  strcpy (p, "b\t");
	  p += 2;
	}
      else
	{
	  strcpy (p, "ba,pt\t%%xcc, ");
	  p += 13;
	}
    }
  *p++ = '%';
  *p++ = 'l';
  *p++ = '0' + label;
  *p++ = '%';
  *p++ = '#';
  *p = '\0';

  return string;
}