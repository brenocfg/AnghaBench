#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  r_info; int /*<<< orphan*/  r_offset; } ;
struct TYPE_8__ {scalar_t__ r_addend; void* r_info; void* r_offset; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ Elf_Internal_Rela ;
typedef  TYPE_2__ Elf64_External_Rel ;
typedef  TYPE_2__ Elf32_External_Rel ;

/* Variables and functions */
 void* BYTE_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* cmalloc (unsigned long,int) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* get_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long,int,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ is_32bit_elf ; 

__attribute__((used)) static int
slurp_rel_relocs (FILE *file,
		  unsigned long rel_offset,
		  unsigned long rel_size,
		  Elf_Internal_Rela **relsp,
		  unsigned long *nrelsp)
{
  Elf_Internal_Rela *rels;
  unsigned long nrels;
  unsigned int i;

  if (is_32bit_elf)
    {
      Elf32_External_Rel *erels;

      erels = get_data (NULL, file, rel_offset, 1, rel_size, _("relocs"));
      if (!erels)
	return 0;

      nrels = rel_size / sizeof (Elf32_External_Rel);

      rels = cmalloc (nrels, sizeof (Elf_Internal_Rela));

      if (rels == NULL)
	{
	  free (erels);
	  error (_("out of memory parsing relocs\n"));
	  return 0;
	}

      for (i = 0; i < nrels; i++)
	{
	  rels[i].r_offset = BYTE_GET (erels[i].r_offset);
	  rels[i].r_info   = BYTE_GET (erels[i].r_info);
	  rels[i].r_addend = 0;
	}

      free (erels);
    }
  else
    {
      Elf64_External_Rel *erels;

      erels = get_data (NULL, file, rel_offset, 1, rel_size, _("relocs"));
      if (!erels)
	return 0;

      nrels = rel_size / sizeof (Elf64_External_Rel);

      rels = cmalloc (nrels, sizeof (Elf_Internal_Rela));

      if (rels == NULL)
	{
	  free (erels);
	  error (_("out of memory parsing relocs\n"));
	  return 0;
	}

      for (i = 0; i < nrels; i++)
	{
	  rels[i].r_offset = BYTE_GET (erels[i].r_offset);
	  rels[i].r_info   = BYTE_GET (erels[i].r_info);
	  rels[i].r_addend = 0;
	}

      free (erels);
    }
  *relsp = rels;
  *nrelsp = nrels;
  return 1;
}