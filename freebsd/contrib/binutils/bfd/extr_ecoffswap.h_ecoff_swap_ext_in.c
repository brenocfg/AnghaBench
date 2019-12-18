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
struct ext_ext {int* es_bits1; int /*<<< orphan*/  es_asym; int /*<<< orphan*/  es_ifd; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_3__ {int jmptbl; int cobol_main; int weakext; int /*<<< orphan*/  asym; int /*<<< orphan*/  ifd; scalar_t__ reserved; } ;
typedef  TYPE_1__ EXTR ;

/* Variables and functions */
 int EXT_BITS1_COBOL_MAIN_BIG ; 
 int EXT_BITS1_COBOL_MAIN_LITTLE ; 
 int EXT_BITS1_JMPTBL_BIG ; 
 int EXT_BITS1_JMPTBL_LITTLE ; 
 int EXT_BITS1_WEAKEXT_BIG ; 
 int EXT_BITS1_WEAKEXT_LITTLE ; 
 int /*<<< orphan*/  H_GET_S16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_GET_S32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ bfd_header_big_endian (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecoff_swap_sym_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (char*,char*,int) ; 

__attribute__((used)) static void
ecoff_swap_ext_in (bfd *abfd, void * ext_copy, EXTR *intern)
{
  struct ext_ext ext[1];

  *ext = *(struct ext_ext *) ext_copy;

  /* Now the fun stuff...  */
  if (bfd_header_big_endian (abfd))
    {
      intern->jmptbl      = 0 != (ext->es_bits1[0] & EXT_BITS1_JMPTBL_BIG);
      intern->cobol_main  = 0 != (ext->es_bits1[0] & EXT_BITS1_COBOL_MAIN_BIG);
      intern->weakext     = 0 != (ext->es_bits1[0] & EXT_BITS1_WEAKEXT_BIG);
    }
  else
    {
      intern->jmptbl      = 0 != (ext->es_bits1[0] & EXT_BITS1_JMPTBL_LITTLE);
      intern->cobol_main  = 0 != (ext->es_bits1[0] & EXT_BITS1_COBOL_MAIN_LITTLE);
      intern->weakext     = 0 != (ext->es_bits1[0] & EXT_BITS1_WEAKEXT_LITTLE);
    }
  intern->reserved = 0;

#if defined (ECOFF_32) || defined (ECOFF_SIGNED_32)
  intern->ifd = H_GET_S16 (abfd, ext->es_ifd);
#endif
#if defined (ECOFF_64) || defined (ECOFF_SIGNED_64)
  intern->ifd = H_GET_S32 (abfd, ext->es_ifd);
#endif

  ecoff_swap_sym_in (abfd, &ext->es_asym, &intern->asym);

#ifdef TEST
  if (memcmp ((char *) ext, (char *) intern, sizeof (*intern)) != 0)
    abort ();
#endif
}