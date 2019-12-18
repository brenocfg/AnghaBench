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
struct stab_section_info {char* filename; scalar_t__ found; int num_sections; int /*<<< orphan*/ * sections; struct stab_section_info* next; } ;
struct section_offsets {int /*<<< orphan*/ * offsets; } ;
struct partial_symtab {char* filename; struct section_offsets* section_offsets; } ;
struct objfile {int /*<<< orphan*/  num_sections; int /*<<< orphan*/  objfile_obstack; struct dbx_symfile_info* sym_stab_info; } ;
struct dbx_symfile_info {struct stab_section_info* stab_section_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIZEOF_N_SECTION_OFFSETS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  symfile_complaints ; 

void
elfstab_offset_sections (struct objfile *objfile, struct partial_symtab *pst)
{
  char *filename = pst->filename;
  struct dbx_symfile_info *dbx = objfile->sym_stab_info;
  struct stab_section_info *maybe = dbx->stab_section_info;
  struct stab_section_info *questionable = 0;
  int i;
  char *p;

  /* The ELF symbol info doesn't include path names, so strip the path
     (if any) from the psymtab filename.  */
  while (0 != (p = strchr (filename, '/')))
    filename = p + 1;

  /* FIXME:  This linear search could speed up significantly
     if it was chained in the right order to match how we search it,
     and if we unchained when we found a match. */
  for (; maybe; maybe = maybe->next)
    {
      if (filename[0] == maybe->filename[0]
	  && strcmp (filename, maybe->filename) == 0)
	{
	  /* We found a match.  But there might be several source files
	     (from different directories) with the same name.  */
	  if (0 == maybe->found)
	    break;
	  questionable = maybe;	/* Might use it later.  */
	}
    }

  if (maybe == 0 && questionable != 0)
    {
      complaint (&symfile_complaints,
		 "elf/stab section information questionable for %s", filename);
      maybe = questionable;
    }

  if (maybe)
    {
      /* Found it!  Allocate a new psymtab struct, and fill it in.  */
      maybe->found++;
      pst->section_offsets = (struct section_offsets *)
	obstack_alloc (&objfile->objfile_obstack, 
		       SIZEOF_N_SECTION_OFFSETS (objfile->num_sections));
      for (i = 0; i < maybe->num_sections; i++)
	(pst->section_offsets)->offsets[i] = maybe->sections[i];
      return;
    }

  /* We were unable to find any offsets for this file.  Complain.  */
  if (dbx->stab_section_info)	/* If there *is* any info, */
    complaint (&symfile_complaints,
	       "elf/stab section information missing for %s", filename);
}