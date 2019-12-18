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
typedef  int print_mode ;
typedef  int bfd_vma ;

/* Variables and functions */
#define  DEC 134 
#define  DEC_5 133 
#define  FULL_HEX 132 
#define  HEX 131 
#define  LONG_HEX 130 
#define  PREFIX_HEX 129 
#define  UNSIGNED 128 
 int _bfd_int64_low (int) ; 
 scalar_t__ is_32bit_elf ; 
 int print_dec_vma (int,int) ; 
 int print_hex_vma (int) ; 
 int printf (char*,...) ; 
 int /*<<< orphan*/  printf_vma (int) ; 

__attribute__((used)) static int
print_vma (bfd_vma vma, print_mode mode)
{
#ifdef BFD64
  if (is_32bit_elf)
#endif
    {
      switch (mode)
	{
	case FULL_HEX:
	  return printf ("0x%8.8lx", (unsigned long) vma);

	case LONG_HEX:
	  return printf ("%8.8lx", (unsigned long) vma);

	case DEC_5:
	  if (vma <= 99999)
	    return printf ("%5ld", (long) vma);
	  /* Drop through.  */

	case PREFIX_HEX:
	  return printf ("0x%lx", (unsigned long) vma);

	case HEX:
	  return printf ("%lx", (unsigned long) vma);

	case DEC:
	  return printf ("%ld", (unsigned long) vma);

	case UNSIGNED:
	  return printf ("%lu", (unsigned long) vma);
	}
    }
#ifdef BFD64
  else
    {
      int nc = 0;

      switch (mode)
	{
	case FULL_HEX:
	  nc = printf ("0x");
	  /* Drop through.  */

	case LONG_HEX:
	  printf_vma (vma);
	  return nc + 16;

	case PREFIX_HEX:
	  nc = printf ("0x");
	  /* Drop through.  */

	case HEX:
#if BFD_HOST_64BIT_LONG
	  return nc + printf ("%lx", vma);
#else
	  return nc + print_hex_vma (vma);
#endif

	case DEC:
#if BFD_HOST_64BIT_LONG
	  return printf ("%ld", vma);
#else
	  return print_dec_vma (vma, 1);
#endif

	case DEC_5:
#if BFD_HOST_64BIT_LONG
	  if (vma <= 99999)
	    return printf ("%5ld", vma);
	  else
	    return printf ("%#lx", vma);
#else
	  if (vma <= 99999)
	    return printf ("%5ld", _bfd_int64_low (vma));
	  else
	    return print_hex_vma (vma);
#endif

	case UNSIGNED:
#if BFD_HOST_64BIT_LONG
	  return printf ("%lu", vma);
#else
	  return print_dec_vma (vma, 0);
#endif
	}
    }
#endif
  return 0;
}