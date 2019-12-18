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
struct objfile {int sect_index_text; int sect_index_data; int sect_index_bss; int sect_index_rodata; int flags; struct objfile* next; int /*<<< orphan*/ * cp_namespace_symtab; int /*<<< orphan*/ * md; int /*<<< orphan*/ * name; int /*<<< orphan*/  mtime; int /*<<< orphan*/ * obfd; int /*<<< orphan*/  objfile_obstack; void* macro_cache; void* psymbol_cache; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 void* bcache_xmalloc () ; 
 char* bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 char* bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_mtime (int /*<<< orphan*/ *) ; 
 scalar_t__ build_objfile_section_table (struct objfile*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (struct objfile*,int /*<<< orphan*/ ,int) ; 
 void* mstrsave (int /*<<< orphan*/ *,char*) ; 
 struct objfile* object_files ; 
 int /*<<< orphan*/  objfile_alloc_data (struct objfile*) ; 
 int /*<<< orphan*/  obstack_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  terminate_minimal_symbol_table (struct objfile*) ; 
 scalar_t__ xmalloc (int) ; 
 int /*<<< orphan*/  xmfree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct objfile *
allocate_objfile (bfd *abfd, int flags)
{
  struct objfile *objfile = NULL;
  struct objfile *last_one = NULL;

  /* If we don't support mapped symbol files, didn't ask for the file to be
     mapped, or failed to open the mapped file for some reason, then revert
     back to an unmapped objfile. */

  if (objfile == NULL)
    {
      objfile = (struct objfile *) xmalloc (sizeof (struct objfile));
      memset (objfile, 0, sizeof (struct objfile));
      objfile->md = NULL;
      objfile->psymbol_cache = bcache_xmalloc ();
      objfile->macro_cache = bcache_xmalloc ();
      /* We could use obstack_specify_allocation here instead, but
	 gdb_obstack.h specifies the alloc/dealloc functions.  */
      obstack_init (&objfile->objfile_obstack);
      terminate_minimal_symbol_table (objfile);
    }

  objfile_alloc_data (objfile);

  /* Update the per-objfile information that comes from the bfd, ensuring
     that any data that is reference is saved in the per-objfile data
     region. */

  objfile->obfd = abfd;
  if (objfile->name != NULL)
    {
      xmfree (objfile->md, objfile->name);
    }
  if (abfd != NULL)
    {
      objfile->name = mstrsave (objfile->md, bfd_get_filename (abfd));
      objfile->mtime = bfd_get_mtime (abfd);

      /* Build section table.  */

      if (build_objfile_section_table (objfile))
	{
	  error ("Can't find the file sections in `%s': %s",
		 objfile->name, bfd_errmsg (bfd_get_error ()));
	}
    }
  else
    {
      objfile->name = mstrsave (objfile->md, "<<anonymous objfile>>");
    }

  /* Initialize the section indexes for this objfile, so that we can
     later detect if they are used w/o being properly assigned to. */

  objfile->sect_index_text = -1;
  objfile->sect_index_data = -1;
  objfile->sect_index_bss = -1;
  objfile->sect_index_rodata = -1;

  /* We don't yet have a C++-specific namespace symtab.  */

  objfile->cp_namespace_symtab = NULL;

  /* Add this file onto the tail of the linked list of other such files. */

  objfile->next = NULL;
  if (object_files == NULL)
    object_files = objfile;
  else
    {
      for (last_one = object_files;
	   last_one->next;
	   last_one = last_one->next);
      last_one->next = objfile;
    }

  /* Save passed in flag bits. */
  objfile->flags |= flags;

  return (objfile);
}