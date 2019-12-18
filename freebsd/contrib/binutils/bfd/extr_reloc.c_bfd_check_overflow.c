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
typedef  enum complain_overflow { ____Placeholder_complain_overflow } complain_overflow ;
typedef  unsigned int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_reloc_status_type ;

/* Variables and functions */
 unsigned int N_ONES (unsigned int) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bfd_reloc_ok ; 
 int /*<<< orphan*/  bfd_reloc_overflow ; 
#define  complain_overflow_bitfield 131 
#define  complain_overflow_dont 130 
#define  complain_overflow_signed 129 
#define  complain_overflow_unsigned 128 

bfd_reloc_status_type
bfd_check_overflow (enum complain_overflow how,
		    unsigned int bitsize,
		    unsigned int rightshift,
		    unsigned int addrsize,
		    bfd_vma relocation)
{
  bfd_vma fieldmask, addrmask, signmask, ss, a;
  bfd_reloc_status_type flag = bfd_reloc_ok;

  /* Note: BITSIZE should always be <= ADDRSIZE, but in case it's not,
     we'll be permissive: extra bits in the field mask will
     automatically extend the address mask for purposes of the
     overflow check.  */
  fieldmask = N_ONES (bitsize);
  signmask = ~fieldmask;
  addrmask = N_ONES (addrsize) | fieldmask;
  a = (relocation & addrmask) >> rightshift;;

  switch (how)
    {
    case complain_overflow_dont:
      break;

    case complain_overflow_signed:
      /* If any sign bits are set, all sign bits must be set.  That
         is, A must be a valid negative address after shifting.  */
      signmask = ~ (fieldmask >> 1);
      /* Fall thru */

    case complain_overflow_bitfield:
      /* Bitfields are sometimes signed, sometimes unsigned.  We
	 explicitly allow an address wrap too, which means a bitfield
	 of n bits is allowed to store -2**n to 2**n-1.  Thus overflow
	 if the value has some, but not all, bits set outside the
	 field.  */
      ss = a & signmask;
      if (ss != 0 && ss != ((addrmask >> rightshift) & signmask))
	flag = bfd_reloc_overflow;
      break;

    case complain_overflow_unsigned:
      /* We have an overflow if the address does not fit in the field.  */
      if ((a & signmask) != 0)
	flag = bfd_reloc_overflow;
      break;

    default:
      abort ();
    }

  return flag;
}