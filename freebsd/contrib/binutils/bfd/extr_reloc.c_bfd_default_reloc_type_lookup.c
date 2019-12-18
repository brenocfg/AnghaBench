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
typedef  int /*<<< orphan*/  reloc_howto_type ;
typedef  int bfd_reloc_code_real_type ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/  bits_per_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_FAIL () ; 
#define  BFD_RELOC_CTOR 128 
 TYPE_1__* bfd_get_arch_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_howto_32 ; 

reloc_howto_type *
bfd_default_reloc_type_lookup (bfd *abfd, bfd_reloc_code_real_type code)
{
  switch (code)
    {
    case BFD_RELOC_CTOR:
      /* The type of reloc used in a ctor, which will be as wide as the
	 address - so either a 64, 32, or 16 bitter.  */
      switch (bfd_get_arch_info (abfd)->bits_per_address)
	{
	case 64:
	  BFD_FAIL ();
	case 32:
	  return &bfd_howto_32;
	case 16:
	  BFD_FAIL ();
	default:
	  BFD_FAIL ();
	}
    default:
      BFD_FAIL ();
    }
  return NULL;
}