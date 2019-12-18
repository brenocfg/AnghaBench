#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct hppa_unw_aux_info {int nsyms; char* symtab; int strtab_size; scalar_t__ table_len; int /*<<< orphan*/ * strtab; int /*<<< orphan*/ * table; } ;
typedef  int /*<<< orphan*/  aux ;
struct TYPE_9__ {unsigned long e_shnum; } ;
struct TYPE_8__ {scalar_t__ sh_type; int sh_size; int sh_entsize; scalar_t__ sh_offset; int /*<<< orphan*/  sh_link; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ Elf_Internal_Shdr ;

/* Variables and functions */
 char* GET_ELF_SYMBOLS (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* SECTION_HEADER (int /*<<< orphan*/ ) ; 
 unsigned long SECTION_HEADER_INDEX (int /*<<< orphan*/ ) ; 
 char* SECTION_NAME (TYPE_1__*) ; 
 scalar_t__ SHT_SYMTAB ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  dump_hppa_unwind (struct hppa_unw_aux_info*) ; 
 int eh_addr_size ; 
 TYPE_4__ elf_header ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * get_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int,int,char*) ; 
 int /*<<< orphan*/  memset (struct hppa_unw_aux_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__* section_headers ; 
 int /*<<< orphan*/  slurp_hppa_unwind_table (int /*<<< orphan*/ *,struct hppa_unw_aux_info*,TYPE_1__*) ; 
 scalar_t__ streq (char*,char*) ; 
 int /*<<< orphan*/ * string_table ; 

__attribute__((used)) static int
hppa_process_unwind (FILE *file)
{
  struct hppa_unw_aux_info aux;
  Elf_Internal_Shdr *unwsec = NULL;
  Elf_Internal_Shdr *strsec;
  Elf_Internal_Shdr *sec;
  unsigned long i;

  memset (& aux, 0, sizeof (aux));

  if (string_table == NULL)
    return 1;

  for (i = 0, sec = section_headers; i < elf_header.e_shnum; ++i, ++sec)
    {
      if (sec->sh_type == SHT_SYMTAB
	  && SECTION_HEADER_INDEX (sec->sh_link) < elf_header.e_shnum)
	{
	  aux.nsyms = sec->sh_size / sec->sh_entsize;
	  aux.symtab = GET_ELF_SYMBOLS (file, sec);

	  strsec = SECTION_HEADER (sec->sh_link);
	  aux.strtab = get_data (NULL, file, strsec->sh_offset,
				 1, strsec->sh_size, _("string table"));
	  aux.strtab_size = aux.strtab != NULL ? strsec->sh_size : 0;
	}
      else if (streq (SECTION_NAME (sec), ".PARISC.unwind"))
	unwsec = sec;
    }

  if (!unwsec)
    printf (_("\nThere are no unwind sections in this file.\n"));

  for (i = 0, sec = section_headers; i < elf_header.e_shnum; ++i, ++sec)
    {
      if (streq (SECTION_NAME (sec), ".PARISC.unwind"))
	{
	  printf (_("\nUnwind section "));
	  printf (_("'%s'"), SECTION_NAME (sec));

	  printf (_(" at offset 0x%lx contains %lu entries:\n"),
		  (unsigned long) sec->sh_offset,
		  (unsigned long) (sec->sh_size / (2 * eh_addr_size + 8)));

          slurp_hppa_unwind_table (file, &aux, sec);
	  if (aux.table_len > 0)
	    dump_hppa_unwind (&aux);

	  if (aux.table)
	    free ((char *) aux.table);
	  aux.table = NULL;
	}
    }

  if (aux.symtab)
    free (aux.symtab);
  if (aux.strtab)
    free ((char *) aux.strtab);

  return 1;
}