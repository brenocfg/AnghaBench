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
struct type {int dummy; } ;
struct return_value_word {int buf_offset; int reg_offset; int reg; int len; } ;
struct gdbarch_tdep {int dummy; } ;
struct TYPE_2__ {int fp0; } ;

/* Variables and functions */
 scalar_t__ BFD_ENDIAN_BIG ; 
 int /*<<< orphan*/  FP_REGISTER_DOUBLE ; 
 scalar_t__ MIPS_FPU_DOUBLE ; 
 scalar_t__ MIPS_FPU_SINGLE ; 
 scalar_t__ MIPS_FPU_TYPE ; 
 scalar_t__ TARGET_BYTE_ORDER ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_FLT ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 scalar_t__ TYPE_CODE_UNION ; 
 int TYPE_LENGTH (struct type*) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 struct gdbarch_tdep* gdbarch_tdep (int /*<<< orphan*/ ) ; 
 TYPE_1__* mips_regnum (int /*<<< orphan*/ ) ; 
 int mips_saved_regsize (struct gdbarch_tdep*) ; 
 int register_size (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
return_value_location (struct type *valtype,
		       struct return_value_word *hi,
		       struct return_value_word *lo)
{
  int len = TYPE_LENGTH (valtype);
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);

  if (TYPE_CODE (valtype) == TYPE_CODE_FLT
      && ((MIPS_FPU_TYPE == MIPS_FPU_DOUBLE && (len == 4 || len == 8))
	  || (MIPS_FPU_TYPE == MIPS_FPU_SINGLE && len == 4)))
    {
      if (!FP_REGISTER_DOUBLE && len == 8)
	{
	  /* We need to break a 64bit float in two 32 bit halves and
	     spread them across a floating-point register pair. */
	  lo->buf_offset = TARGET_BYTE_ORDER == BFD_ENDIAN_BIG ? 4 : 0;
	  hi->buf_offset = TARGET_BYTE_ORDER == BFD_ENDIAN_BIG ? 0 : 4;
	  lo->reg_offset = ((TARGET_BYTE_ORDER == BFD_ENDIAN_BIG
			     && register_size (current_gdbarch,
					       mips_regnum (current_gdbarch)->
					       fp0) == 8) ? 4 : 0);
	  hi->reg_offset = lo->reg_offset;
	  lo->reg = mips_regnum (current_gdbarch)->fp0 + 0;
	  hi->reg = mips_regnum (current_gdbarch)->fp0 + 1;
	  lo->len = 4;
	  hi->len = 4;
	}
      else
	{
	  /* The floating point value fits in a single floating-point
	     register. */
	  lo->reg_offset = ((TARGET_BYTE_ORDER == BFD_ENDIAN_BIG
			     && register_size (current_gdbarch,
					       mips_regnum (current_gdbarch)->
					       fp0) == 8
			     && len == 4) ? 4 : 0);
	  lo->reg = mips_regnum (current_gdbarch)->fp0;
	  lo->len = len;
	  lo->buf_offset = 0;
	  hi->len = 0;
	  hi->reg_offset = 0;
	  hi->buf_offset = 0;
	  hi->reg = 0;
	}
    }
  else
    {
      /* Locate a result possibly spread across two registers. */
      int regnum = 2;
      lo->reg = regnum + 0;
      hi->reg = regnum + 1;
      if (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG
	  && len < mips_saved_regsize (tdep))
	{
	  /* "un-left-justify" the value in the low register */
	  lo->reg_offset = mips_saved_regsize (tdep) - len;
	  lo->len = len;
	  hi->reg_offset = 0;
	  hi->len = 0;
	}
      else if (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG && len > mips_saved_regsize (tdep)	/* odd-size structs */
	       && len < mips_saved_regsize (tdep) * 2
	       && (TYPE_CODE (valtype) == TYPE_CODE_STRUCT ||
		   TYPE_CODE (valtype) == TYPE_CODE_UNION))
	{
	  /* "un-left-justify" the value spread across two registers. */
	  lo->reg_offset = 2 * mips_saved_regsize (tdep) - len;
	  lo->len = mips_saved_regsize (tdep) - lo->reg_offset;
	  hi->reg_offset = 0;
	  hi->len = len - lo->len;
	}
      else
	{
	  /* Only perform a partial copy of the second register. */
	  lo->reg_offset = 0;
	  hi->reg_offset = 0;
	  if (len > mips_saved_regsize (tdep))
	    {
	      lo->len = mips_saved_regsize (tdep);
	      hi->len = len - mips_saved_regsize (tdep);
	    }
	  else
	    {
	      lo->len = len;
	      hi->len = 0;
	    }
	}
      if (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG
	  && register_size (current_gdbarch, regnum) == 8
	  && mips_saved_regsize (tdep) == 4)
	{
	  /* Account for the fact that only the least-signficant part
	     of the register is being used */
	  lo->reg_offset += 4;
	  hi->reg_offset += 4;
	}
      lo->buf_offset = 0;
      hi->buf_offset = lo->len;
    }
}