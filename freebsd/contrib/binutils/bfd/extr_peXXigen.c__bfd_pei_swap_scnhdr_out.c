#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct internal_scnhdr {int s_vaddr; int s_flags; int s_nlnno; int s_nreloc; int /*<<< orphan*/  s_name; int /*<<< orphan*/  s_lnnoptr; int /*<<< orphan*/  s_relptr; int /*<<< orphan*/  s_scnptr; scalar_t__ s_size; scalar_t__ s_paddr; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_10__ {TYPE_2__* link_info; } ;
struct TYPE_6__ {int ImageBase; } ;
struct TYPE_9__ {TYPE_1__ pe_opthdr; } ;
struct TYPE_8__ {int /*<<< orphan*/  s_flags; int /*<<< orphan*/  s_nreloc; int /*<<< orphan*/  s_nlnno; int /*<<< orphan*/  s_lnnoptr; int /*<<< orphan*/  s_relptr; int /*<<< orphan*/  s_scnptr; int /*<<< orphan*/  s_paddr; int /*<<< orphan*/  s_size; int /*<<< orphan*/  s_vaddr; int /*<<< orphan*/  s_name; } ;
struct TYPE_7__ {int /*<<< orphan*/  shared; int /*<<< orphan*/  relocatable; } ;
typedef  TYPE_3__ SCNHDR ;

