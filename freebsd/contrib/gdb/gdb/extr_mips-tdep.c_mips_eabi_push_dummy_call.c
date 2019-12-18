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
struct value {int dummy; } ;
struct type {int dummy; } ;
struct regcache {int dummy; } ;
struct gdbarch_tdep {int dummy; } ;
struct gdbarch {int dummy; } ;
typedef  enum type_code { ____Placeholder_type_code } type_code ;
typedef  unsigned long LONGEST ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int A0_REGNUM ; 
 scalar_t__ BFD_ENDIAN_BIG ; 
 int /*<<< orphan*/  FP_REGISTER_DOUBLE ; 
 int MAX_REGISTER_SIZE ; 
 int MIPS_LAST_ARG_REGNUM ; 
 int MIPS_LAST_FP_ARG_REGNUM ; 
 int /*<<< orphan*/  RA_REGNUM ; 
 int /*<<< orphan*/  SP_REGNUM ; 
 int /*<<< orphan*/  T9_REGNUM ; 
 scalar_t__ TARGET_BYTE_ORDER ; 
 int TYPE_CODE (struct type*) ; 
 int TYPE_CODE_FLT ; 
 int TYPE_CODE_INT ; 
 int TYPE_CODE_PTR ; 
 int TYPE_CODE_STRUCT ; 
 int TYPE_CODE_UNION ; 
 int TYPE_LENGTH (struct type*) ; 
 int /*<<< orphan*/  VALUE_ADDRESS (struct value*) ; 
 scalar_t__ VALUE_CONTENTS (struct value*) ; 
 struct type* VALUE_TYPE (struct value*) ; 
 int align_down (int,int) ; 
 int align_up (int,int) ; 
 struct type* check_typedef (struct type*) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 unsigned long extract_unsigned_integer (char*,int) ; 
 scalar_t__ fp_register_arg_p (int,struct type*) ; 
 int /*<<< orphan*/  fprintf_filtered (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 struct gdbarch_tdep* gdbarch_tdep (struct gdbarch*) ; 
 scalar_t__ mips_debug ; 
 int mips_fpa0_regnum (int /*<<< orphan*/ ) ; 
 int mips_saved_regsize (struct gdbarch_tdep*) ; 
 int mips_stack_argsize (struct gdbarch_tdep*) ; 
 int /*<<< orphan*/  paddr_nz (int) ; 
 int /*<<< orphan*/  phex (unsigned long,int) ; 
 int /*<<< orphan*/  regcache_cooked_write_signed (struct regcache*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  store_unsigned_integer (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_memory (int,char*,int) ; 
 int /*<<< orphan*/  write_register (int,unsigned long) ; 

__attribute__((used)) static CORE_ADDR
mips_eabi_push_dummy_call (struct gdbarch *gdbarch, CORE_ADDR func_addr,
			   struct regcache *regcache, CORE_ADDR bp_addr,
			   int nargs, struct value **args, CORE_ADDR sp,
			   int struct_return, CORE_ADDR struct_addr)
{
  int argreg;
  int float_argreg;
  int argnum;
  int len = 0;
  int stack_offset = 0;
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  /* For shared libraries, "t9" needs to point at the function
     address.  */
  regcache_cooked_write_signed (regcache, T9_REGNUM, func_addr);

  /* Set the return address register to point to the entry point of
     the program, where a breakpoint lies in wait.  */
  regcache_cooked_write_signed (regcache, RA_REGNUM, bp_addr);

  /* First ensure that the stack and structure return address (if any)
     are properly aligned.  The stack has to be at least 64-bit
     aligned even on 32-bit machines, because doubles must be 64-bit
     aligned.  For n32 and n64, stack frames need to be 128-bit
     aligned, so we round to this widest known alignment.  */

  sp = align_down (sp, 16);
  struct_addr = align_down (struct_addr, 16);

  /* Now make space on the stack for the args.  We allocate more
     than necessary for EABI, because the first few arguments are
     passed in registers, but that's OK.  */
  for (argnum = 0; argnum < nargs; argnum++)
    len += align_up (TYPE_LENGTH (VALUE_TYPE (args[argnum])),
		     mips_stack_argsize (tdep));
  sp -= align_up (len, 16);

  if (mips_debug)
    fprintf_unfiltered (gdb_stdlog,
			"mips_eabi_push_dummy_call: sp=0x%s allocated %ld\n",
			paddr_nz (sp), (long) align_up (len, 16));

  /* Initialize the integer and float register pointers.  */
  argreg = A0_REGNUM;
  float_argreg = mips_fpa0_regnum (current_gdbarch);

  /* The struct_return pointer occupies the first parameter-passing reg.  */
  if (struct_return)
    {
      if (mips_debug)
	fprintf_unfiltered (gdb_stdlog,
			    "mips_eabi_push_dummy_call: struct_return reg=%d 0x%s\n",
			    argreg, paddr_nz (struct_addr));
      write_register (argreg++, struct_addr);
    }

  /* Now load as many as possible of the first arguments into
     registers, and push the rest onto the stack.  Loop thru args
     from first to last.  */
  for (argnum = 0; argnum < nargs; argnum++)
    {
      char *val;
      char valbuf[MAX_REGISTER_SIZE];
      struct value *arg = args[argnum];
      struct type *arg_type = check_typedef (VALUE_TYPE (arg));
      int len = TYPE_LENGTH (arg_type);
      enum type_code typecode = TYPE_CODE (arg_type);

      if (mips_debug)
	fprintf_unfiltered (gdb_stdlog,
			    "mips_eabi_push_dummy_call: %d len=%d type=%d",
			    argnum + 1, len, (int) typecode);

      /* The EABI passes structures that do not fit in a register by
         reference.  */
      if (len > mips_saved_regsize (tdep)
	  && (typecode == TYPE_CODE_STRUCT || typecode == TYPE_CODE_UNION))
	{
	  store_unsigned_integer (valbuf, mips_saved_regsize (tdep),
				  VALUE_ADDRESS (arg));
	  typecode = TYPE_CODE_PTR;
	  len = mips_saved_regsize (tdep);
	  val = valbuf;
	  if (mips_debug)
	    fprintf_unfiltered (gdb_stdlog, " push");
	}
      else
	val = (char *) VALUE_CONTENTS (arg);

      /* 32-bit ABIs always start floating point arguments in an
         even-numbered floating point register.  Round the FP register
         up before the check to see if there are any FP registers
         left.  Non MIPS_EABI targets also pass the FP in the integer
         registers so also round up normal registers.  */
      if (!FP_REGISTER_DOUBLE && fp_register_arg_p (typecode, arg_type))
	{
	  if ((float_argreg & 1))
	    float_argreg++;
	}

      /* Floating point arguments passed in registers have to be
         treated specially.  On 32-bit architectures, doubles
         are passed in register pairs; the even register gets
         the low word, and the odd register gets the high word.
         On non-EABI processors, the first two floating point arguments are
         also copied to general registers, because MIPS16 functions
         don't use float registers for arguments.  This duplication of
         arguments in general registers can't hurt non-MIPS16 functions
         because those registers are normally skipped.  */
      /* MIPS_EABI squeezes a struct that contains a single floating
         point value into an FP register instead of pushing it onto the
         stack.  */
      if (fp_register_arg_p (typecode, arg_type)
	  && float_argreg <= MIPS_LAST_FP_ARG_REGNUM)
	{
	  if (!FP_REGISTER_DOUBLE && len == 8)
	    {
	      int low_offset = TARGET_BYTE_ORDER == BFD_ENDIAN_BIG ? 4 : 0;
	      unsigned long regval;

	      /* Write the low word of the double to the even register(s).  */
	      regval = extract_unsigned_integer (val + low_offset, 4);
	      if (mips_debug)
		fprintf_unfiltered (gdb_stdlog, " - fpreg=%d val=%s",
				    float_argreg, phex (regval, 4));
	      write_register (float_argreg++, regval);

	      /* Write the high word of the double to the odd register(s).  */
	      regval = extract_unsigned_integer (val + 4 - low_offset, 4);
	      if (mips_debug)
		fprintf_unfiltered (gdb_stdlog, " - fpreg=%d val=%s",
				    float_argreg, phex (regval, 4));
	      write_register (float_argreg++, regval);
	    }
	  else
	    {
	      /* This is a floating point value that fits entirely
	         in a single register.  */
	      /* On 32 bit ABI's the float_argreg is further adjusted
	         above to ensure that it is even register aligned.  */
	      LONGEST regval = extract_unsigned_integer (val, len);
	      if (mips_debug)
		fprintf_unfiltered (gdb_stdlog, " - fpreg=%d val=%s",
				    float_argreg, phex (regval, len));
	      write_register (float_argreg++, regval);
	    }
	}
      else
	{
	  /* Copy the argument to general registers or the stack in
	     register-sized pieces.  Large arguments are split between
	     registers and stack.  */
	  /* Note: structs whose size is not a multiple of
	     mips_regsize() are treated specially: Irix cc passes them
	     in registers where gcc sometimes puts them on the stack.
	     For maximum compatibility, we will put them in both
	     places.  */
	  int odd_sized_struct = ((len > mips_saved_regsize (tdep))
				  && (len % mips_saved_regsize (tdep) != 0));

	  /* Note: Floating-point values that didn't fit into an FP
	     register are only written to memory.  */
	  while (len > 0)
	    {
	      /* Remember if the argument was written to the stack.  */
	      int stack_used_p = 0;
	      int partial_len = (len < mips_saved_regsize (tdep)
				 ? len : mips_saved_regsize (tdep));

	      if (mips_debug)
		fprintf_unfiltered (gdb_stdlog, " -- partial=%d",
				    partial_len);

	      /* Write this portion of the argument to the stack.  */
	      if (argreg > MIPS_LAST_ARG_REGNUM
		  || odd_sized_struct
		  || fp_register_arg_p (typecode, arg_type))
		{
		  /* Should shorter than int integer values be
		     promoted to int before being stored? */
		  int longword_offset = 0;
		  CORE_ADDR addr;
		  stack_used_p = 1;
		  if (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG)
		    {
		      if (mips_stack_argsize (tdep) == 8
			  && (typecode == TYPE_CODE_INT
			      || typecode == TYPE_CODE_PTR
			      || typecode == TYPE_CODE_FLT) && len <= 4)
			longword_offset = mips_stack_argsize (tdep) - len;
		      else if ((typecode == TYPE_CODE_STRUCT
				|| typecode == TYPE_CODE_UNION)
			       && (TYPE_LENGTH (arg_type)
				   < mips_stack_argsize (tdep)))
			longword_offset = mips_stack_argsize (tdep) - len;
		    }

		  if (mips_debug)
		    {
		      fprintf_unfiltered (gdb_stdlog, " - stack_offset=0x%s",
					  paddr_nz (stack_offset));
		      fprintf_unfiltered (gdb_stdlog, " longword_offset=0x%s",
					  paddr_nz (longword_offset));
		    }

		  addr = sp + stack_offset + longword_offset;

		  if (mips_debug)
		    {
		      int i;
		      fprintf_unfiltered (gdb_stdlog, " @0x%s ",
					  paddr_nz (addr));
		      for (i = 0; i < partial_len; i++)
			{
			  fprintf_unfiltered (gdb_stdlog, "%02x",
					      val[i] & 0xff);
			}
		    }
		  write_memory (addr, val, partial_len);
		}

	      /* Note!!! This is NOT an else clause.  Odd sized
	         structs may go thru BOTH paths.  Floating point
	         arguments will not.  */
	      /* Write this portion of the argument to a general
	         purpose register.  */
	      if (argreg <= MIPS_LAST_ARG_REGNUM
		  && !fp_register_arg_p (typecode, arg_type))
		{
		  LONGEST regval =
		    extract_unsigned_integer (val, partial_len);

		  if (mips_debug)
		    fprintf_filtered (gdb_stdlog, " - reg=%d val=%s",
				      argreg,
				      phex (regval,
					    mips_saved_regsize (tdep)));
		  write_register (argreg, regval);
		  argreg++;
		}

	      len -= partial_len;
	      val += partial_len;

	      /* Compute the the offset into the stack at which we
	         will copy the next parameter.

	         In the new EABI (and the NABI32), the stack_offset
	         only needs to be adjusted when it has been used.  */

	      if (stack_used_p)
		stack_offset += align_up (partial_len,
					  mips_stack_argsize (tdep));
	    }
	}
      if (mips_debug)
	fprintf_unfiltered (gdb_stdlog, "\n");
    }

  regcache_cooked_write_signed (regcache, SP_REGNUM, sp);

  /* Return adjusted stack pointer.  */
  return sp;
}