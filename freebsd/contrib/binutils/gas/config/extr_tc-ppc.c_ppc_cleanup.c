#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int valueT ;
typedef  scalar_t__ subsegT ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int SEC_HAS_CONTENTS ; 
 int SEC_READONLY ; 
 int /*<<< orphan*/  bfd_set_section_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  frag_align (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* frag_more (int) ; 
 int /*<<< orphan*/  md_number_to_chars (char*,int,int) ; 
 int /*<<< orphan*/ * now_seg ; 
 scalar_t__ now_subseg ; 
 scalar_t__* ppc_apuinfo_list ; 
 unsigned int ppc_apuinfo_num ; 
 int /*<<< orphan*/  stdoutput ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/ * subseg_new (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subseg_set (int /*<<< orphan*/ *,scalar_t__) ; 

void
ppc_cleanup (void)
{
#ifdef OBJ_ELF
  if (ppc_apuinfo_list == NULL)
    return;

  /* Ok, so write the section info out.  We have this layout:

  byte	data		what
  ----	----		----
  0	8		length of "APUinfo\0"
  4	(n*4)		number of APU's (4 bytes each)
  8	2		note type 2
  12	"APUinfo\0"	name
  20	APU#1		first APU's info
  24	APU#2		second APU's info
  ...	...
  */
  {
    char *p;
    asection *seg = now_seg;
    subsegT subseg = now_subseg;
    asection *apuinfo_secp = (asection *) NULL;
    unsigned int i;

    /* Create the .PPC.EMB.apuinfo section.  */
    apuinfo_secp = subseg_new (".PPC.EMB.apuinfo", 0);
    bfd_set_section_flags (stdoutput,
			   apuinfo_secp,
			   SEC_HAS_CONTENTS | SEC_READONLY);

    p = frag_more (4);
    md_number_to_chars (p, (valueT) 8, 4);

    p = frag_more (4);
    md_number_to_chars (p, (valueT) ppc_apuinfo_num * 4, 4);

    p = frag_more (4);
    md_number_to_chars (p, (valueT) 2, 4);

    p = frag_more (8);
    strcpy (p, "APUinfo");

    for (i = 0; i < ppc_apuinfo_num; i++)
      {
	p = frag_more (4);
	md_number_to_chars (p, (valueT) ppc_apuinfo_list[i], 4);
      }

    frag_align (2, 0, 0);

    /* We probably can't restore the current segment, for there likely
       isn't one yet...  */
    if (seg && subseg)
      subseg_set (seg, subseg);
  }
#endif
}