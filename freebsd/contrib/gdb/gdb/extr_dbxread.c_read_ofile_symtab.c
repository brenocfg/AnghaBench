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
struct section_offsets {int dummy; } ;
struct partial_symtab {scalar_t__ textlow; int texthigh; int /*<<< orphan*/  symtab; struct section_offsets* section_offsets; struct objfile* objfile; } ;
struct objfile {int /*<<< orphan*/ * obfd; } ;
struct internal_nlist {unsigned char n_type; int /*<<< orphan*/  n_value; int /*<<< orphan*/  n_desc; } ;
struct external_nlist {int /*<<< orphan*/  e_type; } ;
typedef  int /*<<< orphan*/  bfd ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ AUTO_DEMANGLING ; 
 int /*<<< orphan*/  DBX_STRINGTAB (struct objfile*) ; 
 scalar_t__ DEPRECATED_STREQ (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ DEPRECATED_STREQN (char const*,char*,int) ; 
 int /*<<< orphan*/  GCC2_COMPILED_FLAG_SYMBOL ; 
 int /*<<< orphan*/  GCC_COMPILED_FLAG_SYMBOL ; 
 int /*<<< orphan*/  GNU_DEMANGLING_STYLE_STRING ; 
 int /*<<< orphan*/  INTERNALIZE_SYMBOL (struct internal_nlist,struct external_nlist*,int /*<<< orphan*/ *) ; 
 int LDSYMLEN (struct partial_symtab*) ; 
 int LDSYMOFF (struct partial_symtab*) ; 
 unsigned char N_EXT ; 
 scalar_t__ N_NBTEXT ; 
 unsigned char N_SO ; 
 unsigned char N_STAB ; 
 unsigned char N_TEXT ; 
 int /*<<< orphan*/  OBJSTAT (struct objfile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUIT ; 
 int /*<<< orphan*/  SECT_OFF_TEXT (struct objfile*) ; 
 char const bfd_get_symbol_leading_char (int /*<<< orphan*/ *) ; 
 unsigned char bfd_h_get_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct objfile* current_objfile ; 
 int /*<<< orphan*/  end_stabs () ; 
 int /*<<< orphan*/  end_symtab (scalar_t__,struct objfile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fill_symbuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * last_source_file ; 
 scalar_t__ last_source_start_addr ; 
 int /*<<< orphan*/  n_stabs ; 
 int /*<<< orphan*/  process_one_symbol (unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct section_offsets*,struct objfile*) ; 
 int /*<<< orphan*/  processing_acc_compilation ; 
 int processing_gcc_compilation ; 
 int /*<<< orphan*/  set_demangling_style (int /*<<< orphan*/ ) ; 
 char* set_namestring (struct objfile*,struct internal_nlist) ; 
 int /*<<< orphan*/  stabs_seek (int) ; 
 int /*<<< orphan*/  stringtab_global ; 
 int /*<<< orphan*/ * subfile_stack ; 
 int symbol_size ; 
 struct external_nlist* symbuf ; 
 size_t symbuf_end ; 
 size_t symbuf_idx ; 
 int symbuf_left ; 
 scalar_t__ symbuf_read ; 
 int /*<<< orphan*/ * symfile_bfd ; 
 unsigned int symnum ; 

__attribute__((used)) static void
read_ofile_symtab (struct partial_symtab *pst)
{
  char *namestring;
  struct external_nlist *bufp;
  struct internal_nlist nlist;
  unsigned char type;
  unsigned max_symnum;
  bfd *abfd;
  struct objfile *objfile;
  int sym_offset;		/* Offset to start of symbols to read */
  int sym_size;			/* Size of symbols to read */
  CORE_ADDR text_offset;	/* Start of text segment for symbols */
  int text_size;		/* Size of text segment for symbols */
  struct section_offsets *section_offsets;

  objfile = pst->objfile;
  sym_offset = LDSYMOFF (pst);
  sym_size = LDSYMLEN (pst);
  text_offset = pst->textlow;
  text_size = pst->texthigh - pst->textlow;
  /* This cannot be simply objfile->section_offsets because of
     elfstab_offset_sections() which initializes the psymtab section
     offsets information in a special way, and that is different from
     objfile->section_offsets. */ 
  section_offsets = pst->section_offsets;

  current_objfile = objfile;
  subfile_stack = NULL;

  stringtab_global = DBX_STRINGTAB (objfile);
  last_source_file = NULL;

  abfd = objfile->obfd;
  symfile_bfd = objfile->obfd;	/* Implicit param to next_text_symbol */
  symbuf_end = symbuf_idx = 0;
  symbuf_read = 0;
  symbuf_left = sym_offset + sym_size;

  /* It is necessary to actually read one symbol *before* the start
     of this symtab's symbols, because the GCC_COMPILED_FLAG_SYMBOL
     occurs before the N_SO symbol.

     Detecting this in read_dbx_symtab
     would slow down initial readin, so we look for it here instead.  */
  if (!processing_acc_compilation && sym_offset >= (int) symbol_size)
    {
      stabs_seek (sym_offset - symbol_size);
      fill_symbuf (abfd);
      bufp = &symbuf[symbuf_idx++];
      INTERNALIZE_SYMBOL (nlist, bufp, abfd);
      OBJSTAT (objfile, n_stabs++);

      namestring = set_namestring (objfile, nlist);

      processing_gcc_compilation = 0;
      if (nlist.n_type == N_TEXT)
	{
	  const char *tempstring = namestring;

	  if (DEPRECATED_STREQ (namestring, GCC_COMPILED_FLAG_SYMBOL))
	    processing_gcc_compilation = 1;
	  else if (DEPRECATED_STREQ (namestring, GCC2_COMPILED_FLAG_SYMBOL))
	    processing_gcc_compilation = 2;
	  if (tempstring[0] == bfd_get_symbol_leading_char (symfile_bfd))
	    ++tempstring;
	  if (DEPRECATED_STREQN (tempstring, "__gnu_compiled", 14))
	    processing_gcc_compilation = 2;
	}

      /* Try to select a C++ demangling based on the compilation unit
         producer. */

#if 0
      /* For now, stay with AUTO_DEMANGLING for g++ output, as we don't
	 know whether it will use the old style or v3 mangling.  */
      if (processing_gcc_compilation)
	{
	  if (AUTO_DEMANGLING)
	    {
	      set_demangling_style (GNU_DEMANGLING_STYLE_STRING);
	    }
	}
#endif
    }
  else
    {
      /* The N_SO starting this symtab is the first symbol, so we
         better not check the symbol before it.  I'm not this can
         happen, but it doesn't hurt to check for it.  */
      stabs_seek (sym_offset);
      processing_gcc_compilation = 0;
    }

  if (symbuf_idx == symbuf_end)
    fill_symbuf (abfd);
  bufp = &symbuf[symbuf_idx];
  if (bfd_h_get_8 (abfd, bufp->e_type) != N_SO)
    error ("First symbol in segment of executable not a source symbol");

  max_symnum = sym_size / symbol_size;

  for (symnum = 0;
       symnum < max_symnum;
       symnum++)
    {
      QUIT;			/* Allow this to be interruptable */
      if (symbuf_idx == symbuf_end)
	fill_symbuf (abfd);
      bufp = &symbuf[symbuf_idx++];
      INTERNALIZE_SYMBOL (nlist, bufp, abfd);
      OBJSTAT (objfile, n_stabs++);

      type = bfd_h_get_8 (abfd, bufp->e_type);

      namestring = set_namestring (objfile, nlist);

      if (type & N_STAB)
	{
	  process_one_symbol (type, nlist.n_desc, nlist.n_value,
			      namestring, section_offsets, objfile);
	}
      /* We skip checking for a new .o or -l file; that should never
         happen in this routine. */
      else if (type == N_TEXT)
	{
	  /* I don't think this code will ever be executed, because
	     the GCC_COMPILED_FLAG_SYMBOL usually is right before
	     the N_SO symbol which starts this source file.
	     However, there is no reason not to accept
	     the GCC_COMPILED_FLAG_SYMBOL anywhere.  */

	  if (DEPRECATED_STREQ (namestring, GCC_COMPILED_FLAG_SYMBOL))
	    processing_gcc_compilation = 1;
	  else if (DEPRECATED_STREQ (namestring, GCC2_COMPILED_FLAG_SYMBOL))
	    processing_gcc_compilation = 2;

#if 0
	  /* For now, stay with AUTO_DEMANGLING for g++ output, as we don't
	     know whether it will use the old style or v3 mangling.  */
	  if (AUTO_DEMANGLING)
	    {
	      set_demangling_style (GNU_DEMANGLING_STYLE_STRING);
	    }
#endif
	}
      else if (type & N_EXT || type == (unsigned char) N_TEXT
	       || type == (unsigned char) N_NBTEXT
	)
	{
	  /* Global symbol: see if we came across a dbx defintion for
	     a corresponding symbol.  If so, store the value.  Remove
	     syms from the chain when their values are stored, but
	     search the whole chain, as there may be several syms from
	     different files with the same name. */
	  /* This is probably not true.  Since the files will be read
	     in one at a time, each reference to a global symbol will
	     be satisfied in each file as it appears. So we skip this
	     section. */
	  ;
	}
    }

  current_objfile = NULL;

  /* In a Solaris elf file, this variable, which comes from the
     value of the N_SO symbol, will still be 0.  Luckily, text_offset,
     which comes from pst->textlow is correct. */
  if (last_source_start_addr == 0)
    last_source_start_addr = text_offset;

  /* In reordered executables last_source_start_addr may not be the
     lower bound for this symtab, instead use text_offset which comes
     from pst->textlow which is correct.  */
  if (last_source_start_addr > text_offset)
    last_source_start_addr = text_offset;

  pst->symtab = end_symtab (text_offset + text_size, objfile, SECT_OFF_TEXT (objfile));

  end_stabs ();
}