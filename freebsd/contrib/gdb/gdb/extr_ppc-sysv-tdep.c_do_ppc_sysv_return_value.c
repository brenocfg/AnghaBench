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
struct gdbarch_tdep {int wordsize; scalar_t__ ppc_vr0_regnum; scalar_t__ ppc_ev0_regnum; scalar_t__ ppc_gp0_regnum; } ;
struct gdbarch {int dummy; } ;
typedef  enum return_value_convention { ____Placeholder_return_value_convention } return_value_convention ;
typedef  void bfd_byte ;
typedef  int /*<<< orphan*/  ULONGEST ;

/* Variables and functions */
 scalar_t__ FP0_REGNUM ; 
 int MAX_REGISTER_SIZE ; 
 int RETURN_VALUE_REGISTER_CONVENTION ; 
 int RETURN_VALUE_STRUCT_CONVENTION ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_ARRAY ; 
 scalar_t__ TYPE_CODE_FLT ; 
 scalar_t__ TYPE_CODE_INT ; 
 int TYPE_LENGTH (struct type*) ; 
 scalar_t__ TYPE_VECTOR (struct type*) ; 
 int /*<<< orphan*/  convert_typed_floating (void const*,struct type*,char*,struct type*) ; 
 int /*<<< orphan*/  extract_unsigned_integer (void const*,int) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 struct gdbarch_tdep* gdbarch_tdep (struct gdbarch*) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ppc_floating_point_unit_p (struct gdbarch*) ; 
 int /*<<< orphan*/  regcache_cooked_read (struct regcache*,scalar_t__,char*) ; 
 int /*<<< orphan*/  regcache_cooked_read_unsigned (struct regcache*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regcache_cooked_write (struct regcache*,scalar_t__,char*) ; 
 int /*<<< orphan*/  regcache_cooked_write_unsigned (struct regcache*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct type* register_type (struct gdbarch*,scalar_t__) ; 
 int /*<<< orphan*/  store_unsigned_integer (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unpack_long (struct type*,void const*) ; 

__attribute__((used)) static enum return_value_convention
do_ppc_sysv_return_value (struct gdbarch *gdbarch, struct type *type,
			  struct regcache *regcache, void *readbuf,
			  const void *writebuf, int broken_gcc)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);
  gdb_assert (tdep->wordsize == 4);
  if (TYPE_CODE (type) == TYPE_CODE_FLT
      && TYPE_LENGTH (type) <= 8
      && ppc_floating_point_unit_p (gdbarch))
    {
      if (readbuf)
	{
	  /* Floats and doubles stored in "f1".  Convert the value to
	     the required type.  */
	  char regval[MAX_REGISTER_SIZE];
	  struct type *regtype = register_type (gdbarch, FP0_REGNUM + 1);
	  regcache_cooked_read (regcache, FP0_REGNUM + 1, regval);
	  convert_typed_floating (regval, regtype, readbuf, type);
	}
      if (writebuf)
	{
	  /* Floats and doubles stored in "f1".  Convert the value to
	     the register's "double" type.  */
	  char regval[MAX_REGISTER_SIZE];
	  struct type *regtype = register_type (gdbarch, FP0_REGNUM);
	  convert_typed_floating (writebuf, type, regval, regtype);
	  regcache_cooked_write (regcache, FP0_REGNUM + 1, regval);
	}
      return RETURN_VALUE_REGISTER_CONVENTION;
    }
  if ((TYPE_CODE (type) == TYPE_CODE_INT && TYPE_LENGTH (type) == 8)
      || (TYPE_CODE (type) == TYPE_CODE_FLT && TYPE_LENGTH (type) == 8))
    {
      if (readbuf)
	{
	  /* A long long, or a double stored in the 32 bit r3/r4.  */
	  regcache_cooked_read (regcache, tdep->ppc_gp0_regnum + 3,
				(bfd_byte *) readbuf + 0);
	  regcache_cooked_read (regcache, tdep->ppc_gp0_regnum + 4,
				(bfd_byte *) readbuf + 4);
	}
      if (writebuf)
	{
	  /* A long long, or a double stored in the 32 bit r3/r4.  */
	  regcache_cooked_write (regcache, tdep->ppc_gp0_regnum + 3,
				 (const bfd_byte *) writebuf + 0);
	  regcache_cooked_write (regcache, tdep->ppc_gp0_regnum + 4,
				 (const bfd_byte *) writebuf + 4);
	}
      return RETURN_VALUE_REGISTER_CONVENTION;
    }
  if (TYPE_CODE (type) == TYPE_CODE_INT
      && TYPE_LENGTH (type) <= tdep->wordsize)
    {
      if (readbuf)
	{
	  /* Some sort of integer stored in r3.  Since TYPE isn't
	     bigger than the register, sign extension isn't a problem
	     - just do everything unsigned.  */
	  ULONGEST regval;
	  regcache_cooked_read_unsigned (regcache, tdep->ppc_gp0_regnum + 3,
					 &regval);
	  store_unsigned_integer (readbuf, TYPE_LENGTH (type), regval);
	}
      if (writebuf)
	{
	  /* Some sort of integer stored in r3.  Use unpack_long since
	     that should handle any required sign extension.  */
	  regcache_cooked_write_unsigned (regcache, tdep->ppc_gp0_regnum + 3,
					  unpack_long (type, writebuf));
	}
      return RETURN_VALUE_REGISTER_CONVENTION;
    }
  if (TYPE_LENGTH (type) == 16
      && TYPE_CODE (type) == TYPE_CODE_ARRAY
      && TYPE_VECTOR (type) && tdep->ppc_vr0_regnum >= 0)
    {
      if (readbuf)
	{
	  /* Altivec places the return value in "v2".  */
	  regcache_cooked_read (regcache, tdep->ppc_vr0_regnum + 2, readbuf);
	}
      if (writebuf)
	{
	  /* Altivec places the return value in "v2".  */
	  regcache_cooked_write (regcache, tdep->ppc_vr0_regnum + 2, writebuf);
	}
      return RETURN_VALUE_REGISTER_CONVENTION;
    }
  if (TYPE_LENGTH (type) == 8
      && TYPE_CODE (type) == TYPE_CODE_ARRAY
      && TYPE_VECTOR (type) && tdep->ppc_ev0_regnum >= 0)
    {
      /* The e500 ABI places return values for the 64-bit DSP types
	 (__ev64_opaque__) in r3.  However, in GDB-speak, ev3
	 corresponds to the entire r3 value for e500, whereas GDB's r3
	 only corresponds to the least significant 32-bits.  So place
	 the 64-bit DSP type's value in ev3.  */
      if (readbuf)
	regcache_cooked_read (regcache, tdep->ppc_ev0_regnum + 3, readbuf);
      if (writebuf)
	regcache_cooked_write (regcache, tdep->ppc_ev0_regnum + 3, writebuf);
      return RETURN_VALUE_REGISTER_CONVENTION;
    }
  if (broken_gcc && TYPE_LENGTH (type) <= 8)
    {
      if (readbuf)
	{
	  /* GCC screwed up.  The last register isn't "left" aligned.
	     Need to extract the least significant part of each
	     register and then store that.  */
	  /* Transfer any full words.  */
	  int word = 0;
	  while (1)
	    {
	      ULONGEST reg;
	      int len = TYPE_LENGTH (type) - word * tdep->wordsize;
	      if (len <= 0)
		break;
	      if (len > tdep->wordsize)
		len = tdep->wordsize;
	      regcache_cooked_read_unsigned (regcache,
					     tdep->ppc_gp0_regnum + 3 + word,
					     &reg);
	      store_unsigned_integer (((bfd_byte *) readbuf
				       + word * tdep->wordsize), len, reg);
	      word++;
	    }
	}
      if (writebuf)
	{
	  /* GCC screwed up.  The last register isn't "left" aligned.
	     Need to extract the least significant part of each
	     register and then store that.  */
	  /* Transfer any full words.  */
	  int word = 0;
	  while (1)
	    {
	      ULONGEST reg;
	      int len = TYPE_LENGTH (type) - word * tdep->wordsize;
	      if (len <= 0)
		break;
	      if (len > tdep->wordsize)
		len = tdep->wordsize;
	      reg = extract_unsigned_integer (((const bfd_byte *) writebuf
					       + word * tdep->wordsize), len);
	      regcache_cooked_write_unsigned (regcache,
					      tdep->ppc_gp0_regnum + 3 + word,
					      reg);
	      word++;
	    }
	}
      return RETURN_VALUE_REGISTER_CONVENTION;
    }
  if (TYPE_LENGTH (type) <= 8)
    {
      if (readbuf)
	{
	  /* This matches SVr4 PPC, it does not match GCC.  */
	  /* The value is right-padded to 8 bytes and then loaded, as
	     two "words", into r3/r4.  */
	  char regvals[MAX_REGISTER_SIZE * 2];
	  regcache_cooked_read (regcache, tdep->ppc_gp0_regnum + 3,
				regvals + 0 * tdep->wordsize);
	  if (TYPE_LENGTH (type) > tdep->wordsize)
	    regcache_cooked_read (regcache, tdep->ppc_gp0_regnum + 4,
				  regvals + 1 * tdep->wordsize);
	  memcpy (readbuf, regvals, TYPE_LENGTH (type));
	}
      if (writebuf)
	{
	  /* This matches SVr4 PPC, it does not match GCC.  */
	  /* The value is padded out to 8 bytes and then loaded, as
	     two "words" into r3/r4.  */
	  char regvals[MAX_REGISTER_SIZE * 2];
	  memset (regvals, 0, sizeof regvals);
	  memcpy (regvals, writebuf, TYPE_LENGTH (type));
	  regcache_cooked_write (regcache, tdep->ppc_gp0_regnum + 3,
				 regvals + 0 * tdep->wordsize);
	  if (TYPE_LENGTH (type) > tdep->wordsize)
	    regcache_cooked_write (regcache, tdep->ppc_gp0_regnum + 4,
				   regvals + 1 * tdep->wordsize);
	}
      return RETURN_VALUE_REGISTER_CONVENTION;
    }
  return RETURN_VALUE_STRUCT_CONVENTION;
}