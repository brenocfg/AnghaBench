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
struct fdr_ext {int* f_bits1; int* f_bits2; int /*<<< orphan*/  f_cbLine; int /*<<< orphan*/  f_cbLineOffset; int /*<<< orphan*/  f_crfd; int /*<<< orphan*/  f_rfdBase; int /*<<< orphan*/  f_caux; int /*<<< orphan*/  f_iauxBase; int /*<<< orphan*/  f_cpd; int /*<<< orphan*/  f_ipdFirst; int /*<<< orphan*/  f_copt; int /*<<< orphan*/  f_ioptBase; int /*<<< orphan*/  f_cline; int /*<<< orphan*/  f_ilineBase; int /*<<< orphan*/  f_csym; int /*<<< orphan*/  f_isymBase; int /*<<< orphan*/  f_cbSs; int /*<<< orphan*/  f_issBase; int /*<<< orphan*/  f_rss; int /*<<< orphan*/  f_adr; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_3__ {long rss; int lang; int fMerge; int fReadin; int fBigendian; int glevel; void* cbLine; void* cbLineOffset; scalar_t__ reserved; void* crfd; void* rfdBase; void* caux; void* iauxBase; void* cpd; void* ipdFirst; void* copt; void* ioptBase; void* cline; void* ilineBase; void* csym; void* isymBase; void* cbSs; void* issBase; void* adr; } ;
typedef  TYPE_1__ FDR ;

/* Variables and functions */
 void* ECOFF_GET_OFF (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int FDR_BITS1_FBIGENDIAN_BIG ; 
 int FDR_BITS1_FBIGENDIAN_LITTLE ; 
 int FDR_BITS1_FMERGE_BIG ; 
 int FDR_BITS1_FMERGE_LITTLE ; 
 int FDR_BITS1_FREADIN_BIG ; 
 int FDR_BITS1_FREADIN_LITTLE ; 
 int FDR_BITS1_LANG_BIG ; 
 int FDR_BITS1_LANG_LITTLE ; 
 int FDR_BITS1_LANG_SH_BIG ; 
 int FDR_BITS1_LANG_SH_LITTLE ; 
 int FDR_BITS2_GLEVEL_BIG ; 
 int FDR_BITS2_GLEVEL_LITTLE ; 
 int FDR_BITS2_GLEVEL_SH_BIG ; 
 int FDR_BITS2_GLEVEL_SH_LITTLE ; 
 void* H_GET_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* H_GET_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ bfd_header_big_endian (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (char*,char*,int) ; 

__attribute__((used)) static void
ecoff_swap_fdr_in (bfd *abfd, void * ext_copy, FDR *intern)
{
  struct fdr_ext ext[1];

  *ext = *(struct fdr_ext *) ext_copy;

  intern->adr           = ECOFF_GET_OFF (abfd, ext->f_adr);
  intern->rss           = H_GET_32 (abfd, ext->f_rss);
#if defined (ECOFF_64) || defined (ECOFF_SIGNED_64)
  if (intern->rss == (signed long) 0xffffffff)
    intern->rss = -1;
#endif
  intern->issBase       = H_GET_32 (abfd, ext->f_issBase);
  intern->cbSs          = ECOFF_GET_OFF (abfd, ext->f_cbSs);
  intern->isymBase      = H_GET_32 (abfd, ext->f_isymBase);
  intern->csym          = H_GET_32 (abfd, ext->f_csym);
  intern->ilineBase     = H_GET_32 (abfd, ext->f_ilineBase);
  intern->cline         = H_GET_32 (abfd, ext->f_cline);
  intern->ioptBase      = H_GET_32 (abfd, ext->f_ioptBase);
  intern->copt          = H_GET_32 (abfd, ext->f_copt);
#if defined (ECOFF_32) || defined (ECOFF_SIGNED_32)
  intern->ipdFirst      = H_GET_16 (abfd, ext->f_ipdFirst);
  intern->cpd           = H_GET_16 (abfd, ext->f_cpd);
#endif
#if defined (ECOFF_64) || defined (ECOFF_SIGNED_64)
  intern->ipdFirst      = H_GET_32 (abfd, ext->f_ipdFirst);
  intern->cpd           = H_GET_32 (abfd, ext->f_cpd);
#endif
  intern->iauxBase      = H_GET_32 (abfd, ext->f_iauxBase);
  intern->caux          = H_GET_32 (abfd, ext->f_caux);
  intern->rfdBase       = H_GET_32 (abfd, ext->f_rfdBase);
  intern->crfd          = H_GET_32 (abfd, ext->f_crfd);

  /* Now the fun stuff...  */
  if (bfd_header_big_endian (abfd))
    {
      intern->lang       = ((ext->f_bits1[0] & FDR_BITS1_LANG_BIG)
			    >> FDR_BITS1_LANG_SH_BIG);
      intern->fMerge     = 0 != (ext->f_bits1[0] & FDR_BITS1_FMERGE_BIG);
      intern->fReadin    = 0 != (ext->f_bits1[0] & FDR_BITS1_FREADIN_BIG);
      intern->fBigendian = 0 != (ext->f_bits1[0] & FDR_BITS1_FBIGENDIAN_BIG);
      intern->glevel     = ((ext->f_bits2[0] & FDR_BITS2_GLEVEL_BIG)
			    >> FDR_BITS2_GLEVEL_SH_BIG);
    }
  else
    {
      intern->lang       = ((ext->f_bits1[0] & FDR_BITS1_LANG_LITTLE)
			    >> FDR_BITS1_LANG_SH_LITTLE);
      intern->fMerge     = 0 != (ext->f_bits1[0] & FDR_BITS1_FMERGE_LITTLE);
      intern->fReadin    = 0 != (ext->f_bits1[0] & FDR_BITS1_FREADIN_LITTLE);
      intern->fBigendian = 0 != (ext->f_bits1[0] & FDR_BITS1_FBIGENDIAN_LITTLE);
      intern->glevel     = ((ext->f_bits2[0] & FDR_BITS2_GLEVEL_LITTLE)
			    >> FDR_BITS2_GLEVEL_SH_LITTLE);
    }
  intern->reserved = 0;

  intern->cbLineOffset  = ECOFF_GET_OFF (abfd, ext->f_cbLineOffset);
  intern->cbLine        = ECOFF_GET_OFF (abfd, ext->f_cbLine);

#ifdef TEST
  if (memcmp ((char *) ext, (char *) intern, sizeof (*intern)) != 0)
    abort ();
#endif
}