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
struct internal_scnhdr {scalar_t__ s_nlnno; scalar_t__ s_nreloc; int /*<<< orphan*/  s_align; int /*<<< orphan*/  s_name; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  s_lnnoptr; int /*<<< orphan*/  s_relptr; int /*<<< orphan*/  s_scnptr; int /*<<< orphan*/  s_size; int /*<<< orphan*/  s_paddr; int /*<<< orphan*/  s_vaddr; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {char* s_name; int /*<<< orphan*/  s_align; int /*<<< orphan*/  s_nreloc; int /*<<< orphan*/  s_nlnno; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  s_lnnoptr; int /*<<< orphan*/  s_relptr; int /*<<< orphan*/  s_scnptr; int /*<<< orphan*/  s_size; int /*<<< orphan*/  s_paddr; int /*<<< orphan*/  s_vaddr; } ;
typedef  TYPE_1__ SCNHDR ;

/* Variables and functions */
 int /*<<< orphan*/  COFF_ADJUST_SCNHDR_OUT_POST (int /*<<< orphan*/ *,void*,void*) ; 
 int /*<<< orphan*/  COFF_ADJUST_SCNHDR_OUT_PRE (int /*<<< orphan*/ *,void*,void*) ; 
 int /*<<< orphan*/  H_PUT_32 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_SCNHDR_NLNNO ; 
 scalar_t__ MAX_SCNHDR_NRELOC ; 
 int /*<<< orphan*/  PUT_SCNHDR_ALIGN (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_SCNHDR_FLAGS (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_SCNHDR_LNNOPTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_SCNHDR_NLNNO (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_SCNHDR_NRELOC (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_SCNHDR_PADDR (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_SCNHDR_RELPTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_SCNHDR_SCNPTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_SCNHDR_SIZE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_SCNHDR_VADDR (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 unsigned int bfd_coff_scnhsz (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_error_file_truncated ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static unsigned int
coff_swap_scnhdr_out (bfd * abfd, void * in, void * out)
{
  struct internal_scnhdr *scnhdr_int = (struct internal_scnhdr *) in;
  SCNHDR *scnhdr_ext = (SCNHDR *) out;
  unsigned int ret = bfd_coff_scnhsz (abfd);

#ifdef COFF_ADJUST_SCNHDR_OUT_PRE
  COFF_ADJUST_SCNHDR_OUT_PRE (abfd, in, out);
#endif
  memcpy (scnhdr_ext->s_name, scnhdr_int->s_name, sizeof (scnhdr_int->s_name));

  PUT_SCNHDR_VADDR (abfd, scnhdr_int->s_vaddr, scnhdr_ext->s_vaddr);
  PUT_SCNHDR_PADDR (abfd, scnhdr_int->s_paddr, scnhdr_ext->s_paddr);
  PUT_SCNHDR_SIZE (abfd, scnhdr_int->s_size, scnhdr_ext->s_size);
  PUT_SCNHDR_SCNPTR (abfd, scnhdr_int->s_scnptr, scnhdr_ext->s_scnptr);
  PUT_SCNHDR_RELPTR (abfd, scnhdr_int->s_relptr, scnhdr_ext->s_relptr);
  PUT_SCNHDR_LNNOPTR (abfd, scnhdr_int->s_lnnoptr, scnhdr_ext->s_lnnoptr);
  PUT_SCNHDR_FLAGS (abfd, scnhdr_int->s_flags, scnhdr_ext->s_flags);
#if defined(M88)
  H_PUT_32 (abfd, scnhdr_int->s_nlnno, scnhdr_ext->s_nlnno);
  H_PUT_32 (abfd, scnhdr_int->s_nreloc, scnhdr_ext->s_nreloc);
#else
  if (scnhdr_int->s_nlnno <= MAX_SCNHDR_NLNNO)
    PUT_SCNHDR_NLNNO (abfd, scnhdr_int->s_nlnno, scnhdr_ext->s_nlnno);
  else
    {
      char buf[sizeof (scnhdr_int->s_name) + 1];

      memcpy (buf, scnhdr_int->s_name, sizeof (scnhdr_int->s_name));
      buf[sizeof (scnhdr_int->s_name)] = '\0';
      (*_bfd_error_handler)
	(_("%s: warning: %s: line number overflow: 0x%lx > 0xffff"),
	 bfd_get_filename (abfd),
	 buf, scnhdr_int->s_nlnno);
      PUT_SCNHDR_NLNNO (abfd, 0xffff, scnhdr_ext->s_nlnno);
    }

  if (scnhdr_int->s_nreloc <= MAX_SCNHDR_NRELOC)
    PUT_SCNHDR_NRELOC (abfd, scnhdr_int->s_nreloc, scnhdr_ext->s_nreloc);
  else
    {
      char buf[sizeof (scnhdr_int->s_name) + 1];

      memcpy (buf, scnhdr_int->s_name, sizeof (scnhdr_int->s_name));
      buf[sizeof (scnhdr_int->s_name)] = '\0';
      (*_bfd_error_handler) (_("%s: %s: reloc overflow: 0x%lx > 0xffff"),
			     bfd_get_filename (abfd),
			     buf, scnhdr_int->s_nreloc);
      bfd_set_error (bfd_error_file_truncated);
      PUT_SCNHDR_NRELOC (abfd, 0xffff, scnhdr_ext->s_nreloc);
      ret = 0;
    }
#endif

#ifdef I960
  PUT_SCNHDR_ALIGN (abfd, scnhdr_int->s_align, scnhdr_ext->s_align);
#endif
#ifdef COFF_ADJUST_SCNHDR_OUT_POST
  COFF_ADJUST_SCNHDR_OUT_POST (abfd, in, out);
#endif
  return ret;
}