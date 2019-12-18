#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_11__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/  name; int /*<<< orphan*/  file_offset; } ;
typedef  TYPE_2__ carsym ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_27__ {int flags; scalar_t__ archive_pass; } ;
typedef  TYPE_3__ bfd ;
struct TYPE_30__ {TYPE_1__* s; } ;
struct TYPE_29__ {int sh_size; int sh_info; int /*<<< orphan*/  sh_link; } ;
struct TYPE_28__ {int /*<<< orphan*/  st_name; } ;
struct TYPE_25__ {int sizeof_sym; } ;
struct TYPE_24__ {TYPE_5__ dynsymtab_hdr; TYPE_5__ symtab_hdr; } ;
typedef  TYPE_4__ Elf_Internal_Sym ;
typedef  TYPE_5__ Elf_Internal_Shdr ;

/* Variables and functions */
 int DYNAMIC ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_3__* _bfd_get_elt_at_filepos (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_check_format (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* bfd_elf_get_elf_syms (TYPE_3__*,TYPE_5__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* bfd_elf_string_from_elf_section (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_object ; 
 scalar_t__ elf_bad_symtab (TYPE_3__*) ; 
 scalar_t__ elf_dynsymtab (TYPE_3__*) ; 
 TYPE_11__* elf_tdata (TYPE_3__*) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 TYPE_8__* get_elf_backend_data (TYPE_3__*) ; 
 int /*<<< orphan*/  is_global_data_symbol_definition (TYPE_3__*,TYPE_4__*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
elf_link_is_defined_archive_symbol (bfd * abfd, carsym * symdef)
{
  Elf_Internal_Shdr * hdr;
  bfd_size_type symcount;
  bfd_size_type extsymcount;
  bfd_size_type extsymoff;
  Elf_Internal_Sym *isymbuf;
  Elf_Internal_Sym *isym;
  Elf_Internal_Sym *isymend;
  bfd_boolean result;

  abfd = _bfd_get_elt_at_filepos (abfd, symdef->file_offset);
  if (abfd == NULL)
    return FALSE;

  if (! bfd_check_format (abfd, bfd_object))
    return FALSE;

  /* If we have already included the element containing this symbol in the
     link then we do not need to include it again.  Just claim that any symbol
     it contains is not a definition, so that our caller will not decide to
     (re)include this element.  */
  if (abfd->archive_pass)
    return FALSE;

  /* Select the appropriate symbol table.  */
  if ((abfd->flags & DYNAMIC) == 0 || elf_dynsymtab (abfd) == 0)
    hdr = &elf_tdata (abfd)->symtab_hdr;
  else
    hdr = &elf_tdata (abfd)->dynsymtab_hdr;

  symcount = hdr->sh_size / get_elf_backend_data (abfd)->s->sizeof_sym;

  /* The sh_info field of the symtab header tells us where the
     external symbols start.  We don't care about the local symbols.  */
  if (elf_bad_symtab (abfd))
    {
      extsymcount = symcount;
      extsymoff = 0;
    }
  else
    {
      extsymcount = symcount - hdr->sh_info;
      extsymoff = hdr->sh_info;
    }

  if (extsymcount == 0)
    return FALSE;

  /* Read in the symbol table.  */
  isymbuf = bfd_elf_get_elf_syms (abfd, hdr, extsymcount, extsymoff,
				  NULL, NULL, NULL);
  if (isymbuf == NULL)
    return FALSE;

  /* Scan the symbol table looking for SYMDEF.  */
  result = FALSE;
  for (isym = isymbuf, isymend = isymbuf + extsymcount; isym < isymend; isym++)
    {
      const char *name;

      name = bfd_elf_string_from_elf_section (abfd, hdr->sh_link,
					      isym->st_name);
      if (name == NULL)
	break;

      if (strcmp (name, symdef->name) == 0)
	{
	  result = is_global_data_symbol_definition (abfd, isym);
	  break;
	}
    }

  free (isymbuf);

  return result;
}