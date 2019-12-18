#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  shndx ;
struct TYPE_15__ {unsigned long sh_link; unsigned long sh_size; int /*<<< orphan*/  sh_offset; } ;
struct TYPE_14__ {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_value; int /*<<< orphan*/  st_shndx; int /*<<< orphan*/  st_other; int /*<<< orphan*/  st_info; int /*<<< orphan*/  st_name; } ;
struct TYPE_13__ {unsigned long sh_size; unsigned long sh_entsize; int /*<<< orphan*/  sh_offset; } ;
struct TYPE_12__ {scalar_t__ st_shndx; void* st_size; void* st_value; void* st_other; void* st_info; void* st_name; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ Elf_Internal_Sym ;
typedef  TYPE_2__ Elf_Internal_Shdr ;
typedef  TYPE_3__ Elf_External_Sym_Shndx ;
typedef  TYPE_3__ Elf64_External_Sym ;

/* Variables and functions */
 void* BYTE_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ SECTION_HEADER_NUM (TYPE_2__*) ; 
 scalar_t__ SHN_XINDEX ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ byte_get (unsigned char*,int) ; 
 TYPE_1__* cmalloc (unsigned long,int) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 TYPE_3__* get_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned long,int /*<<< orphan*/ ) ; 
 int section_headers ; 
 TYPE_5__* symtab_shndx_hdr ; 

__attribute__((used)) static Elf_Internal_Sym *
get_64bit_elf_symbols (FILE *file, Elf_Internal_Shdr *section)
{
  unsigned long number;
  Elf64_External_Sym *esyms;
  Elf_External_Sym_Shndx *shndx;
  Elf_Internal_Sym *isyms;
  Elf_Internal_Sym *psym;
  unsigned int j;

  esyms = get_data (NULL, file, section->sh_offset, 1, section->sh_size,
		    _("symbols"));
  if (!esyms)
    return NULL;

  shndx = NULL;
  if (symtab_shndx_hdr != NULL
      && (symtab_shndx_hdr->sh_link
	  == (unsigned long) SECTION_HEADER_NUM (section - section_headers)))
    {
      shndx = get_data (NULL, file, symtab_shndx_hdr->sh_offset,
			1, symtab_shndx_hdr->sh_size, _("symtab shndx"));
      if (!shndx)
	{
	  free (esyms);
	  return NULL;
	}
    }

  number = section->sh_size / section->sh_entsize;
  isyms = cmalloc (number, sizeof (Elf_Internal_Sym));

  if (isyms == NULL)
    {
      error (_("Out of memory\n"));
      if (shndx)
	free (shndx);
      free (esyms);
      return NULL;
    }

  for (j = 0, psym = isyms;
       j < number;
       j++, psym++)
    {
      psym->st_name  = BYTE_GET (esyms[j].st_name);
      psym->st_info  = BYTE_GET (esyms[j].st_info);
      psym->st_other = BYTE_GET (esyms[j].st_other);
      psym->st_shndx = BYTE_GET (esyms[j].st_shndx);
      if (psym->st_shndx == SHN_XINDEX && shndx != NULL)
	psym->st_shndx
	  = byte_get ((unsigned char *) &shndx[j], sizeof (shndx[j]));
      psym->st_value = BYTE_GET (esyms[j].st_value);
      psym->st_size  = BYTE_GET (esyms[j].st_size);
    }

  if (shndx)
    free (shndx);
  free (esyms);

  return isyms;
}