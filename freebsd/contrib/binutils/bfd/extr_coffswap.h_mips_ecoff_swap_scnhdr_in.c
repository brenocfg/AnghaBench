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
struct internal_scnhdr {int /*<<< orphan*/  s_align; int /*<<< orphan*/  s_nlnno; int /*<<< orphan*/  s_nreloc; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  s_lnnoptr; int /*<<< orphan*/  s_relptr; int /*<<< orphan*/  s_scnptr; int /*<<< orphan*/  s_size; int /*<<< orphan*/  s_paddr; int /*<<< orphan*/  s_vaddr; int /*<<< orphan*/  s_name; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/  s_align; int /*<<< orphan*/  s_nlnno; int /*<<< orphan*/  s_nreloc; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  s_lnnoptr; int /*<<< orphan*/  s_relptr; int /*<<< orphan*/  s_scnptr; int /*<<< orphan*/  s_size; int /*<<< orphan*/  s_paddr; int /*<<< orphan*/  s_vaddr; int /*<<< orphan*/  s_name; } ;
typedef  TYPE_1__ SCNHDR ;

/* Variables and functions */
 int /*<<< orphan*/  COFF_ADJUST_SCNHDR_IN_POST (int /*<<< orphan*/ *,void*,void*) ; 
 int /*<<< orphan*/  COFF_ADJUST_SCNHDR_IN_PRE (int /*<<< orphan*/ *,void*,void*) ; 
 int /*<<< orphan*/  GET_SCNHDR_ALIGN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_SCNHDR_FLAGS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_SCNHDR_LNNOPTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_SCNHDR_NLNNO (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_SCNHDR_NRELOC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_SCNHDR_PADDR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_SCNHDR_RELPTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_SCNHDR_SCNPTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_SCNHDR_SIZE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_SCNHDR_VADDR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
coff_swap_scnhdr_in (bfd * abfd, void * ext, void * in)
{
  SCNHDR *scnhdr_ext = (SCNHDR *) ext;
  struct internal_scnhdr *scnhdr_int = (struct internal_scnhdr *) in;

#ifdef COFF_ADJUST_SCNHDR_IN_PRE
  COFF_ADJUST_SCNHDR_IN_PRE (abfd, ext, in);
#endif
  memcpy (scnhdr_int->s_name, scnhdr_ext->s_name, sizeof (scnhdr_int->s_name));

  scnhdr_int->s_vaddr = GET_SCNHDR_VADDR (abfd, scnhdr_ext->s_vaddr);
  scnhdr_int->s_paddr = GET_SCNHDR_PADDR (abfd, scnhdr_ext->s_paddr);
  scnhdr_int->s_size = GET_SCNHDR_SIZE (abfd, scnhdr_ext->s_size);

  scnhdr_int->s_scnptr = GET_SCNHDR_SCNPTR (abfd, scnhdr_ext->s_scnptr);
  scnhdr_int->s_relptr = GET_SCNHDR_RELPTR (abfd, scnhdr_ext->s_relptr);
  scnhdr_int->s_lnnoptr = GET_SCNHDR_LNNOPTR (abfd, scnhdr_ext->s_lnnoptr);
  scnhdr_int->s_flags = GET_SCNHDR_FLAGS (abfd, scnhdr_ext->s_flags);
  scnhdr_int->s_nreloc = GET_SCNHDR_NRELOC (abfd, scnhdr_ext->s_nreloc);
  scnhdr_int->s_nlnno = GET_SCNHDR_NLNNO (abfd, scnhdr_ext->s_nlnno);
#ifdef I960
  scnhdr_int->s_align = GET_SCNHDR_ALIGN (abfd, scnhdr_ext->s_align);
#endif
#ifdef COFF_ADJUST_SCNHDR_IN_POST
  COFF_ADJUST_SCNHDR_IN_POST (abfd, ext, in);
#endif
}