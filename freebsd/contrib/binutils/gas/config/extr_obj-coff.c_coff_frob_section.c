#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolS ;
typedef  TYPE_2__* segT ;
struct TYPE_16__ {int fr_address; int fr_fix; char* fr_literal; struct TYPE_16__* fr_next; int /*<<< orphan*/  fr_offset; } ;
typedef  TYPE_3__ fragS ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
struct TYPE_17__ {TYPE_1__* frchainP; } ;
struct TYPE_15__ {int /*<<< orphan*/  name; scalar_t__ alignment_power; } ;
struct TYPE_14__ {TYPE_3__* frch_root; TYPE_3__* frch_last; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_STAT ; 
 int OCTETS_PER_BYTE_POWER ; 
 int /*<<< orphan*/  SA_SET_SCN_SCNLEN (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SF_SET_STATICS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAB_SECTION_NAME ; 
 int /*<<< orphan*/  STAB_STRING_SECTION_NAME ; 
 int /*<<< orphan*/  S_SET_NUMBER_AUXILIARY (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  S_SET_STORAGE_CLASS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int bfd_get_section_size (TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_h_put_16 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_h_put_32 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_set_section_size (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 TYPE_2__* bss_section ; 
 TYPE_2__* data_section ; 
 int /*<<< orphan*/ * section_symbol (TYPE_2__*) ; 
 TYPE_6__* seg_info (TYPE_2__*) ; 
 int /*<<< orphan*/  stdoutput ; 
 int /*<<< orphan*/  streq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* subseg_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* text_section ; 

void
coff_frob_section (segT sec)
{
  segT strsec;
  char *p;
  fragS *fragp;
  bfd_vma size, n_entries, mask;
  bfd_vma align_power = (bfd_vma)sec->alignment_power + OCTETS_PER_BYTE_POWER;

  /* The COFF back end in BFD requires that all section sizes be
     rounded up to multiples of the corresponding section alignments,
     supposedly because standard COFF has no other way of encoding alignment
     for sections.  If your COFF flavor has a different way of encoding
     section alignment, then skip this step, as TICOFF does.  */
  size = bfd_get_section_size (sec);
  mask = ((bfd_vma) 1 << align_power) - 1;
#if !defined(TICOFF)
  if (size & mask)
    {
      bfd_vma new_size;
      fragS *last;

      new_size = (size + mask) & ~mask;
      bfd_set_section_size (stdoutput, sec, new_size);

      /* If the size had to be rounded up, add some padding in
         the last non-empty frag.  */
      fragp = seg_info (sec)->frchainP->frch_root;
      last = seg_info (sec)->frchainP->frch_last;
      while (fragp->fr_next != last)
	fragp = fragp->fr_next;
      last->fr_address = size;
      fragp->fr_offset += new_size - size;
    }
#endif

  /* If the section size is non-zero, the section symbol needs an aux
     entry associated with it, indicating the size.  We don't know
     all the values yet; coff_frob_symbol will fill them in later.  */
#ifndef TICOFF
  if (size != 0
      || sec == text_section
      || sec == data_section
      || sec == bss_section)
#endif
    {
      symbolS *secsym = section_symbol (sec);

      S_SET_STORAGE_CLASS (secsym, C_STAT);
      S_SET_NUMBER_AUXILIARY (secsym, 1);
      SF_SET_STATICS (secsym);
      SA_SET_SCN_SCNLEN (secsym, size);
    }

  /* FIXME: These should be in a "stabs.h" file, or maybe as.h.  */
#ifndef STAB_SECTION_NAME
#define STAB_SECTION_NAME ".stab"
#endif
#ifndef STAB_STRING_SECTION_NAME
#define STAB_STRING_SECTION_NAME ".stabstr"
#endif
  if (! streq (STAB_STRING_SECTION_NAME, sec->name))
    return;

  strsec = sec;
  sec = subseg_get (STAB_SECTION_NAME, 0);
  /* size is already rounded up, since other section will be listed first */
  size = bfd_get_section_size (strsec);

  n_entries = bfd_get_section_size (sec) / 12 - 1;

  /* Find first non-empty frag.  It should be large enough.  */
  fragp = seg_info (sec)->frchainP->frch_root;
  while (fragp && fragp->fr_fix == 0)
    fragp = fragp->fr_next;
  assert (fragp != 0 && fragp->fr_fix >= 12);

  /* Store the values.  */
  p = fragp->fr_literal;
  bfd_h_put_16 (stdoutput, n_entries, (bfd_byte *) p + 6);
  bfd_h_put_32 (stdoutput, size, (bfd_byte *) p + 8);
}