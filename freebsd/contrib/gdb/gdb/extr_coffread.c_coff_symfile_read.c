#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
struct objfile {TYPE_2__* obfd; struct dbx_symfile_info* sym_stab_info; scalar_t__ sym_private; } ;
struct dbx_symfile_info {int dummy; } ;
struct coff_symfile_info {TYPE_11__* stabstrsect; scalar_t__ stabsects; int /*<<< orphan*/  textsize; int /*<<< orphan*/  textaddr; scalar_t__ min_lineno_offset; scalar_t__ max_lineno_offset; } ;
struct cleanup {int dummy; } ;
struct TYPE_17__ {int sym_filepos; unsigned int local_symesz; scalar_t__ local_auxesz; int /*<<< orphan*/  local_linesz; int /*<<< orphan*/  local_n_tshift; int /*<<< orphan*/  local_n_tmask; int /*<<< orphan*/  local_n_btshft; int /*<<< orphan*/  local_n_btmask; } ;
typedef  TYPE_1__ coff_data_type ;
struct TYPE_18__ {int /*<<< orphan*/  where; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_16__ {int /*<<< orphan*/  filepos; } ;

/* Variables and functions */
 char* bfd_get_filename (TYPE_2__*) ; 
 unsigned int bfd_get_symcount (TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_get_target (TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_map_over_sections (TYPE_2__*,int /*<<< orphan*/ ,void*) ; 
 int bfd_section_size (TYPE_2__*,TYPE_11__*) ; 
 int /*<<< orphan*/  bfd_seek (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* coff_data (TYPE_2__*) ; 
 int /*<<< orphan*/  coff_locate_sections ; 
 int /*<<< orphan*/  coff_symtab_read (long,unsigned int,struct objfile*) ; 
 int /*<<< orphan*/  coffstab_build_psymtabs (struct objfile*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  dwarf2_build_psymtabs (struct objfile*,int) ; 
 scalar_t__ dwarf2_has_info (TYPE_2__*) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  find_linenos ; 
 int /*<<< orphan*/  free_current_contents ; 
 int /*<<< orphan*/  free_linetab_cleanup ; 
 int /*<<< orphan*/  free_stringtab_cleanup ; 
 int init_lineno (TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  init_minimal_symbol_collection () ; 
 int init_stringtab (TYPE_2__*,int) ; 
 int /*<<< orphan*/  install_minimal_symbols (struct objfile*) ; 
 scalar_t__ local_auxesz ; 
 int /*<<< orphan*/  local_linesz ; 
 int /*<<< orphan*/  local_n_btmask ; 
 int /*<<< orphan*/  local_n_btshft ; 
 int /*<<< orphan*/  local_n_tmask ; 
 int /*<<< orphan*/  local_n_tshift ; 
 unsigned int local_symesz ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char**) ; 
 struct cleanup* make_cleanup_discard_minimal_symbols () ; 
 int pe_file ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__* symfile_bfd ; 
 char* temp_aux ; 
 char* temp_sym ; 
 scalar_t__ xmalloc (scalar_t__) ; 

__attribute__((used)) static void
coff_symfile_read (struct objfile *objfile, int mainline)
{
  struct coff_symfile_info *info;
  struct dbx_symfile_info *dbxinfo;
  bfd *abfd = objfile->obfd;
  coff_data_type *cdata = coff_data (abfd);
  char *name = bfd_get_filename (abfd);
  int val;
  unsigned int num_symbols;
  int symtab_offset;
  int stringtab_offset;
  struct cleanup *back_to, *cleanup_minimal_symbols;
  int stabstrsize;
  int len;
  char * target;
  
  info = (struct coff_symfile_info *) objfile->sym_private;
  dbxinfo = objfile->sym_stab_info;
  symfile_bfd = abfd;		/* Kludge for swap routines */

/* WARNING WILL ROBINSON!  ACCESSING BFD-PRIVATE DATA HERE!  FIXME!  */
  num_symbols = bfd_get_symcount (abfd);	/* How many syms */
  symtab_offset = cdata->sym_filepos;	/* Symbol table file offset */
  stringtab_offset = symtab_offset +	/* String table file offset */
    num_symbols * cdata->local_symesz;

  /* Set a few file-statics that give us specific information about
     the particular COFF file format we're reading.  */
  local_n_btmask = cdata->local_n_btmask;
  local_n_btshft = cdata->local_n_btshft;
  local_n_tmask = cdata->local_n_tmask;
  local_n_tshift = cdata->local_n_tshift;
  local_linesz = cdata->local_linesz;
  local_symesz = cdata->local_symesz;
  local_auxesz = cdata->local_auxesz;

  /* Allocate space for raw symbol and aux entries, based on their
     space requirements as reported by BFD.  */
  temp_sym = (char *) xmalloc
    (cdata->local_symesz + cdata->local_auxesz);
  temp_aux = temp_sym + cdata->local_symesz;
  back_to = make_cleanup (free_current_contents, &temp_sym);

  /* We need to know whether this is a PE file, because in PE files,
     unlike standard COFF files, symbol values are stored as offsets
     from the section address, rather than as absolute addresses.
     FIXME: We should use BFD to read the symbol table, and thus avoid
     this problem.  */
  pe_file =
    strncmp (bfd_get_target (objfile->obfd), "pe", 2) == 0
    || strncmp (bfd_get_target (objfile->obfd), "epoc-pe", 7) == 0;

/* End of warning */

  info->min_lineno_offset = 0;
  info->max_lineno_offset = 0;

  /* Only read line number information if we have symbols.

     On Windows NT, some of the system's DLL's have sections with
     PointerToLinenumbers fields that are non-zero, but point at
     random places within the image file.  (In the case I found,
     KERNEL32.DLL's .text section has a line number info pointer that
     points into the middle of the string `lib\\i386\kernel32.dll'.)

     However, these DLL's also have no symbols.  The line number
     tables are meaningless without symbols.  And in fact, GDB never
     uses the line number information unless there are symbols.  So we
     can avoid spurious error messages (and maybe run a little
     faster!) by not even reading the line number table unless we have
     symbols.  */
  if (num_symbols > 0)
    {
      /* Read the line number table, all at once.  */
      bfd_map_over_sections (abfd, find_linenos, (void *) info);

      make_cleanup (free_linetab_cleanup, 0 /*ignore*/);
      val = init_lineno (abfd, info->min_lineno_offset,
                         info->max_lineno_offset - info->min_lineno_offset);
      if (val < 0)
        error ("\"%s\": error reading line numbers\n", name);
    }

  /* Now read the string table, all at once.  */

  make_cleanup (free_stringtab_cleanup, 0 /*ignore*/);
  val = init_stringtab (abfd, stringtab_offset);
  if (val < 0)
    error ("\"%s\": can't get string table", name);

  init_minimal_symbol_collection ();
  cleanup_minimal_symbols = make_cleanup_discard_minimal_symbols ();

  /* Now that the executable file is positioned at symbol table,
     process it and define symbols accordingly.  */

  coff_symtab_read ((long) symtab_offset, num_symbols, objfile);

  /* Install any minimal symbols that have been collected as the current
     minimal symbols for this objfile.  */

  install_minimal_symbols (objfile);

  /* Free the installed minimal symbol data.  */
  do_cleanups (cleanup_minimal_symbols);

  bfd_map_over_sections (abfd, coff_locate_sections, (void *) info);

  if (info->stabsects)
    {
      if (!info->stabstrsect)
	{
	  error (("The debugging information in `%s' is corrupted.\n"
		  "The file has a `.stabs' section, but no `.stabstr' "
		  "section."),
		 name);
	}

      /* FIXME: dubious.  Why can't we use something normal like
         bfd_get_section_contents?  */
      bfd_seek (abfd, abfd->where, 0);

      stabstrsize = bfd_section_size (abfd, info->stabstrsect);

      coffstab_build_psymtabs (objfile,
			       mainline,
			       info->textaddr, info->textsize,
			       info->stabsects,
			       info->stabstrsect->filepos, stabstrsize);
    }
  if (dwarf2_has_info (abfd))
    {
      /* DWARF2 sections.  */
      dwarf2_build_psymtabs (objfile, mainline);
    }

  do_cleanups (back_to);
}