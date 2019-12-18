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
struct internal_aouthdr {void* fprmask; void* gprmask; void* gp_value; void* bss_start; void** cprmask; void* o_maxdata; void* o_maxstack; void* o_cputype; void* o_modtype; void* o_algndata; void* o_algntext; void* o_snbss; void* o_snloader; void* o_sntoc; void* o_sndata; void* o_sntext; void* o_snentry; void* o_toc; int /*<<< orphan*/ * vid; int /*<<< orphan*/  o_sri; int /*<<< orphan*/  o_inlib; void* tagentries; int /*<<< orphan*/  data_start; int /*<<< orphan*/  text_start; int /*<<< orphan*/  entry; int /*<<< orphan*/  bsize; int /*<<< orphan*/  dsize; int /*<<< orphan*/  tsize; void* vstamp; void* magic; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/  fprmask; int /*<<< orphan*/  gprmask; int /*<<< orphan*/  gp_value; int /*<<< orphan*/  bss_start; int /*<<< orphan*/ * cprmask; int /*<<< orphan*/  o_maxdata; int /*<<< orphan*/  o_maxstack; int /*<<< orphan*/  o_cputype; int /*<<< orphan*/  o_modtype; int /*<<< orphan*/  o_algndata; int /*<<< orphan*/  o_algntext; int /*<<< orphan*/  o_snbss; int /*<<< orphan*/  o_snloader; int /*<<< orphan*/  o_sntoc; int /*<<< orphan*/  o_sndata; int /*<<< orphan*/  o_sntext; int /*<<< orphan*/  o_snentry; int /*<<< orphan*/  o_toc; scalar_t__ vid; scalar_t__ o_sri; scalar_t__ o_inlib; int /*<<< orphan*/  tagentries; int /*<<< orphan*/  data_start; int /*<<< orphan*/  text_start; int /*<<< orphan*/  entry; int /*<<< orphan*/  bsize; int /*<<< orphan*/  dsize; int /*<<< orphan*/  tsize; int /*<<< orphan*/  vstamp; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ AOUTHDR ;

/* Variables and functions */
 int /*<<< orphan*/  GET_AOUTHDR_BSIZE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_AOUTHDR_DATA_START (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_AOUTHDR_DSIZE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_AOUTHDR_ENTRY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_AOUTHDR_TEXT_START (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_AOUTHDR_TSIZE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* H_GET_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* H_GET_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* H_GET_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_PUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
coff_swap_aouthdr_in (bfd * abfd, void * aouthdr_ext1, void * aouthdr_int1)
{
  AOUTHDR *aouthdr_ext;
  struct internal_aouthdr *aouthdr_int;

  aouthdr_ext = (AOUTHDR *) aouthdr_ext1;
  aouthdr_int = (struct internal_aouthdr *) aouthdr_int1;
  aouthdr_int->magic = H_GET_16 (abfd, aouthdr_ext->magic);
  aouthdr_int->vstamp = H_GET_16 (abfd, aouthdr_ext->vstamp);
  aouthdr_int->tsize = GET_AOUTHDR_TSIZE (abfd, aouthdr_ext->tsize);
  aouthdr_int->dsize = GET_AOUTHDR_DSIZE (abfd, aouthdr_ext->dsize);
  aouthdr_int->bsize = GET_AOUTHDR_BSIZE (abfd, aouthdr_ext->bsize);
  aouthdr_int->entry = GET_AOUTHDR_ENTRY (abfd, aouthdr_ext->entry);
  aouthdr_int->text_start =
    GET_AOUTHDR_TEXT_START (abfd, aouthdr_ext->text_start);
  aouthdr_int->data_start =
    GET_AOUTHDR_DATA_START (abfd, aouthdr_ext->data_start);

#ifdef I960
  aouthdr_int->tagentries = H_GET_32 (abfd, aouthdr_ext->tagentries);
#endif

#ifdef APOLLO_M68
  H_PUT_32 (abfd, aouthdr_int->o_inlib, aouthdr_ext->o_inlib);
  H_PUT_32 (abfd, aouthdr_int->o_sri, aouthdr_ext->o_sri);
  H_PUT_32 (abfd, aouthdr_int->vid[0], aouthdr_ext->vid);
  H_PUT_32 (abfd, aouthdr_int->vid[1], aouthdr_ext->vid + 4);
#endif

#ifdef RS6000COFF_C
#ifdef XCOFF64
  aouthdr_int->o_toc = H_GET_64 (abfd, aouthdr_ext->o_toc);
#else
  aouthdr_int->o_toc = H_GET_32 (abfd, aouthdr_ext->o_toc);
#endif
  aouthdr_int->o_snentry  = H_GET_16 (abfd, aouthdr_ext->o_snentry);
  aouthdr_int->o_sntext   = H_GET_16 (abfd, aouthdr_ext->o_sntext);
  aouthdr_int->o_sndata   = H_GET_16 (abfd, aouthdr_ext->o_sndata);
  aouthdr_int->o_sntoc    = H_GET_16 (abfd, aouthdr_ext->o_sntoc);
  aouthdr_int->o_snloader = H_GET_16 (abfd, aouthdr_ext->o_snloader);
  aouthdr_int->o_snbss    = H_GET_16 (abfd, aouthdr_ext->o_snbss);
  aouthdr_int->o_algntext = H_GET_16 (abfd, aouthdr_ext->o_algntext);
  aouthdr_int->o_algndata = H_GET_16 (abfd, aouthdr_ext->o_algndata);
  aouthdr_int->o_modtype  = H_GET_16 (abfd, aouthdr_ext->o_modtype);
  aouthdr_int->o_cputype  = H_GET_16 (abfd, aouthdr_ext->o_cputype);
#ifdef XCOFF64
  aouthdr_int->o_maxstack = H_GET_64 (abfd, aouthdr_ext->o_maxstack);
  aouthdr_int->o_maxdata  = H_GET_64 (abfd, aouthdr_ext->o_maxdata);
#else
  aouthdr_int->o_maxstack = H_GET_32 (abfd, aouthdr_ext->o_maxstack);
  aouthdr_int->o_maxdata  = H_GET_32 (abfd, aouthdr_ext->o_maxdata);
#endif
#endif

#ifdef MIPSECOFF
  aouthdr_int->bss_start  = H_GET_32 (abfd, aouthdr_ext->bss_start);
  aouthdr_int->gp_value   = H_GET_32 (abfd, aouthdr_ext->gp_value);
  aouthdr_int->gprmask    = H_GET_32 (abfd, aouthdr_ext->gprmask);
  aouthdr_int->cprmask[0] = H_GET_32 (abfd, aouthdr_ext->cprmask[0]);
  aouthdr_int->cprmask[1] = H_GET_32 (abfd, aouthdr_ext->cprmask[1]);
  aouthdr_int->cprmask[2] = H_GET_32 (abfd, aouthdr_ext->cprmask[2]);
  aouthdr_int->cprmask[3] = H_GET_32 (abfd, aouthdr_ext->cprmask[3]);
#endif

#ifdef ALPHAECOFF
  aouthdr_int->bss_start = H_GET_64 (abfd, aouthdr_ext->bss_start);
  aouthdr_int->gp_value  = H_GET_64 (abfd, aouthdr_ext->gp_value);
  aouthdr_int->gprmask   = H_GET_32 (abfd, aouthdr_ext->gprmask);
  aouthdr_int->fprmask   = H_GET_32 (abfd, aouthdr_ext->fprmask);
#endif
}