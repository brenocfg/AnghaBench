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
struct internal_aouthdr {int magic; int vstamp; int o_snentry; int o_sntext; int o_sndata; int o_sntoc; int o_snloader; int o_snbss; int o_algntext; int o_algndata; int o_modtype; int o_cputype; int /*<<< orphan*/  fprmask; int /*<<< orphan*/  gprmask; int /*<<< orphan*/  gp_value; int /*<<< orphan*/  bss_start; int /*<<< orphan*/ * cprmask; int /*<<< orphan*/  o_maxdata; int /*<<< orphan*/  o_maxstack; int /*<<< orphan*/  o_toc; int /*<<< orphan*/  tagentries; int /*<<< orphan*/  data_start; int /*<<< orphan*/  text_start; int /*<<< orphan*/  entry; int /*<<< orphan*/  bsize; int /*<<< orphan*/  dsize; int /*<<< orphan*/  tsize; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/  fprmask; int /*<<< orphan*/  gprmask; int /*<<< orphan*/  gp_value; int /*<<< orphan*/  bss_start; int /*<<< orphan*/  padding; int /*<<< orphan*/  bldrev; int /*<<< orphan*/ * cprmask; int /*<<< orphan*/  o_resv3; int /*<<< orphan*/  o_debugger; int /*<<< orphan*/  o_resv2; int /*<<< orphan*/  o_maxdata; int /*<<< orphan*/  o_maxstack; int /*<<< orphan*/  o_cputype; int /*<<< orphan*/  o_modtype; int /*<<< orphan*/  o_algndata; int /*<<< orphan*/  o_algntext; int /*<<< orphan*/  o_snbss; int /*<<< orphan*/  o_snloader; int /*<<< orphan*/  o_sntoc; int /*<<< orphan*/  o_sndata; int /*<<< orphan*/  o_sntext; int /*<<< orphan*/  o_snentry; int /*<<< orphan*/  o_toc; int /*<<< orphan*/  tagentries; int /*<<< orphan*/  data_start; int /*<<< orphan*/  text_start; int /*<<< orphan*/  entry; int /*<<< orphan*/  bsize; int /*<<< orphan*/  dsize; int /*<<< orphan*/  tsize; int /*<<< orphan*/  vstamp; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ AOUTHDR ;

/* Variables and functions */
 unsigned int AOUTSZ ; 
 int /*<<< orphan*/  H_PUT_16 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_PUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_PUT_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_AOUTHDR_BSIZE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_AOUTHDR_DATA_START (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_AOUTHDR_DSIZE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_AOUTHDR_ENTRY (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_AOUTHDR_TEXT_START (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_AOUTHDR_TSIZE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int
coff_swap_aouthdr_out (bfd * abfd, void * in, void * out)
{
  struct internal_aouthdr *aouthdr_in = (struct internal_aouthdr *) in;
  AOUTHDR *aouthdr_out = (AOUTHDR *) out;

  H_PUT_16 (abfd, aouthdr_in->magic, aouthdr_out->magic);
  H_PUT_16 (abfd, aouthdr_in->vstamp, aouthdr_out->vstamp);
  PUT_AOUTHDR_TSIZE (abfd, aouthdr_in->tsize, aouthdr_out->tsize);
  PUT_AOUTHDR_DSIZE (abfd, aouthdr_in->dsize, aouthdr_out->dsize);
  PUT_AOUTHDR_BSIZE (abfd, aouthdr_in->bsize, aouthdr_out->bsize);
  PUT_AOUTHDR_ENTRY (abfd, aouthdr_in->entry, aouthdr_out->entry);
  PUT_AOUTHDR_TEXT_START (abfd, aouthdr_in->text_start,
			  aouthdr_out->text_start);
  PUT_AOUTHDR_DATA_START (abfd, aouthdr_in->data_start,
			  aouthdr_out->data_start);

#ifdef I960
  H_PUT_32 (abfd, aouthdr_in->tagentries, aouthdr_out->tagentries);
#endif

#ifdef RS6000COFF_C
#ifdef XCOFF64
  H_PUT_64 (abfd, aouthdr_in->o_toc, aouthdr_out->o_toc);
#else
  H_PUT_32 (abfd, aouthdr_in->o_toc, aouthdr_out->o_toc);
#endif
  H_PUT_16 (abfd, aouthdr_in->o_snentry, aouthdr_out->o_snentry);
  H_PUT_16 (abfd, aouthdr_in->o_sntext, aouthdr_out->o_sntext);
  H_PUT_16 (abfd, aouthdr_in->o_sndata, aouthdr_out->o_sndata);
  H_PUT_16 (abfd, aouthdr_in->o_sntoc, aouthdr_out->o_sntoc);
  H_PUT_16 (abfd, aouthdr_in->o_snloader, aouthdr_out->o_snloader);
  H_PUT_16 (abfd, aouthdr_in->o_snbss, aouthdr_out->o_snbss);
  H_PUT_16 (abfd, aouthdr_in->o_algntext, aouthdr_out->o_algntext);
  H_PUT_16 (abfd, aouthdr_in->o_algndata, aouthdr_out->o_algndata);
  H_PUT_16 (abfd, aouthdr_in->o_modtype, aouthdr_out->o_modtype);
  H_PUT_16 (abfd, aouthdr_in->o_cputype, aouthdr_out->o_cputype);
#ifdef XCOFF64
  H_PUT_64 (abfd, aouthdr_in->o_maxstack, aouthdr_out->o_maxstack);
  H_PUT_64 (abfd, aouthdr_in->o_maxdata, aouthdr_out->o_maxdata);
#else
  H_PUT_32 (abfd, aouthdr_in->o_maxstack, aouthdr_out->o_maxstack);
  H_PUT_32 (abfd, aouthdr_in->o_maxdata, aouthdr_out->o_maxdata);
#endif
  memset (aouthdr_out->o_resv2, 0, sizeof aouthdr_out->o_resv2);
#ifdef XCOFF64
  memset (aouthdr_out->o_debugger, 0, sizeof aouthdr_out->o_debugger);
  memset (aouthdr_out->o_resv3, 0, sizeof aouthdr_out->o_resv3);
#endif
#endif

#ifdef MIPSECOFF
  H_PUT_32 (abfd, aouthdr_in->bss_start, aouthdr_out->bss_start);
  H_PUT_32 (abfd, aouthdr_in->gp_value, aouthdr_out->gp_value);
  H_PUT_32 (abfd, aouthdr_in->gprmask, aouthdr_out->gprmask);
  H_PUT_32 (abfd, aouthdr_in->cprmask[0], aouthdr_out->cprmask[0]);
  H_PUT_32 (abfd, aouthdr_in->cprmask[1], aouthdr_out->cprmask[1]);
  H_PUT_32 (abfd, aouthdr_in->cprmask[2], aouthdr_out->cprmask[2]);
  H_PUT_32 (abfd, aouthdr_in->cprmask[3], aouthdr_out->cprmask[3]);
#endif

#ifdef ALPHAECOFF
  /* FIXME: What does bldrev mean?  */
  H_PUT_16 (abfd, 2, aouthdr_out->bldrev);
  H_PUT_16 (abfd, 0, aouthdr_out->padding);
  H_PUT_64 (abfd, aouthdr_in->bss_start, aouthdr_out->bss_start);
  H_PUT_64 (abfd, aouthdr_in->gp_value, aouthdr_out->gp_value);
  H_PUT_32 (abfd, aouthdr_in->gprmask, aouthdr_out->gprmask);
  H_PUT_32 (abfd, aouthdr_in->fprmask, aouthdr_out->fprmask);
#endif

  return AOUTSZ;
}