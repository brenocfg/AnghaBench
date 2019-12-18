#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct internal_ldrel {int l_symndx; int /*<<< orphan*/  l_vaddr; } ;
struct internal_ldhdr {int l_nreloc; } ;
typedef  int /*<<< orphan*/  bfd_byte ;
struct TYPE_20__ {int flags; } ;
typedef  TYPE_1__ bfd ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_21__ {int /*<<< orphan*/ ** symbol_ptr_ptr; } ;
typedef  TYPE_2__ asection ;
struct TYPE_22__ {int /*<<< orphan*/  howto; scalar_t__ addend; int /*<<< orphan*/  address; int /*<<< orphan*/ ** sym_ptr_ptr; } ;
typedef  TYPE_3__ arelent ;
struct TYPE_23__ {int /*<<< orphan*/ * contents; } ;

/* Variables and functions */
 int DYNAMIC ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_3__* bfd_alloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bfd_error_bad_value ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 int /*<<< orphan*/  bfd_error_no_symbols ; 
 TYPE_2__* bfd_get_section_by_name (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_xcoff_dynamic_reloc_howto (TYPE_1__*) ; 
 int bfd_xcoff_ldrelsz (TYPE_1__*) ; 
 int bfd_xcoff_loader_reloc_offset (TYPE_1__*,struct internal_ldhdr*) ; 
 int /*<<< orphan*/  bfd_xcoff_swap_ldhdr_in (TYPE_1__*,int /*<<< orphan*/ *,struct internal_ldhdr*) ; 
 int /*<<< orphan*/  bfd_xcoff_swap_ldrel_in (TYPE_1__*,int /*<<< orphan*/ *,struct internal_ldrel*) ; 
 TYPE_6__* coff_section_data (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  xcoff_get_section_contents (TYPE_1__*,TYPE_2__*) ; 

long
_bfd_xcoff_canonicalize_dynamic_reloc (bfd *abfd,
				       arelent **prelocs,
				       asymbol **syms)
{
  asection *lsec;
  bfd_byte *contents;
  struct internal_ldhdr ldhdr;
  arelent *relbuf;
  bfd_byte *elrel, *elrelend;

  if ((abfd->flags & DYNAMIC) == 0)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return -1;
    }

  lsec = bfd_get_section_by_name (abfd, ".loader");
  if (lsec == NULL)
    {
      bfd_set_error (bfd_error_no_symbols);
      return -1;
    }

  if (! xcoff_get_section_contents (abfd, lsec))
    return -1;
  contents = coff_section_data (abfd, lsec)->contents;

  bfd_xcoff_swap_ldhdr_in (abfd, contents, &ldhdr);

  relbuf = bfd_alloc (abfd, ldhdr.l_nreloc * sizeof (arelent));
  if (relbuf == NULL)
    return -1;

  elrel = contents + bfd_xcoff_loader_reloc_offset(abfd, &ldhdr);

  elrelend = elrel + ldhdr.l_nreloc * bfd_xcoff_ldrelsz(abfd);
  for (; elrel < elrelend; elrel += bfd_xcoff_ldrelsz(abfd), relbuf++,
	 prelocs++)
    {
      struct internal_ldrel ldrel;

      bfd_xcoff_swap_ldrel_in (abfd, elrel, &ldrel);

      if (ldrel.l_symndx >= 3)
	relbuf->sym_ptr_ptr = syms + (ldrel.l_symndx - 3);
      else
	{
	  const char *name;
	  asection *sec;

	  switch (ldrel.l_symndx)
	    {
	    case 0:
	      name = ".text";
	      break;
	    case 1:
	      name = ".data";
	      break;
	    case 2:
	      name = ".bss";
	      break;
	    default:
	      abort ();
	      break;
	    }

	  sec = bfd_get_section_by_name (abfd, name);
	  if (sec == NULL)
	    {
	      bfd_set_error (bfd_error_bad_value);
	      return -1;
	    }

	  relbuf->sym_ptr_ptr = sec->symbol_ptr_ptr;
	}

      relbuf->address = ldrel.l_vaddr;
      relbuf->addend = 0;

      /* Most dynamic relocs have the same type.  FIXME: This is only
	 correct if ldrel.l_rtype == 0.  In other cases, we should use
	 a different howto.  */
      relbuf->howto = bfd_xcoff_dynamic_reloc_howto(abfd);

      /* FIXME: We have no way to record the l_rsecnm field.  */

      *prelocs = relbuf;
    }

  *prelocs = NULL;

  return ldhdr.l_nreloc;
}