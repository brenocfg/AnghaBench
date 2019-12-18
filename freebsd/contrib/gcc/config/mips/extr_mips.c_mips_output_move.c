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

/* Variables and functions */
 scalar_t__ ALL_COP_REG_P (size_t) ; 
 scalar_t__ CONST0_RTX (scalar_t__) ; 
 scalar_t__ CONST_GP_P (scalar_t__) ; 
 int CONST_INT ; 
 char COPNUM_AS_CHAR_FROM_REGNUM (size_t) ; 
 scalar_t__ DSP_ACC_REG_P (size_t) ; 
 scalar_t__ FP_REG_P (size_t) ; 
 int GET_CODE (scalar_t__) ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
 int GET_MODE_SIZE (scalar_t__) ; 
 scalar_t__ GP_REG_P (size_t) ; 
 int HIGH ; 
 int INTVAL (scalar_t__) ; 
 scalar_t__ ISA_HAS_8CC ; 
 scalar_t__ MD_REG_P (size_t) ; 
 int MEM ; 
 int REG ; 
 size_t REGNO (scalar_t__) ; 
 scalar_t__ ST_REG_P (size_t) ; 
 int /*<<< orphan*/  TARGET_MIPS16 ; 
 scalar_t__ V2SFmode ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ mips_split_64bit_move_p (scalar_t__,scalar_t__) ; 
 char** reg_names ; 
 scalar_t__ symbolic_operand (scalar_t__,int /*<<< orphan*/ ) ; 

const char *
mips_output_move (rtx dest, rtx src)
{
  enum rtx_code dest_code, src_code;
  bool dbl_p;

  dest_code = GET_CODE (dest);
  src_code = GET_CODE (src);
  dbl_p = (GET_MODE_SIZE (GET_MODE (dest)) == 8);

  if (dbl_p && mips_split_64bit_move_p (dest, src))
    return "#";

  if ((src_code == REG && GP_REG_P (REGNO (src)))
      || (!TARGET_MIPS16 && src == CONST0_RTX (GET_MODE (dest))))
    {
      if (dest_code == REG)
	{
	  if (GP_REG_P (REGNO (dest)))
	    return "move\t%0,%z1";

	  if (MD_REG_P (REGNO (dest)))
	    return "mt%0\t%z1";

	  if (DSP_ACC_REG_P (REGNO (dest)))
	    {
	      static char retval[] = "mt__\t%z1,%q0";
	      retval[2] = reg_names[REGNO (dest)][4];
	      retval[3] = reg_names[REGNO (dest)][5];
	      return retval;
	    }

	  if (FP_REG_P (REGNO (dest)))
	    return (dbl_p ? "dmtc1\t%z1,%0" : "mtc1\t%z1,%0");

	  if (ALL_COP_REG_P (REGNO (dest)))
	    {
	      static char retval[] = "dmtc_\t%z1,%0";

	      retval[4] = COPNUM_AS_CHAR_FROM_REGNUM (REGNO (dest));
	      return (dbl_p ? retval : retval + 1);
	    }
	}
      if (dest_code == MEM)
	return (dbl_p ? "sd\t%z1,%0" : "sw\t%z1,%0");
    }
  if (dest_code == REG && GP_REG_P (REGNO (dest)))
    {
      if (src_code == REG)
	{
	  if (DSP_ACC_REG_P (REGNO (src)))
	    {
	      static char retval[] = "mf__\t%0,%q1";
	      retval[2] = reg_names[REGNO (src)][4];
	      retval[3] = reg_names[REGNO (src)][5];
	      return retval;
	    }

	  if (ST_REG_P (REGNO (src)) && ISA_HAS_8CC)
	    return "lui\t%0,0x3f80\n\tmovf\t%0,%.,%1";

	  if (FP_REG_P (REGNO (src)))
	    return (dbl_p ? "dmfc1\t%0,%1" : "mfc1\t%0,%1");

	  if (ALL_COP_REG_P (REGNO (src)))
	    {
	      static char retval[] = "dmfc_\t%0,%1";

	      retval[4] = COPNUM_AS_CHAR_FROM_REGNUM (REGNO (src));
	      return (dbl_p ? retval : retval + 1);
	    }
	}

      if (src_code == MEM)
	return (dbl_p ? "ld\t%0,%1" : "lw\t%0,%1");

      if (src_code == CONST_INT)
	{
	  /* Don't use the X format, because that will give out of
	     range numbers for 64 bit hosts and 32 bit targets.  */
	  if (!TARGET_MIPS16)
	    return "li\t%0,%1\t\t\t# %X1";

	  if (INTVAL (src) >= 0 && INTVAL (src) <= 0xffff)
	    return "li\t%0,%1";

	  if (INTVAL (src) < 0 && INTVAL (src) >= -0xffff)
	    return "#";
	}

      if (src_code == HIGH)
	return "lui\t%0,%h1";

      if (CONST_GP_P (src))
	return "move\t%0,%1";

      if (symbolic_operand (src, VOIDmode))
	return (dbl_p ? "dla\t%0,%1" : "la\t%0,%1");
    }
  if (src_code == REG && FP_REG_P (REGNO (src)))
    {
      if (dest_code == REG && FP_REG_P (REGNO (dest)))
	{
	  if (GET_MODE (dest) == V2SFmode)
	    return "mov.ps\t%0,%1";
	  else
	    return (dbl_p ? "mov.d\t%0,%1" : "mov.s\t%0,%1");
	}

      if (dest_code == MEM)
	return (dbl_p ? "sdc1\t%1,%0" : "swc1\t%1,%0");
    }
  if (dest_code == REG && FP_REG_P (REGNO (dest)))
    {
      if (src_code == MEM)
	return (dbl_p ? "ldc1\t%0,%1" : "lwc1\t%0,%1");
    }
  if (dest_code == REG && ALL_COP_REG_P (REGNO (dest)) && src_code == MEM)
    {
      static char retval[] = "l_c_\t%0,%1";

      retval[1] = (dbl_p ? 'd' : 'w');
      retval[3] = COPNUM_AS_CHAR_FROM_REGNUM (REGNO (dest));
      return retval;
    }
  if (dest_code == MEM && src_code == REG && ALL_COP_REG_P (REGNO (src)))
    {
      static char retval[] = "s_c_\t%1,%0";

      retval[1] = (dbl_p ? 'd' : 'w');
      retval[3] = COPNUM_AS_CHAR_FROM_REGNUM (REGNO (src));
      return retval;
    }
  gcc_unreachable ();
}