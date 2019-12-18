#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned char kind; scalar_t__ extension; } ;
union dnttentry {TYPE_1__ dblock; } ;
struct symtab {int dummy; } ;
struct section_offsets {int dummy; } ;
struct objfile {int dummy; } ;
struct dntt_type_block {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ DNTT_TYPE_MODULE ; 
 scalar_t__ DNTT_TYPE_SRCFILE ; 
 int /*<<< orphan*/  HP_DEMANGLING_STYLE_STRING ; 
 int /*<<< orphan*/  QUIT ; 
 int /*<<< orphan*/  SECT_OFF_TEXT (struct objfile*) ; 
 scalar_t__ current_demangling_style ; 
 struct objfile* current_objfile ; 
 scalar_t__ edg_demangling ; 
 struct symtab* end_symtab (int /*<<< orphan*/ ,struct objfile*,int /*<<< orphan*/ ) ; 
 int hp_som_som_object_present ; 
 union dnttentry* hpread_get_lntt (int,struct objfile*) ; 
 int /*<<< orphan*/  hpread_process_one_debug_symbol (union dnttentry*,char*,struct section_offsets*,struct objfile*,int /*<<< orphan*/ ,int,char*,unsigned int,int*) ; 
 scalar_t__ last_source_file ; 
 int /*<<< orphan*/  record_debugformat (char*) ; 
 int /*<<< orphan*/  set_demangling_style (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_namestring (union dnttentry*,char**,struct objfile*) ; 
 int /*<<< orphan*/  start_symtab (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ subfile_stack ; 
 unsigned int symnum ; 

__attribute__((used)) static struct symtab *
hpread_expand_symtab (struct objfile *objfile, int sym_offset, int sym_size,
		      CORE_ADDR text_offset, int text_size,
		      struct section_offsets *section_offsets, char *filename)
{
  char *namestring;
  union dnttentry *dn_bufp;
  unsigned max_symnum;
  int at_module_boundary = 0;
  /* 1 => at end, -1 => at beginning */

  int sym_index = sym_offset / sizeof (struct dntt_type_block);

  current_objfile = objfile;
  subfile_stack = 0;

  last_source_file = 0;

  /* Demangling style -- if EDG style already set, don't change it,
     as HP style causes some problems with the KAI EDG compiler */
  if (current_demangling_style != edg_demangling)
    {
      /* Otherwise, ensure that we are using HP style demangling */
      set_demangling_style (HP_DEMANGLING_STYLE_STRING);
    }

  dn_bufp = hpread_get_lntt (sym_index, objfile);
  if (!((dn_bufp->dblock.kind == (unsigned char) DNTT_TYPE_SRCFILE) ||
	(dn_bufp->dblock.kind == (unsigned char) DNTT_TYPE_MODULE)))
    {
      start_symtab ("globals", NULL, 0);
      record_debugformat ("HP");
    }

  /* The psymtab builder (hp-psymtab-read.c) is the one that
   * determined the "sym_size" argument (i.e. how many DNTT symbols
   * are in this symtab), which we use to compute "max_symnum"
   * (point in DNTT to which we read). 
   *
   * Perhaps this should be changed so that 
   * process_one_debug_symbol() "knows" when
   * to stop reading (based on reading from the MODULE to the matching
   * END), and take out this reliance on a #-syms being passed in...
   * (I'm worried about the reliability of this number). But I'll
   * leave it as-is, for now. - RT
   *
   * The change above has been made. I've left the "for" loop control
   * in to prepare for backing this out again. -JB
   */
  max_symnum = sym_size / sizeof (struct dntt_type_block);
  /* No reason to multiply on pst side and divide on sym side... FIXME */

  /* Read in and process each debug symbol within the specified range.
   */
  for (symnum = 0;
       symnum < max_symnum;
       symnum++)
    {
      QUIT;			/* Allow this to be interruptable */
      dn_bufp = hpread_get_lntt (sym_index + symnum, objfile);

      if (dn_bufp->dblock.extension)
	continue;

      /* Yow!  We call set_namestring on things without names!  */
      set_namestring (dn_bufp, &namestring, objfile);

      hpread_process_one_debug_symbol (dn_bufp, namestring, section_offsets,
				       objfile, text_offset, text_size,
				       filename, symnum + sym_index,
				       &at_module_boundary
	);

      /* OLD COMMENTS: This routine is only called for psts.  All psts
       * correspond to MODULES.  If we ever do lazy-reading of globals
       * from the LNTT, then there will be a pst which ends when the
       * LNTT ends, and not at an END MODULE entry.  Then we'll have
       * to re-visit this break.  

       if( at_end_of_module )
       break;

       */

      /* We no longer break out of the loop when we reach the end of a
         module. The reason is that with CTTI, the compiler can generate
         function symbols (for template function instantiations) which are not
         in any module; typically they show up beyond a module's end, and
         before the next module's start.  We include them in the current
         module.  However, we still don't trust the MAX_SYMNUM value from
         the psymtab, so we break out if we enter a new module. */

      if (at_module_boundary == -1)
	break;
    }

  current_objfile = NULL;
  hp_som_som_object_present = 1;	/* Indicate we've processed an HP SOM SOM file */

  return end_symtab (text_offset + text_size, objfile, SECT_OFF_TEXT (objfile));
}