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
struct TYPE_3__ {int value; int /*<<< orphan*/  rndx; int /*<<< orphan*/  ot; } ;
typedef  TYPE_1__ OPTR ;

/* Variables and functions */
 int /*<<< orphan*/  H_PUT_32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int OPT_BITS2_VALUE_SH_LEFT_BIG ; 
 int OPT_BITS2_VALUE_SH_LEFT_LITTLE ; 
 int OPT_BITS3_VALUE_SH_LEFT_BIG ; 
 int OPT_BITS3_VALUE_SH_LEFT_LITTLE ; 
 int OPT_BITS4_VALUE_SH_LEFT_BIG ; 
 int OPT_BITS4_VALUE_SH_LEFT_LITTLE ; 
 int /*<<< orphan*/  _bfd_ecoff_swap_rndx_out (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ bfd_header_big_endian (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (char*,char*,int) ; 

__attribute__((used)) static void
ecoff_swap_opt_out (bfd *abfd, const OPTR *intern_copy, void * ext_ptr)
{
  struct opt_ext *ext = (struct opt_ext *) ext_ptr;
  OPTR intern[1];

  /* Make it reasonable to do in-place.  */
  *intern = *intern_copy;

  if (bfd_header_big_endian (abfd))
    {
      ext->o_bits1[0] = intern->ot;
      ext->o_bits2[0] = intern->value >> OPT_BITS2_VALUE_SH_LEFT_BIG;
      ext->o_bits3[0] = intern->value >> OPT_BITS3_VALUE_SH_LEFT_BIG;
      ext->o_bits4[0] = intern->value >> OPT_BITS4_VALUE_SH_LEFT_BIG;
    }
  else
    {
      ext->o_bits1[0] = intern->ot;
      ext->o_bits2[0] = intern->value >> OPT_BITS2_VALUE_SH_LEFT_LITTLE;
      ext->o_bits3[0] = intern->value >> OPT_BITS3_VALUE_SH_LEFT_LITTLE;
      ext->o_bits4[0] = intern->value >> OPT_BITS4_VALUE_SH_LEFT_LITTLE;
    }

  _bfd_ecoff_swap_rndx_out (bfd_header_big_endian (abfd),
			    &intern->rndx, &ext->o_rndx);

  H_PUT_32 (abfd, intern->value, ext->o_offset);

#ifdef TEST
  if (memcmp ((char *) ext, (char *) intern, sizeof (*intern)) != 0)
    abort ();
#endif
}