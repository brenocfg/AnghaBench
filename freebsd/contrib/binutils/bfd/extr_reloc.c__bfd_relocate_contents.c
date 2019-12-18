#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int rightshift; unsigned int bitpos; scalar_t__ size; int complain_on_overflow; unsigned int src_mask; unsigned int dst_mask; int /*<<< orphan*/  bitsize; } ;
typedef  TYPE_1__ reloc_howto_type ;
typedef  unsigned int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_reloc_status_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 unsigned int N_ONES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bfd_arch_bits_per_address (int /*<<< orphan*/ *) ; 
 unsigned int bfd_get_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int bfd_get_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int bfd_get_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int bfd_get_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bfd_get_reloc_size (TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_put_16 (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_put_64 (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_put_8 (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_reloc_ok ; 
 int /*<<< orphan*/  bfd_reloc_overflow ; 
#define  complain_overflow_bitfield 130 
 int complain_overflow_dont ; 
#define  complain_overflow_signed 129 
#define  complain_overflow_unsigned 128 

bfd_reloc_status_type
_bfd_relocate_contents (reloc_howto_type *howto,
			bfd *input_bfd,
			bfd_vma relocation,
			bfd_byte *location)
{
  int size;
  bfd_vma x = 0;
  bfd_reloc_status_type flag;
  unsigned int rightshift = howto->rightshift;
  unsigned int bitpos = howto->bitpos;

  /* If the size is negative, negate RELOCATION.  This isn't very
     general.  */
  if (howto->size < 0)
    relocation = -relocation;

  /* Get the value we are going to relocate.  */
  size = bfd_get_reloc_size (howto);
  switch (size)
    {
    default:
    case 0:
      abort ();
    case 1:
      x = bfd_get_8 (input_bfd, location);
      break;
    case 2:
      x = bfd_get_16 (input_bfd, location);
      break;
    case 4:
      x = bfd_get_32 (input_bfd, location);
      break;
    case 8:
#ifdef BFD64
      x = bfd_get_64 (input_bfd, location);
#else
      abort ();
#endif
      break;
    }

  /* Check for overflow.  FIXME: We may drop bits during the addition
     which we don't check for.  We must either check at every single
     operation, which would be tedious, or we must do the computations
     in a type larger than bfd_vma, which would be inefficient.  */
  flag = bfd_reloc_ok;
  if (howto->complain_on_overflow != complain_overflow_dont)
    {
      bfd_vma addrmask, fieldmask, signmask, ss;
      bfd_vma a, b, sum;

      /* Get the values to be added together.  For signed and unsigned
         relocations, we assume that all values should be truncated to
         the size of an address.  For bitfields, all the bits matter.
         See also bfd_check_overflow.  */
      fieldmask = N_ONES (howto->bitsize);
      signmask = ~fieldmask;
      addrmask = N_ONES (bfd_arch_bits_per_address (input_bfd)) | fieldmask;
      a = (relocation & addrmask) >> rightshift;
      b = (x & howto->src_mask & addrmask) >> bitpos;

      switch (howto->complain_on_overflow)
	{
	case complain_overflow_signed:
	  /* If any sign bits are set, all sign bits must be set.
	     That is, A must be a valid negative address after
	     shifting.  */
	  signmask = ~(fieldmask >> 1);
	  /* Fall thru */

	case complain_overflow_bitfield:
	  /* Much like the signed check, but for a field one bit
	     wider.  We allow a bitfield to represent numbers in the
	     range -2**n to 2**n-1, where n is the number of bits in the
	     field.  Note that when bfd_vma is 32 bits, a 32-bit reloc
	     can't overflow, which is exactly what we want.  */
	  ss = a & signmask;
	  if (ss != 0 && ss != ((addrmask >> rightshift) & signmask))
	    flag = bfd_reloc_overflow;

	  /* We only need this next bit of code if the sign bit of B
             is below the sign bit of A.  This would only happen if
             SRC_MASK had fewer bits than BITSIZE.  Note that if
             SRC_MASK has more bits than BITSIZE, we can get into
             trouble; we would need to verify that B is in range, as
             we do for A above.  */
	  ss = ((~howto->src_mask) >> 1) & howto->src_mask;
	  ss >>= bitpos;

	  /* Set all the bits above the sign bit.  */
	  b = (b ^ ss) - ss;

	  /* Now we can do the addition.  */
	  sum = a + b;

	  /* See if the result has the correct sign.  Bits above the
             sign bit are junk now; ignore them.  If the sum is
             positive, make sure we did not have all negative inputs;
             if the sum is negative, make sure we did not have all
             positive inputs.  The test below looks only at the sign
             bits, and it really just
	         SIGN (A) == SIGN (B) && SIGN (A) != SIGN (SUM)

	     We mask with addrmask here to explicitly allow an address
	     wrap-around.  The Linux kernel relies on it, and it is
	     the only way to write assembler code which can run when
	     loaded at a location 0x80000000 away from the location at
	     which it is linked.  */
	  if (((~(a ^ b)) & (a ^ sum)) & signmask & addrmask)
	    flag = bfd_reloc_overflow;
	  break;

	case complain_overflow_unsigned:
	  /* Checking for an unsigned overflow is relatively easy:
             trim the addresses and add, and trim the result as well.
             Overflow is normally indicated when the result does not
             fit in the field.  However, we also need to consider the
             case when, e.g., fieldmask is 0x7fffffff or smaller, an
             input is 0x80000000, and bfd_vma is only 32 bits; then we
             will get sum == 0, but there is an overflow, since the
             inputs did not fit in the field.  Instead of doing a
             separate test, we can check for this by or-ing in the
             operands when testing for the sum overflowing its final
             field.  */
	  sum = (a + b) & addrmask;
	  if ((a | b | sum) & signmask)
	    flag = bfd_reloc_overflow;
	  break;

	default:
	  abort ();
	}
    }

  /* Put RELOCATION in the right bits.  */
  relocation >>= (bfd_vma) rightshift;
  relocation <<= (bfd_vma) bitpos;

  /* Add RELOCATION to the right bits of X.  */
  x = ((x & ~howto->dst_mask)
       | (((x & howto->src_mask) + relocation) & howto->dst_mask));

  /* Put the relocated value back in the object file.  */
  switch (size)
    {
    default:
      abort ();
    case 1:
      bfd_put_8 (input_bfd, x, location);
      break;
    case 2:
      bfd_put_16 (input_bfd, x, location);
      break;
    case 4:
      bfd_put_32 (input_bfd, x, location);
      break;
    case 8:
#ifdef BFD64
      bfd_put_64 (input_bfd, x, location);
#else
      abort ();
#endif
      break;
    }

  return flag;
}