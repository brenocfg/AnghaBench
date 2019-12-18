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
struct type {int dummy; } ;
struct regcache {int dummy; } ;
struct gdbarch_tdep {scalar_t__ ppc_gp0_regnum; } ;
struct gdbarch {int dummy; } ;
typedef  enum return_value_convention { ____Placeholder_return_value_convention } return_value_convention ;
typedef  char bfd_byte ;
typedef  int /*<<< orphan*/  ULONGEST ;

/* Variables and functions */
 scalar_t__ FP0_REGNUM ; 
 int MAX_REGISTER_SIZE ; 
 int RETURN_VALUE_REGISTER_CONVENTION ; 
 int RETURN_VALUE_STRUCT_CONVENTION ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_ARRAY ; 
 scalar_t__ TYPE_CODE_COMPLEX ; 
 scalar_t__ TYPE_CODE_FLT ; 
 scalar_t__ TYPE_CODE_INT ; 
 scalar_t__ TYPE_CODE_PTR ; 
 int TYPE_LENGTH (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  convert_typed_floating (char const*,struct type*,char*,struct type*) ; 
 struct gdbarch* current_gdbarch ; 
 struct gdbarch_tdep* gdbarch_tdep (struct gdbarch*) ; 
 int /*<<< orphan*/  regcache_cooked_read (struct regcache*,scalar_t__,char*) ; 
 int /*<<< orphan*/  regcache_cooked_read_part (struct regcache*,scalar_t__,int,int,void*) ; 
 int /*<<< orphan*/  regcache_cooked_read_unsigned (struct regcache*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regcache_cooked_write (struct regcache*,scalar_t__,char const*) ; 
 int /*<<< orphan*/  regcache_cooked_write_part (struct regcache*,scalar_t__,int,int,void const*) ; 
 int /*<<< orphan*/  regcache_cooked_write_unsigned (struct regcache*,scalar_t__,int /*<<< orphan*/ ) ; 
 int register_size (struct gdbarch*,scalar_t__) ; 
 struct type* register_type (struct gdbarch*,scalar_t__) ; 
 int /*<<< orphan*/  store_unsigned_integer (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unpack_long (struct type*,void const*) ; 

enum return_value_convention
ppc64_sysv_abi_return_value (struct gdbarch *gdbarch, struct type *valtype,
			     struct regcache *regcache, void *readbuf,
			     const void *writebuf)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);
  /* Floats and doubles in F1.  */
  if (TYPE_CODE (valtype) == TYPE_CODE_FLT && TYPE_LENGTH (valtype) <= 8)
    {
      char regval[MAX_REGISTER_SIZE];
      struct type *regtype = register_type (gdbarch, FP0_REGNUM);
      if (writebuf != NULL)
	{
	  convert_typed_floating (writebuf, valtype, regval, regtype);
	  regcache_cooked_write (regcache, FP0_REGNUM + 1, regval);
	}
      if (readbuf != NULL)
	{
	  regcache_cooked_read (regcache, FP0_REGNUM + 1, regval);
	  convert_typed_floating (regval, regtype, readbuf, valtype);
	}
      return RETURN_VALUE_REGISTER_CONVENTION;
    }
  if (TYPE_CODE (valtype) == TYPE_CODE_INT && TYPE_LENGTH (valtype) <= 8)
    {
      /* Integers in r3.  */
      if (writebuf != NULL)
	{
	  /* Be careful to sign extend the value.  */
	  regcache_cooked_write_unsigned (regcache, tdep->ppc_gp0_regnum + 3,
					  unpack_long (valtype, writebuf));
	}
      if (readbuf != NULL)
	{
	  /* Extract the integer from r3.  Since this is truncating the
	     value, there isn't a sign extension problem.  */
	  ULONGEST regval;
	  regcache_cooked_read_unsigned (regcache, tdep->ppc_gp0_regnum + 3,
					 &regval);
	  store_unsigned_integer (readbuf, TYPE_LENGTH (valtype), regval);
	}
      return RETURN_VALUE_REGISTER_CONVENTION;
    }
  /* All pointers live in r3.  */
  if (TYPE_CODE (valtype) == TYPE_CODE_PTR)
    {
      /* All pointers live in r3.  */
      if (writebuf != NULL)
	regcache_cooked_write (regcache, tdep->ppc_gp0_regnum + 3, writebuf);
      if (readbuf != NULL)
	regcache_cooked_read (regcache, tdep->ppc_gp0_regnum + 3, readbuf);
      return RETURN_VALUE_REGISTER_CONVENTION;
    }
  if (TYPE_CODE (valtype) == TYPE_CODE_ARRAY
      && TYPE_LENGTH (valtype) <= 8
      && TYPE_CODE (TYPE_TARGET_TYPE (valtype)) == TYPE_CODE_INT
      && TYPE_LENGTH (TYPE_TARGET_TYPE (valtype)) == 1)
    {
      /* Small character arrays are returned, right justified, in r3.  */
      int offset = (register_size (gdbarch, tdep->ppc_gp0_regnum + 3)
		    - TYPE_LENGTH (valtype));
      if (writebuf != NULL)
	regcache_cooked_write_part (regcache, tdep->ppc_gp0_regnum + 3,
				    offset, TYPE_LENGTH (valtype), writebuf);
      if (readbuf != NULL)
	regcache_cooked_read_part (regcache, tdep->ppc_gp0_regnum + 3,
				   offset, TYPE_LENGTH (valtype), readbuf);
      return RETURN_VALUE_REGISTER_CONVENTION;
    }
  /* Big floating point values get stored in adjacent floating
     point registers.  */
  if (TYPE_CODE (valtype) == TYPE_CODE_FLT
      && (TYPE_LENGTH (valtype) == 16 || TYPE_LENGTH (valtype) == 32))
    {
      if (writebuf || readbuf != NULL)
	{
	  int i;
	  for (i = 0; i < TYPE_LENGTH (valtype) / 8; i++)
	    {
	      if (writebuf != NULL)
		regcache_cooked_write (regcache, FP0_REGNUM + 1 + i,
				       (const bfd_byte *) writebuf + i * 8);
	      if (readbuf != NULL)
		regcache_cooked_read (regcache, FP0_REGNUM + 1 + i,
				      (bfd_byte *) readbuf + i * 8);
	    }
	}
      return RETURN_VALUE_REGISTER_CONVENTION;
    }
  /* Complex values get returned in f1:f2, need to convert.  */
  if (TYPE_CODE (valtype) == TYPE_CODE_COMPLEX
      && (TYPE_LENGTH (valtype) == 8 || TYPE_LENGTH (valtype) == 16))
    {
      if (regcache != NULL)
	{
	  int i;
	  for (i = 0; i < 2; i++)
	    {
	      char regval[MAX_REGISTER_SIZE];
	      struct type *regtype =
		register_type (current_gdbarch, FP0_REGNUM);
	      if (writebuf != NULL)
		{
		  convert_typed_floating ((const bfd_byte *) writebuf +
					  i * (TYPE_LENGTH (valtype) / 2),
					  valtype, regval, regtype);
		  regcache_cooked_write (regcache, FP0_REGNUM + 1 + i,
					 regval);
		}
	      if (readbuf != NULL)
		{
		  regcache_cooked_read (regcache, FP0_REGNUM + 1 + i, regval);
		  convert_typed_floating (regval, regtype,
					  (bfd_byte *) readbuf +
					  i * (TYPE_LENGTH (valtype) / 2),
					  valtype);
		}
	    }
	}
      return RETURN_VALUE_REGISTER_CONVENTION;
    }
  /* Big complex values get stored in f1:f4.  */
  if (TYPE_CODE (valtype) == TYPE_CODE_COMPLEX && TYPE_LENGTH (valtype) == 32)
    {
      if (regcache != NULL)
	{
	  int i;
	  for (i = 0; i < 4; i++)
	    {
	      if (writebuf != NULL)
		regcache_cooked_write (regcache, FP0_REGNUM + 1 + i,
				       (const bfd_byte *) writebuf + i * 8);
	      if (readbuf != NULL)
		regcache_cooked_read (regcache, FP0_REGNUM + 1 + i,
				      (bfd_byte *) readbuf + i * 8);
	    }
	}
      return RETURN_VALUE_REGISTER_CONVENTION;
    }
  return RETURN_VALUE_STRUCT_CONVENTION;
}