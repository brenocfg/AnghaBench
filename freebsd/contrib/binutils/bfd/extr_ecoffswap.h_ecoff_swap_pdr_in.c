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
struct pdr_ext {int* p_bits1; int* p_bits2; int /*<<< orphan*/  p_localoff; int /*<<< orphan*/  p_gp_prologue; int /*<<< orphan*/  p_cbLineOffset; int /*<<< orphan*/  p_lnHigh; int /*<<< orphan*/  p_lnLow; int /*<<< orphan*/  p_pcreg; int /*<<< orphan*/  p_framereg; int /*<<< orphan*/  p_frameoffset; int /*<<< orphan*/  p_fregoffset; int /*<<< orphan*/  p_fregmask; int /*<<< orphan*/  p_iopt; int /*<<< orphan*/  p_regoffset; int /*<<< orphan*/  p_regmask; int /*<<< orphan*/  p_iline; int /*<<< orphan*/  p_isym; int /*<<< orphan*/  p_adr; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_3__ {long isym; long iline; int gp_used; int reg_frame; int prof; int reserved; void* localoff; void* gp_prologue; void* cbLineOffset; void* lnHigh; void* lnLow; void* pcreg; void* framereg; void* frameoffset; void* fregoffset; void* fregmask; void* iopt; void* regoffset; void* regmask; void* adr; } ;
typedef  TYPE_1__ PDR ;

/* Variables and functions */
 void* ECOFF_GET_OFF (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* H_GET_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* H_GET_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* H_GET_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* H_GET_S32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PDR_BITS1_GP_USED_BIG ; 
 int PDR_BITS1_GP_USED_LITTLE ; 
 int PDR_BITS1_PROF_BIG ; 
 int PDR_BITS1_PROF_LITTLE ; 
 int PDR_BITS1_REG_FRAME_BIG ; 
 int PDR_BITS1_REG_FRAME_LITTLE ; 
 int PDR_BITS1_RESERVED_BIG ; 
 int PDR_BITS1_RESERVED_LITTLE ; 
 int PDR_BITS1_RESERVED_SH_LEFT_BIG ; 
 int PDR_BITS1_RESERVED_SH_LITTLE ; 
 int PDR_BITS2_RESERVED_BIG ; 
 int PDR_BITS2_RESERVED_LITTLE ; 
 int PDR_BITS2_RESERVED_SH_BIG ; 
 int PDR_BITS2_RESERVED_SH_LEFT_LITTLE ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ bfd_header_big_endian (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ecoff_swap_pdr_in (bfd *abfd, void * ext_copy, PDR *intern)
{
  struct pdr_ext ext[1];

  *ext = *(struct pdr_ext *) ext_copy;

  memset ((void *) intern, 0, sizeof (*intern));

  intern->adr           = ECOFF_GET_OFF (abfd, ext->p_adr);
  intern->isym          = H_GET_32 (abfd, ext->p_isym);
  intern->iline         = H_GET_32 (abfd, ext->p_iline);
  intern->regmask       = H_GET_32 (abfd, ext->p_regmask);
  intern->regoffset     = H_GET_S32 (abfd, ext->p_regoffset);
  intern->iopt          = H_GET_S32 (abfd, ext->p_iopt);
  intern->fregmask      = H_GET_32 (abfd, ext->p_fregmask);
  intern->fregoffset    = H_GET_S32 (abfd, ext->p_fregoffset);
  intern->frameoffset   = H_GET_S32 (abfd, ext->p_frameoffset);
  intern->framereg      = H_GET_16 (abfd, ext->p_framereg);
  intern->pcreg         = H_GET_16 (abfd, ext->p_pcreg);
  intern->lnLow         = H_GET_32 (abfd, ext->p_lnLow);
  intern->lnHigh        = H_GET_32 (abfd, ext->p_lnHigh);
  intern->cbLineOffset  = ECOFF_GET_OFF (abfd, ext->p_cbLineOffset);

#if defined (ECOFF_64) || defined (ECOFF_SIGNED_64)
  if (intern->isym == (signed long) 0xffffffff)
    intern->isym = -1;
  if (intern->iline == (signed long) 0xffffffff)
    intern->iline = -1;

  intern->gp_prologue = H_GET_8 (abfd, ext->p_gp_prologue);
  if (bfd_header_big_endian (abfd))
    {
      intern->gp_used = 0 != (ext->p_bits1[0] & PDR_BITS1_GP_USED_BIG);
      intern->reg_frame = 0 != (ext->p_bits1[0] & PDR_BITS1_REG_FRAME_BIG);
      intern->prof = 0 != (ext->p_bits1[0] & PDR_BITS1_PROF_BIG);
      intern->reserved = (((ext->p_bits1[0] & PDR_BITS1_RESERVED_BIG)
			   << PDR_BITS1_RESERVED_SH_LEFT_BIG)
			  | ((ext->p_bits2[0] & PDR_BITS2_RESERVED_BIG)
			     >> PDR_BITS2_RESERVED_SH_BIG));
    }
  else
    {
      intern->gp_used = 0 != (ext->p_bits1[0] & PDR_BITS1_GP_USED_LITTLE);
      intern->reg_frame = 0 != (ext->p_bits1[0] & PDR_BITS1_REG_FRAME_LITTLE);
      intern->prof = 0 != (ext->p_bits1[0] & PDR_BITS1_PROF_LITTLE);
      intern->reserved = (((ext->p_bits1[0] & PDR_BITS1_RESERVED_LITTLE)
			   >> PDR_BITS1_RESERVED_SH_LITTLE)
			  | ((ext->p_bits2[0] & PDR_BITS2_RESERVED_LITTLE)
			     << PDR_BITS2_RESERVED_SH_LEFT_LITTLE));
    }
  intern->localoff = H_GET_8 (abfd, ext->p_localoff);
#endif

#ifdef TEST
  if (memcmp ((char *) ext, (char *) intern, sizeof (*intern)) != 0)
    abort ();
#endif
}