#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct opt_ext {int* o_bits2; int* o_bits3; int* o_bits4; int /*<<< orphan*/  o_offset; int /*<<< orphan*/  o_rndx; int /*<<< orphan*/ * o_bits1; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_3__ {unsigned int value; int /*<<< orphan*/  offset; int /*<<< orphan*/  rndx; int /*<<< orphan*/  ot; } ;
typedef  TYPE_1__ OPTR ;

/* Variables and functions */
 int /*<<< orphan*/  H_GET_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int OPT_BITS2_VALUE_SH_LEFT_BIG ; 
 int OPT_BITS2_VALUE_SH_LEFT_LITTLE ; 
 int /*<<< orphan*/  _bfd_ecoff_swap_rndx_in (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ bfd_header_big_endian (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (char*,char*,int) ; 

__attribute__((used)) static void
ecoff_swap_opt_in (bfd *abfd, void * ext_copy, OPTR * intern)
{
  struct opt_ext ext[1];

  *ext = *(struct opt_ext *) ext_copy;

  if (bfd_header_big_endian (abfd))
    {
      intern->ot = ext->o_bits1[0];
      intern->value = (((unsigned int) ext->o_bits2[0]
			<< OPT_BITS2_VALUE_SH_LEFT_BIG)
		       | ((unsigned int) ext->o_bits3[0]
			  << OPT_BITS2_VALUE_SH_LEFT_BIG)
		       | ((unsigned int) ext->o_bits4[0]
			  << OPT_BITS2_VALUE_SH_LEFT_BIG));
    }
  else
    {
      intern->ot = ext->o_bits1[0];
      intern->value = ((ext->o_bits2[0] << OPT_BITS2_VALUE_SH_LEFT_LITTLE)
		       | (ext->o_bits3[0] << OPT_BITS2_VALUE_SH_LEFT_LITTLE)
		       | (ext->o_bits4[0] << OPT_BITS2_VALUE_SH_LEFT_LITTLE));
    }

  _bfd_ecoff_swap_rndx_in (bfd_header_big_endian (abfd),
			   &ext->o_rndx, &intern->rndx);

  intern->offset = H_GET_32 (abfd, ext->o_offset);

#ifdef TEST
  if (memcmp ((char *) ext, (char *) intern, sizeof (*intern)) != 0)
    abort ();
#endif
}