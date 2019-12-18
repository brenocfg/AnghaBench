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
struct hdr_ext {int /*<<< orphan*/  h_cbExtOffset; int /*<<< orphan*/  h_iextMax; int /*<<< orphan*/  h_cbRfdOffset; int /*<<< orphan*/  h_crfd; int /*<<< orphan*/  h_cbFdOffset; int /*<<< orphan*/  h_ifdMax; int /*<<< orphan*/  h_cbSsExtOffset; int /*<<< orphan*/  h_issExtMax; int /*<<< orphan*/  h_cbSsOffset; int /*<<< orphan*/  h_issMax; int /*<<< orphan*/  h_cbAuxOffset; int /*<<< orphan*/  h_iauxMax; int /*<<< orphan*/  h_cbOptOffset; int /*<<< orphan*/  h_ioptMax; int /*<<< orphan*/  h_cbSymOffset; int /*<<< orphan*/  h_isymMax; int /*<<< orphan*/  h_cbPdOffset; int /*<<< orphan*/  h_ipdMax; int /*<<< orphan*/  h_cbDnOffset; int /*<<< orphan*/  h_idnMax; int /*<<< orphan*/  h_cbLineOffset; int /*<<< orphan*/  h_cbLine; int /*<<< orphan*/  h_ilineMax; int /*<<< orphan*/  h_vstamp; int /*<<< orphan*/  h_magic; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_3__ {void* cbExtOffset; void* iextMax; void* cbRfdOffset; void* crfd; void* cbFdOffset; void* ifdMax; void* cbSsExtOffset; void* issExtMax; void* cbSsOffset; void* issMax; void* cbAuxOffset; void* iauxMax; void* cbOptOffset; void* ioptMax; void* cbSymOffset; void* isymMax; void* cbPdOffset; void* ipdMax; void* cbDnOffset; void* idnMax; void* cbLineOffset; void* cbLine; void* ilineMax; void* vstamp; void* magic; } ;
typedef  TYPE_1__ HDRR ;

/* Variables and functions */
 void* ECOFF_GET_OFF (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* H_GET_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* H_GET_S16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ memcmp (char*,char*,int) ; 

__attribute__((used)) static void
ecoff_swap_hdr_in (bfd *abfd, void * ext_copy, HDRR *intern)
{
  struct hdr_ext ext[1];

  *ext = *(struct hdr_ext *) ext_copy;

  intern->magic         = H_GET_S16     (abfd, ext->h_magic);
  intern->vstamp        = H_GET_S16     (abfd, ext->h_vstamp);
  intern->ilineMax      = H_GET_32      (abfd, ext->h_ilineMax);
  intern->cbLine        = ECOFF_GET_OFF (abfd, ext->h_cbLine);
  intern->cbLineOffset  = ECOFF_GET_OFF (abfd, ext->h_cbLineOffset);
  intern->idnMax        = H_GET_32      (abfd, ext->h_idnMax);
  intern->cbDnOffset    = ECOFF_GET_OFF (abfd, ext->h_cbDnOffset);
  intern->ipdMax        = H_GET_32      (abfd, ext->h_ipdMax);
  intern->cbPdOffset    = ECOFF_GET_OFF (abfd, ext->h_cbPdOffset);
  intern->isymMax       = H_GET_32      (abfd, ext->h_isymMax);
  intern->cbSymOffset   = ECOFF_GET_OFF (abfd, ext->h_cbSymOffset);
  intern->ioptMax       = H_GET_32      (abfd, ext->h_ioptMax);
  intern->cbOptOffset   = ECOFF_GET_OFF (abfd, ext->h_cbOptOffset);
  intern->iauxMax       = H_GET_32      (abfd, ext->h_iauxMax);
  intern->cbAuxOffset   = ECOFF_GET_OFF (abfd, ext->h_cbAuxOffset);
  intern->issMax        = H_GET_32      (abfd, ext->h_issMax);
  intern->cbSsOffset    = ECOFF_GET_OFF (abfd, ext->h_cbSsOffset);
  intern->issExtMax     = H_GET_32      (abfd, ext->h_issExtMax);
  intern->cbSsExtOffset = ECOFF_GET_OFF (abfd, ext->h_cbSsExtOffset);
  intern->ifdMax        = H_GET_32      (abfd, ext->h_ifdMax);
  intern->cbFdOffset    = ECOFF_GET_OFF (abfd, ext->h_cbFdOffset);
  intern->crfd          = H_GET_32      (abfd, ext->h_crfd);
  intern->cbRfdOffset   = ECOFF_GET_OFF (abfd, ext->h_cbRfdOffset);
  intern->iextMax       = H_GET_32      (abfd, ext->h_iextMax);
  intern->cbExtOffset   = ECOFF_GET_OFF (abfd, ext->h_cbExtOffset);

#ifdef TEST
  if (memcmp ((char *) ext, (char *) intern, sizeof (*intern)) != 0)
    abort ();
#endif
}