/* Variables and functions */
 int /*<<< orphan*/  H_PUT_16 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_PUT_32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int IMAGE_SCN_ALIGN_8BYTES ; 
 int IMAGE_SCN_CNT_CODE ; 
 int IMAGE_SCN_CNT_INITIALIZED_DATA ; 
 int IMAGE_SCN_CNT_UNINITIALIZED_DATA ; 
 int IMAGE_SCN_LNK_NRELOC_OVFL ; 
 int IMAGE_SCN_MEM_DISCARDABLE ; 
 int IMAGE_SCN_MEM_EXECUTE ; 
 int IMAGE_SCN_MEM_READ ; 
 int IMAGE_SCN_MEM_WRITE ; 
 int /*<<< orphan*/  PUT_SCNHDR_LNNOPTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_SCNHDR_PADDR (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_SCNHDR_RELPTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_SCNHDR_SCNPTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_SCNHDR_SIZE (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_SCNHDR_VADDR (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 unsigned int SCNHSZ ; 
 int WP_TEXT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfd_error_file_truncated ; 
 int bfd_get_file_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_pe_executable_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 TYPE_5__* coff_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* pe_data (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

unsigned int
_bfd_XXi_swap_scnhdr_out (bfd * abfd, void * in, void * out)
{
  struct internal_scnhdr *scnhdr_int = (struct internal_scnhdr *) in;
  SCNHDR *scnhdr_ext = (SCNHDR *) out;
  unsigned int ret = SCNHSZ;
  bfd_vma ps;
  bfd_vma ss;

  memcpy (scnhdr_ext->s_name, scnhdr_int->s_name, sizeof (scnhdr_int->s_name));

  PUT_SCNHDR_VADDR (abfd,
		    ((scnhdr_int->s_vaddr
		      - pe_data (abfd)->pe_opthdr.ImageBase)
		     & 0xffffffff),
		    scnhdr_ext->s_vaddr);

  /* NT wants the size data to be rounded up to the next
     NT_FILE_ALIGNMENT, but zero if it has no content (as in .bss,
     sometimes).  */
  if ((scnhdr_int->s_flags & IMAGE_SCN_CNT_UNINITIALIZED_DATA) != 0)
    {
      if (bfd_pe_executable_p (abfd))
	{
	  ps = scnhdr_int->s_size;
	  ss = 0;
	}
      else
       {
         ps = 0;
         ss = scnhdr_int->s_size;
       }
    }
  else
    {
      if (bfd_pe_executable_p (abfd))
	ps = scnhdr_int->s_paddr;
      else
	ps = 0;

      ss = scnhdr_int->s_size;
    }

  PUT_SCNHDR_SIZE (abfd, ss,
		   scnhdr_ext->s_size);

  /* s_paddr in PE is really the virtual size.  */
  PUT_SCNHDR_PADDR (abfd, ps, scnhdr_ext->s_paddr);

  PUT_SCNHDR_SCNPTR (abfd, scnhdr_int->s_scnptr,
		     scnhdr_ext->s_scnptr);
  PUT_SCNHDR_RELPTR (abfd, scnhdr_int->s_relptr,
		     scnhdr_ext->s_relptr);
  PUT_SCNHDR_LNNOPTR (abfd, scnhdr_int->s_lnnoptr,
		      scnhdr_ext->s_lnnoptr);

  {
    /* Extra flags must be set when dealing with PE.  All sections should also
       have the IMAGE_SCN_MEM_READ (0x40000000) flag set.  In addition, the
       .text section must have IMAGE_SCN_MEM_EXECUTE (0x20000000) and the data
       sections (.idata, .data, .bss, .CRT) must have IMAGE_SCN_MEM_WRITE set
       (this is especially important when dealing with the .idata section since
       the addresses for routines from .dlls must be overwritten).  If .reloc
       section data is ever generated, we must add IMAGE_SCN_MEM_DISCARDABLE
       (0x02000000).  Also, the resource data should also be read and
       writable.  */

    /* FIXME: Alignment is also encoded in this field, at least on PPC and 
       ARM-WINCE.  Although - how do we get the original alignment field
       back ?  */

    typedef struct
    {
      const char * 	section_name;
      unsigned long	must_have;
    }
    pe_required_section_flags;
    
    pe_required_section_flags known_sections [] =
      {
	{ ".arch",  IMAGE_SCN_MEM_READ | IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_DISCARDABLE | IMAGE_SCN_ALIGN_8BYTES },
	{ ".bss",   IMAGE_SCN_MEM_READ | IMAGE_SCN_CNT_UNINITIALIZED_DATA | IMAGE_SCN_MEM_WRITE },
	{ ".data",  IMAGE_SCN_MEM_READ | IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_WRITE },
	{ ".edata", IMAGE_SCN_MEM_READ | IMAGE_SCN_CNT_INITIALIZED_DATA },
	{ ".idata", IMAGE_SCN_MEM_READ | IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_WRITE },
	{ ".pdata", IMAGE_SCN_MEM_READ | IMAGE_SCN_CNT_INITIALIZED_DATA },
	{ ".rdata", IMAGE_SCN_MEM_READ | IMAGE_SCN_CNT_INITIALIZED_DATA },
	{ ".reloc", IMAGE_SCN_MEM_READ | IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_DISCARDABLE },
	{ ".rsrc",  IMAGE_SCN_MEM_READ | IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_WRITE },
	{ ".text" , IMAGE_SCN_MEM_READ | IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_EXECUTE },
	{ ".tls",   IMAGE_SCN_MEM_READ | IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_WRITE },
	{ ".xdata", IMAGE_SCN_MEM_READ | IMAGE_SCN_CNT_INITIALIZED_DATA },
	{ NULL, 0}
      };

    pe_required_section_flags * p;

    /* We have defaulted to adding the IMAGE_SCN_MEM_WRITE flag, but now
       we know exactly what this specific section wants so we remove it
       and then allow the must_have field to add it back in if necessary.
       However, we don't remove IMAGE_SCN_MEM_WRITE flag from .text if the
       default WP_TEXT file flag has been cleared.  WP_TEXT may be cleared
       by ld --enable-auto-import (if auto-import is actually needed),
       by ld --omagic, or by obcopy --writable-text.  */

    for (p = known_sections; p->section_name; p++)
      if (strcmp (scnhdr_int->s_name, p->section_name) == 0)
	{
	  if (strcmp (scnhdr_int->s_name, ".text")
	      || (bfd_get_file_flags (abfd) & WP_TEXT))
	    scnhdr_int->s_flags &= ~IMAGE_SCN_MEM_WRITE;
	  scnhdr_int->s_flags |= p->must_have;
	  break;
	}

    H_PUT_32 (abfd, scnhdr_int->s_flags, scnhdr_ext->s_flags);
  }

  if (coff_data (abfd)->link_info
      && ! coff_data (abfd)->link_info->relocatable
      && ! coff_data (abfd)->link_info->shared
      && strcmp (scnhdr_int->s_name, ".text") == 0)
    {
      /* By inference from looking at MS output, the 32 bit field
	 which is the combination of the number_of_relocs and
	 number_of_linenos is used for the line number count in
	 executables.  A 16-bit field won't do for cc1.  The MS
	 document says that the number of relocs is zero for
	 executables, but the 17-th bit has been observed to be there.
	 Overflow is not an issue: a 4G-line program will overflow a
	 bunch of other fields long before this!  */
      H_PUT_16 (abfd, (scnhdr_int->s_nlnno & 0xffff), scnhdr_ext->s_nlnno);
      H_PUT_16 (abfd, (scnhdr_int->s_nlnno >> 16), scnhdr_ext->s_nreloc);
    }
  else
    {
      if (scnhdr_int->s_nlnno <= 0xffff)
	H_PUT_16 (abfd, scnhdr_int->s_nlnno, scnhdr_ext->s_nlnno);
      else
	{
	  (*_bfd_error_handler) (_("%s: line number overflow: 0x%lx > 0xffff"),
				 bfd_get_filename (abfd),
				 scnhdr_int->s_nlnno);
	  bfd_set_error (bfd_error_file_truncated);
	  H_PUT_16 (abfd, 0xffff, scnhdr_ext->s_nlnno);
	  ret = 0;
	}

      /* Although we could encode 0xffff relocs here, we do not, to be
         consistent with other parts of bfd. Also it lets us warn, as
         we should never see 0xffff here w/o having the overflow flag
         set.  */
      if (scnhdr_int->s_nreloc < 0xffff)
	H_PUT_16 (abfd, scnhdr_int->s_nreloc, scnhdr_ext->s_nreloc);
      else
	{
	  /* PE can deal with large #s of relocs, but not here.  */
	  H_PUT_16 (abfd, 0xffff, scnhdr_ext->s_nreloc);
	  scnhdr_int->s_flags |= IMAGE_SCN_LNK_NRELOC_OVFL;
	  H_PUT_32 (abfd, scnhdr_int->s_flags, scnhdr_ext->s_flags);
	}
    }
  return ret;
}