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
struct gdbarch {int dummy; } ;
typedef  int /*<<< orphan*/  ULONGEST ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int FIND_GLOBAL_POINTER (int) ; 
 int /*<<< orphan*/  IA64_BR0_REGNUM ; 
 int /*<<< orphan*/  IA64_BSP_REGNUM ; 
 int /*<<< orphan*/  IA64_CFM_REGNUM ; 
 int IA64_FR16_REGNUM ; 
 int IA64_FR8_REGNUM ; 
 int /*<<< orphan*/  IA64_GR1_REGNUM ; 
 int /*<<< orphan*/  IA64_GR8_REGNUM ; 
 int /*<<< orphan*/  IA64_PFS_REGNUM ; 
 int MAX_REGISTER_SIZE ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_FUNC ; 
 scalar_t__ TYPE_CODE_PTR ; 
 int TYPE_LENGTH (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 scalar_t__ VALUE_CONTENTS (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  builtin_type_ia64_ext ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_typed_floating (scalar_t__,struct type*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_unsigned_integer (scalar_t__,int) ; 
 int /*<<< orphan*/  find_func_descr (int /*<<< orphan*/ ,int*) ; 
 struct type* is_float_or_hfa_type (struct type*) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int read_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_cooked_write (struct regcache*,int,void*) ; 
 int /*<<< orphan*/  regcache_cooked_write_unsigned (struct regcache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rse_address_add (int,int) ; 
 scalar_t__ slot_alignment_is_next_even (struct type*) ; 
 int /*<<< orphan*/  sp_regnum ; 
 int /*<<< orphan*/  store_unsigned_integer (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_memory (int,char*,int) ; 
 int /*<<< orphan*/  write_register (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static CORE_ADDR
ia64_push_dummy_call (struct gdbarch *gdbarch, CORE_ADDR func_addr, 
		      struct regcache *regcache, CORE_ADDR bp_addr,
		      int nargs, struct value **args, CORE_ADDR sp,
		      int struct_return, CORE_ADDR struct_addr)
{
  int argno;
  struct value *arg;
  struct type *type;
  int len, argoffset;
  int nslots, rseslots, memslots, slotnum, nfuncargs;
  int floatreg;
  CORE_ADDR bsp, cfm, pfs, new_bsp, funcdescaddr, pc, global_pointer;

  nslots = 0;
  nfuncargs = 0;
  /* Count the number of slots needed for the arguments.  */
  for (argno = 0; argno < nargs; argno++)
    {
      arg = args[argno];
      type = check_typedef (VALUE_TYPE (arg));
      len = TYPE_LENGTH (type);

      if ((nslots & 1) && slot_alignment_is_next_even (type))
	nslots++;

      if (TYPE_CODE (type) == TYPE_CODE_FUNC)
	nfuncargs++;

      nslots += (len + 7) / 8;
    }

  /* Divvy up the slots between the RSE and the memory stack.  */
  rseslots = (nslots > 8) ? 8 : nslots;
  memslots = nslots - rseslots;

  /* Allocate a new RSE frame.  */
  cfm = read_register (IA64_CFM_REGNUM);

  bsp = read_register (IA64_BSP_REGNUM);
  new_bsp = rse_address_add (bsp, rseslots);
  write_register (IA64_BSP_REGNUM, new_bsp);

  pfs = read_register (IA64_PFS_REGNUM);
  pfs &= 0xc000000000000000LL;
  pfs |= (cfm & 0xffffffffffffLL);
  write_register (IA64_PFS_REGNUM, pfs);

  cfm &= 0xc000000000000000LL;
  cfm |= rseslots;
  write_register (IA64_CFM_REGNUM, cfm);
  
  /* We will attempt to find function descriptors in the .opd segment,
     but if we can't we'll construct them ourselves.  That being the
     case, we'll need to reserve space on the stack for them.  */
  funcdescaddr = sp - nfuncargs * 16;
  funcdescaddr &= ~0xfLL;

  /* Adjust the stack pointer to it's new value.  The calling conventions
     require us to have 16 bytes of scratch, plus whatever space is
     necessary for the memory slots and our function descriptors.  */
  sp = sp - 16 - (memslots + nfuncargs) * 8;
  sp &= ~0xfLL;				/* Maintain 16 byte alignment.  */

  /* Place the arguments where they belong.  The arguments will be
     either placed in the RSE backing store or on the memory stack.
     In addition, floating point arguments or HFAs are placed in
     floating point registers.  */
  slotnum = 0;
  floatreg = IA64_FR8_REGNUM;
  for (argno = 0; argno < nargs; argno++)
    {
      struct type *float_elt_type;

      arg = args[argno];
      type = check_typedef (VALUE_TYPE (arg));
      len = TYPE_LENGTH (type);

      /* Special handling for function parameters.  */
      if (len == 8 
          && TYPE_CODE (type) == TYPE_CODE_PTR 
	  && TYPE_CODE (TYPE_TARGET_TYPE (type)) == TYPE_CODE_FUNC)
	{
	  char val_buf[8];

	  store_unsigned_integer (val_buf, 8,
				  find_func_descr (extract_unsigned_integer (VALUE_CONTENTS (arg), 8),
						   &funcdescaddr));
	  if (slotnum < rseslots)
	    write_memory (rse_address_add (bsp, slotnum), val_buf, 8);
	  else
	    write_memory (sp + 16 + 8 * (slotnum - rseslots), val_buf, 8);
	  slotnum++;
	  continue;
	}

      /* Normal slots.  */

      /* Skip odd slot if necessary...  */
      if ((slotnum & 1) && slot_alignment_is_next_even (type))
	slotnum++;

      argoffset = 0;
      while (len > 0)
	{
	  char val_buf[8];

	  memset (val_buf, 0, 8);
	  memcpy (val_buf, VALUE_CONTENTS (arg) + argoffset, (len > 8) ? 8 : len);

	  if (slotnum < rseslots)
	    write_memory (rse_address_add (bsp, slotnum), val_buf, 8);
	  else
	    write_memory (sp + 16 + 8 * (slotnum - rseslots), val_buf, 8);

	  argoffset += 8;
	  len -= 8;
	  slotnum++;
	}

      /* Handle floating point types (including HFAs).  */
      float_elt_type = is_float_or_hfa_type (type);
      if (float_elt_type != NULL)
	{
	  argoffset = 0;
	  len = TYPE_LENGTH (type);
	  while (len > 0 && floatreg < IA64_FR16_REGNUM)
	    {
	      char to[MAX_REGISTER_SIZE];
	      convert_typed_floating (VALUE_CONTENTS (arg) + argoffset, float_elt_type,
				      to, builtin_type_ia64_ext);
	      regcache_cooked_write (regcache, floatreg, (void *)to);
	      floatreg++;
	      argoffset += TYPE_LENGTH (float_elt_type);
	      len -= TYPE_LENGTH (float_elt_type);
	    }
	}
    }

  /* Store the struct return value in r8 if necessary.  */
  if (struct_return)
    {
      regcache_cooked_write_unsigned (regcache, IA64_GR8_REGNUM, (ULONGEST)struct_addr);
    }

  global_pointer = FIND_GLOBAL_POINTER (func_addr);

  if (global_pointer != 0)
    write_register (IA64_GR1_REGNUM, global_pointer);

  write_register (IA64_BR0_REGNUM, bp_addr);

  write_register (sp_regnum, sp);

  return sp;
}