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
struct obj_section {int /*<<< orphan*/ * objfile; } ;
struct minimal_symbol {int dummy; } ;
struct gdbarch_tdep {int wordsize; int ppc_gp0_regnum; scalar_t__ ppc_vr0_regnum; int ppc_lr_regnum; } ;
struct gdbarch {int dummy; } ;
typedef  int ULONGEST ;
typedef  int LONGEST ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int FP0_REGNUM ; 
 int MAX_REGISTER_SIZE ; 
 int SP_REGNUM ; 
 char* SYMBOL_LINKAGE_NAME (struct minimal_symbol*) ; 
 int SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_ARRAY ; 
 scalar_t__ TYPE_CODE_ENUM ; 
 scalar_t__ TYPE_CODE_FLT ; 
 scalar_t__ TYPE_CODE_INT ; 
 int TYPE_LENGTH (struct type*) ; 
 scalar_t__ TYPE_VECTOR (struct type*) ; 
 char* VALUE_CONTENTS (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 int align_down (int,int) ; 
 int align_up (int,int) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_typed_floating (char*,struct type*,char*,struct type*) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 struct obj_section* find_pc_section (int) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 struct gdbarch_tdep* gdbarch_tdep (int /*<<< orphan*/ ) ; 
 struct minimal_symbol* lookup_minimal_symbol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct minimal_symbol* lookup_minimal_symbol_by_pc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ppc_floating_point_unit_p (int /*<<< orphan*/ ) ; 
 int read_memory_unsigned_integer (int,int) ; 
 int read_sp () ; 
 int /*<<< orphan*/  regcache_cooked_write (struct regcache*,int,char*) ; 
 int /*<<< orphan*/  regcache_cooked_write_signed (struct regcache*,int,int) ; 
 int /*<<< orphan*/  regcache_cooked_write_unsigned (struct regcache*,int,int) ; 
 struct type* register_type (struct gdbarch*,int) ; 
 int unpack_long (struct type*,char*) ; 
 int /*<<< orphan*/  write_memory (int,char*,int) ; 
 int /*<<< orphan*/  write_memory_signed_integer (int,int,int const) ; 
 int /*<<< orphan*/  write_memory_unsigned_integer (int,int,int) ; 

CORE_ADDR
ppc64_sysv_abi_push_dummy_call (struct gdbarch *gdbarch, CORE_ADDR func_addr,
				struct regcache *regcache, CORE_ADDR bp_addr,
				int nargs, struct value **args, CORE_ADDR sp,
				int struct_return, CORE_ADDR struct_addr)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);
  /* By this stage in the proceedings, SP has been decremented by "red
     zone size" + "struct return size".  Fetch the stack-pointer from
     before this and use that as the BACK_CHAIN.  */
  const CORE_ADDR back_chain = read_sp ();
  /* See for-loop comment below.  */
  int write_pass;
  /* Size of the Altivec's vector parameter region, the final value is
     computed in the for-loop below.  */
  LONGEST vparam_size = 0;
  /* Size of the general parameter region, the final value is computed
     in the for-loop below.  */
  LONGEST gparam_size = 0;
  /* Kevin writes ... I don't mind seeing tdep->wordsize used in the
     calls to align_up(), align_down(), etc.  because this makes it
     easier to reuse this code (in a copy/paste sense) in the future,
     but it is a 64-bit ABI and asserting that the wordsize is 8 bytes
     at some point makes it easier to verify that this function is
     correct without having to do a non-local analysis to figure out
     the possible values of tdep->wordsize.  */
  gdb_assert (tdep->wordsize == 8);

  /* Go through the argument list twice.

     Pass 1: Compute the function call's stack space and register
     requirements.

     Pass 2: Replay the same computation but this time also write the
     values out to the target.  */

  for (write_pass = 0; write_pass < 2; write_pass++)
    {
      int argno;
      /* Next available floating point register for float and double
         arguments.  */
      int freg = 1;
      /* Next available general register for non-vector (but possibly
         float) arguments.  */
      int greg = 3;
      /* Next available vector register for vector arguments.  */
      int vreg = 2;
      /* The address, at which the next general purpose parameter
         (integer, struct, float, ...) should be saved.  */
      CORE_ADDR gparam;
      /* Address, at which the next Altivec vector parameter should be
         saved.  */
      CORE_ADDR vparam;

      if (!write_pass)
	{
	  /* During the first pass, GPARAM and VPARAM are more like
	     offsets (start address zero) than addresses.  That way
	     the accumulate the total stack space each region
	     requires.  */
	  gparam = 0;
	  vparam = 0;
	}
      else
	{
	  /* Decrement the stack pointer making space for the Altivec
	     and general on-stack parameters.  Set vparam and gparam
	     to their corresponding regions.  */
	  vparam = align_down (sp - vparam_size, 16);
	  gparam = align_down (vparam - gparam_size, 16);
	  /* Add in space for the TOC, link editor double word,
	     compiler double word, LR save area, CR save area.  */
	  sp = align_down (gparam - 48, 16);
	}

      /* If the function is returning a `struct', then there is an
         extra hidden parameter (which will be passed in r3)
         containing the address of that struct..  In that case we
         should advance one word and start from r4 register to copy
         parameters.  This also consumes one on-stack parameter slot.  */
      if (struct_return)
	{
	  if (write_pass)
	    regcache_cooked_write_signed (regcache,
					  tdep->ppc_gp0_regnum + greg,
					  struct_addr);
	  greg++;
	  gparam = align_up (gparam + tdep->wordsize, tdep->wordsize);
	}

      for (argno = 0; argno < nargs; argno++)
	{
	  struct value *arg = args[argno];
	  struct type *type = check_typedef (VALUE_TYPE (arg));
	  char *val = VALUE_CONTENTS (arg);
	  if (TYPE_CODE (type) == TYPE_CODE_FLT && TYPE_LENGTH (type) <= 8)
	    {
	      /* Floats and Doubles go in f1 .. f13.  They also
	         consume a left aligned GREG,, and can end up in
	         memory.  */
	      if (write_pass)
		{
		  if (ppc_floating_point_unit_p (current_gdbarch)
		      && freg <= 13)
		    {
		      char regval[MAX_REGISTER_SIZE];
		      struct type *regtype = register_type (gdbarch,
							    FP0_REGNUM);
		      convert_typed_floating (val, type, regval, regtype);
		      regcache_cooked_write (regcache, FP0_REGNUM + freg,
					     regval);
		    }
		  if (greg <= 10)
		    {
		      /* The ABI states "Single precision floating
		         point values are mapped to the first word in
		         a single doubleword" and "... floating point
		         values mapped to the first eight doublewords
		         of the parameter save area are also passed in
		         general registers").

		         This code interprets that to mean: store it,
		         left aligned, in the general register.  */
		      char regval[MAX_REGISTER_SIZE];
		      memset (regval, 0, sizeof regval);
		      memcpy (regval, val, TYPE_LENGTH (type));
		      regcache_cooked_write (regcache,
					     tdep->ppc_gp0_regnum + greg,
					     regval);
		    }
		  write_memory (gparam, val, TYPE_LENGTH (type));
		}
	      /* Always consume parameter stack space.  */
	      freg++;
	      greg++;
	      gparam = align_up (gparam + TYPE_LENGTH (type), tdep->wordsize);
	    }
	  else if (TYPE_LENGTH (type) == 16 && TYPE_VECTOR (type)
		   && TYPE_CODE (type) == TYPE_CODE_ARRAY
		   && tdep->ppc_vr0_regnum >= 0)
	    {
	      /* In the Altivec ABI, vectors go in the vector
	         registers v2 .. v13, or when that runs out, a vector
	         annex which goes above all the normal parameters.
	         NOTE: cagney/2003-09-21: This is a guess based on the
	         PowerOpen Altivec ABI.  */
	      if (vreg <= 13)
		{
		  if (write_pass)
		    regcache_cooked_write (regcache,
					   tdep->ppc_vr0_regnum + vreg, val);
		  vreg++;
		}
	      else
		{
		  if (write_pass)
		    write_memory (vparam, val, TYPE_LENGTH (type));
		  vparam = align_up (vparam + TYPE_LENGTH (type), 16);
		}
	    }
	  else if ((TYPE_CODE (type) == TYPE_CODE_INT
		    || TYPE_CODE (type) == TYPE_CODE_ENUM)
		   && TYPE_LENGTH (type) <= 8)
	    {
	      /* Scalars get sign[un]extended and go in gpr3 .. gpr10.
	         They can also end up in memory.  */
	      if (write_pass)
		{
		  /* Sign extend the value, then store it unsigned.  */
		  ULONGEST word = unpack_long (type, val);
		  if (greg <= 10)
		    regcache_cooked_write_unsigned (regcache,
						    tdep->ppc_gp0_regnum +
						    greg, word);
		  write_memory_unsigned_integer (gparam, tdep->wordsize,
						 word);
		}
	      greg++;
	      gparam = align_up (gparam + TYPE_LENGTH (type), tdep->wordsize);
	    }
	  else
	    {
	      int byte;
	      for (byte = 0; byte < TYPE_LENGTH (type);
		   byte += tdep->wordsize)
		{
		  if (write_pass && greg <= 10)
		    {
		      char regval[MAX_REGISTER_SIZE];
		      int len = TYPE_LENGTH (type) - byte;
		      if (len > tdep->wordsize)
			len = tdep->wordsize;
		      memset (regval, 0, sizeof regval);
		      /* WARNING: cagney/2003-09-21: As best I can
		         tell, the ABI specifies that the value should
		         be left aligned.  Unfortunately, GCC doesn't
		         do this - it instead right aligns even sized
		         values and puts odd sized values on the
		         stack.  Work around that by putting both a
		         left and right aligned value into the
		         register (hopefully no one notices :-^).
		         Arrrgh!  */
		      /* Left aligned (8 byte values such as pointers
		         fill the buffer).  */
		      memcpy (regval, val + byte, len);
		      /* Right aligned (but only if even).  */
		      if (len == 1 || len == 2 || len == 4)
			memcpy (regval + tdep->wordsize - len,
				val + byte, len);
		      regcache_cooked_write (regcache, greg, regval);
		    }
		  greg++;
		}
	      if (write_pass)
		/* WARNING: cagney/2003-09-21: Strictly speaking, this
		   isn't necessary, unfortunately, GCC appears to get
		   "struct convention" parameter passing wrong putting
		   odd sized structures in memory instead of in a
		   register.  Work around this by always writing the
		   value to memory.  Fortunately, doing this
		   simplifies the code.  */
		write_memory (gparam, val, TYPE_LENGTH (type));
	      /* Always consume parameter stack space.  */
	      gparam = align_up (gparam + TYPE_LENGTH (type), tdep->wordsize);
	    }
	}

      if (!write_pass)
	{
	  /* Save the true region sizes ready for the second pass.  */
	  vparam_size = vparam;
	  /* Make certain that the general parameter save area is at
	     least the minimum 8 registers (or doublewords) in size.  */
	  if (greg < 8)
	    gparam_size = 8 * tdep->wordsize;
	  else
	    gparam_size = gparam;
	}
    }

  /* Update %sp.   */
  regcache_cooked_write_signed (regcache, SP_REGNUM, sp);

  /* Write the backchain (it occupies WORDSIZED bytes).  */
  write_memory_signed_integer (sp, tdep->wordsize, back_chain);

  /* Point the inferior function call's return address at the dummy's
     breakpoint.  */
  regcache_cooked_write_signed (regcache, tdep->ppc_lr_regnum, bp_addr);

  /* Find a value for the TOC register.  Every symbol should have both
     ".FN" and "FN" in the minimal symbol table.  "FN" points at the
     FN's descriptor, while ".FN" points at the entry point (which
     matches FUNC_ADDR).  Need to reverse from FUNC_ADDR back to the
     FN's descriptor address (while at the same time being careful to
     find "FN" in the same object file as ".FN").  */
  {
    /* Find the minimal symbol that corresponds to FUNC_ADDR (should
       have the name ".FN").  */
    struct minimal_symbol *dot_fn = lookup_minimal_symbol_by_pc (func_addr);
    if (dot_fn != NULL && SYMBOL_LINKAGE_NAME (dot_fn)[0] == '.')
      {
	/* Get the section that contains FUNC_ADR.  Need this for the
           "objfile" that it contains.  */
	struct obj_section *dot_fn_section = find_pc_section (func_addr);
	if (dot_fn_section != NULL && dot_fn_section->objfile != NULL)
	  {
	    /* Now find the corresponding "FN" (dropping ".") minimal
	       symbol's address.  Only look for the minimal symbol in
	       ".FN"'s object file - avoids problems when two object
	       files (i.e., shared libraries) contain a minimal symbol
	       with the same name.  */
	    struct minimal_symbol *fn =
	      lookup_minimal_symbol (SYMBOL_LINKAGE_NAME (dot_fn) + 1, NULL,
				     dot_fn_section->objfile);
	    if (fn != NULL)
	      {
		/* Got the address of that descriptor.  The TOC is the
		   second double word.  */
		CORE_ADDR toc =
		  read_memory_unsigned_integer (SYMBOL_VALUE_ADDRESS (fn)
						+ tdep->wordsize,
						tdep->wordsize);
		regcache_cooked_write_unsigned (regcache,
						tdep->ppc_gp0_regnum + 2, toc);
	      }
	  }
      }
  }

  return sp;
}