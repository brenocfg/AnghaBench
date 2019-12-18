#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_13__ ;
typedef  struct TYPE_21__   TYPE_11__ ;

/* Type definitions */
struct partial_symtab {int dummy; } ;
struct partial_symbol {int dummy; } ;
struct TYPE_24__ {struct partial_symbol** next; struct partial_symbol** list; } ;
struct TYPE_23__ {struct partial_symbol** next; struct partial_symbol** list; } ;
struct objfile {TYPE_2__ static_psymbols; TYPE_1__ global_psymbols; } ;
struct dntt_type_block {int dummy; } ;
typedef  TYPE_3__* quick_procedure_entry_ptr ;
struct TYPE_25__ {int adrEnd; scalar_t__ sbProc; } ;
typedef  TYPE_3__ quick_procedure_entry ;
typedef  TYPE_5__* quick_module_entry_ptr ;
struct TYPE_26__ {scalar_t__ sbMod; } ;
typedef  TYPE_5__ quick_module_entry ;
typedef  TYPE_7__* quick_file_entry_ptr ;
struct TYPE_27__ {scalar_t__ sbFile; } ;
typedef  TYPE_7__ quick_file_entry ;
typedef  TYPE_9__* quick_class_entry_ptr ;
struct TYPE_28__ {scalar_t__ sbClass; } ;
typedef  TYPE_9__ quick_class_entry ;
struct TYPE_22__ {int end; } ;
struct TYPE_21__ {int pd_entries; int fd_entries; int md_entries; int cd_entries; int globals; } ;
typedef  TYPE_11__* PXDB_header_ptr ;
typedef  int CORE_ADDR ;
typedef  int /*<<< orphan*/  B_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  B_BYTES (int) ; 
 int /*<<< orphan*/  B_CLRALL (int /*<<< orphan*/ *,int) ; 
 int CURR_FILE_END ; 
 int CURR_FILE_ISYM ; 
 int CURR_FILE_START ; 
 int CURR_MODULE_END ; 
 int CURR_MODULE_ISYM ; 
 int CURR_MODULE_START ; 
 int CURR_PROC_ISYM ; 
 int CURR_PROC_START ; 
 scalar_t__ FILE_END (int) ; 
 int FILE_START (int) ; 
 int /*<<< orphan*/  HP_DEMANGLING_STYLE_STRING ; 
 int LNTT_SYMCOUNT (struct objfile*) ; 
 int MODULE_START (int) ; 
 scalar_t__ PROC_END (int) ; 
 scalar_t__ PROC_START (int) ; 
 int /*<<< orphan*/  TELL_OBJFILE ; 
 scalar_t__ VALID_CLASS (int) ; 
 scalar_t__ VALID_CURR_FILE ; 
 scalar_t__ VALID_CURR_MODULE ; 
 scalar_t__ VALID_CURR_PROC ; 
 scalar_t__ VALID_FILE (int) ; 
 scalar_t__ VALID_MODULE (int) ; 
 scalar_t__ VALID_PROC (int) ; 
 int /*<<< orphan*/  clear_pst_syms () ; 
 scalar_t__ current_demangling_style ; 
 scalar_t__ edg_demangling ; 
 int find_next_file_isym (int,TYPE_7__*,int,TYPE_11__*) ; 
 int find_next_module_isym (int,TYPE_5__*,int,TYPE_11__*) ; 
 int find_next_proc_isym (int,TYPE_3__*,int,TYPE_11__*) ; 
 int find_next_pst_start (int) ; 
 struct partial_symtab* hpread_end_psymtab (struct partial_symtab*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct partial_symtab* hpread_start_psymtab (struct objfile*,char*,int,int,struct partial_symbol**,struct partial_symbol**) ; 
 int /*<<< orphan*/  init_pst_syms () ; 
 int max (int,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  paddr_nz (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_13__* pst_syms_array ; 
 int pst_syms_count ; 
 int /*<<< orphan*/  record_pst_syms (int,int) ; 
 int scan_procs (int*,TYPE_3__*,int,int,int,struct partial_symtab*,char*,struct objfile*) ; 
 int /*<<< orphan*/  set_demangling_style (int /*<<< orphan*/ ) ; 
 scalar_t__ told_objfile ; 
 int /*<<< orphan*/  warning (char*,...) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hpread_quick_traverse (struct objfile *objfile, char *gntt_bits,
		       char *vt_bits, PXDB_header_ptr pxdb_header_p)
{
  struct partial_symtab *pst;

  char *addr;

  quick_procedure_entry *qPD;
  quick_file_entry *qFD;
  quick_module_entry *qMD;
  quick_class_entry *qCD;

  int idx;
  int i;
  CORE_ADDR start_adr;		/* current psymtab's starting code addr   */
  CORE_ADDR end_adr;		/* current psymtab's ending code addr     */
  CORE_ADDR next_mod_adr;	/* next module's starting code addr    */
  int curr_pd;			/* current procedure */
  int curr_fd;			/* current file      */
  int curr_md;			/* current module    */
  int start_sym;		/* current psymtab's starting symbol index */
  int end_sym;			/* current psymtab's ending symbol index   */
  int max_LNTT_sym_index;
  int syms_in_pst;
  B_TYPE *class_entered;

  struct partial_symbol **global_syms;	/* We'll be filling in the "global"   */
  struct partial_symbol **static_syms;	/* and "static" tables in the objfile
					   as we go, so we need a pair of     
					   current pointers. */

#ifdef DUMPING
  /* Turn this on for lots of debugging information in this routine.
     You get a blow-by-blow account of quick lookup table reading */
  static int dumping = 0;
#endif

  pst = (struct partial_symtab *) 0;

  /* Clear out some globals */
  init_pst_syms ();
  told_objfile = 0;

  /* Demangling style -- if EDG style already set, don't change it,
     as HP style causes some problems with the KAI EDG compiler */
  if (current_demangling_style != edg_demangling)
    {
      /* Otherwise, ensure that we are using HP style demangling */
      set_demangling_style (HP_DEMANGLING_STYLE_STRING);
    }

  /* First we need to find the starting points of the quick
     look-up tables in the GNTT. */

  addr = gntt_bits;

  qPD = (quick_procedure_entry_ptr) addr;
  addr += pxdb_header_p->pd_entries * sizeof (quick_procedure_entry);

#ifdef DUMPING
  if (dumping)
    {
      printf ("\n Printing routines as we see them\n");
      for (i = 0; VALID_PROC (i); i++)
	{
	  idx = (long) qPD[i].sbProc;
	  printf ("%s %x..%x\n", &vt_bits[idx],
		  (int) PROC_START (i),
		  (int) PROC_END (i));
	}
    }
#endif

  qFD = (quick_file_entry_ptr) addr;
  addr += pxdb_header_p->fd_entries * sizeof (quick_file_entry);

#ifdef DUMPING
  if (dumping)
    {
      printf ("\n Printing files as we see them\n");
      for (i = 0; VALID_FILE (i); i++)
	{
	  idx = (long) qFD[i].sbFile;
	  printf ("%s %x..%x\n", &vt_bits[idx],
		  (int) FILE_START (i),
		  (int) FILE_END (i));
	}
    }
#endif

  qMD = (quick_module_entry_ptr) addr;
  addr += pxdb_header_p->md_entries * sizeof (quick_module_entry);

#ifdef DUMPING
  if (dumping)
    {
      printf ("\n Printing modules as we see them\n");
      for (i = 0; i < pxdb_header_p->md_entries; i++)
	{
	  idx = (long) qMD[i].sbMod;
	  printf ("%s\n", &vt_bits[idx]);
	}
    }
#endif

  qCD = (quick_class_entry_ptr) addr;
  addr += pxdb_header_p->cd_entries * sizeof (quick_class_entry);

#ifdef DUMPING
  if (dumping)
    {
      printf ("\n Printing classes as we see them\n");
      for (i = 0; VALID_CLASS (i); i++)
	{
	  idx = (long) qCD[i].sbClass;
	  printf ("%s\n", &vt_bits[idx]);
	}

      printf ("\n Done with dump, on to build!\n");
    }
#endif

  /* We need this index only while hp-symtab-read.c expects
     a byte offset to the end of the LNTT entries for a given
     psymtab.  Thus the need for it should go away someday.

     When it goes away, then we won't have any need to load the
     LNTT from the objfile at psymtab-time, and start-up will be
     faster.  To make that work, we'll need some way to create
     a null pst for the "globals" pseudo-module. */
  max_LNTT_sym_index = LNTT_SYMCOUNT (objfile);

  /* Scan the module descriptors and make a psymtab for each.

     We know the MDs, FDs and the PDs are in order by starting
     address.  We use that fact to traverse all three arrays in
     parallel, knowing when the next PD is in a new file
     and we need to create a new psymtab. */
  curr_pd = 0;			/* Current procedure entry */
  curr_fd = 0;			/* Current file entry */
  curr_md = 0;			/* Current module entry */

  start_adr = 0;		/* Current psymtab code range */
  end_adr = 0;

  start_sym = 0;		/* Current psymtab symbol range */
  end_sym = 0;

  syms_in_pst = 0;		/* Symbol count for psymtab */

  /* Psts actually just have pointers into the objfile's
     symbol table, not their own symbol tables. */
  global_syms = objfile->global_psymbols.list;
  static_syms = objfile->static_psymbols.list;


  /* First skip over pseudo-entries with address 0.  These represent inlined
     routines and abstract (uninstantiated) template routines.
     FIXME: These should be read in and available -- even if we can't set
     breakpoints, etc., there's some information that can be presented
     to the user. pai/1997-10-08  */

  while (VALID_CURR_PROC && (CURR_PROC_START == 0))
    curr_pd++;

  /* Loop over files, modules, and procedures in code address order. Each
     time we enter an iteration of this loop, curr_pd points to the first
     unprocessed procedure, curr_fd points to the first unprocessed file, and
     curr_md to the first unprocessed module.  Each iteration of this loop
     updates these as required -- any or all of them may be bumpd up
     each time around.  When we exit this loop, we are done with all files
     and modules in the tables -- there may still be some procedures, however.

     Note: This code used to loop only over module entries, under the assumption
     that files can occur via inclusions and are thus unreliable, while a
     compiled object always corresponds to a module.  With CTTI in the HP aCC
     compiler, it turns out that compiled objects may have only files and no
     modules; so we have to loop over files and modules, creating psymtabs for
     either as appropriate.  Unfortunately there are some problems (notably:
     1. the lack of "SRC_FILE_END" entries in the LNTT, 2. the lack of pointers
     to the ending symbol indices of a module or a file) which make it quite hard
     to do this correctly.  Currently it uses a bunch of heuristics to start and
     end psymtabs; they seem to work well with most objects generated by aCC, but
     who knows when that will change...   */

  while (VALID_CURR_FILE || VALID_CURR_MODULE)
    {

      char *mod_name_string = NULL;
      char *full_name_string;

      /* First check for modules like "version.c", which have no code
         in them but still have qMD entries.  They also have no qFD or
         qPD entries.  Their start address is -1 and their end address
         is 0.  */
      if (VALID_CURR_MODULE && (CURR_MODULE_START == -1) && (CURR_MODULE_END == 0))
	{

	  mod_name_string = &vt_bits[(long) qMD[curr_md].sbMod];

#ifdef DUMPING
	  if (dumping)
	    printf ("Module with data only %s\n", mod_name_string);
#endif

	  /* We'll skip the rest (it makes error-checking easier), and
	     just make an empty pst.  Right now empty psts are not put
	     in the pst chain, so all this is for naught, but later it
	     might help.  */

	  pst = hpread_start_psymtab (objfile,
				      mod_name_string,
				      CURR_MODULE_START,	/* Low text address: bogus! */
		       (CURR_MODULE_ISYM * sizeof (struct dntt_type_block)),
	  /* ldsymoff */
				      global_syms,
				      static_syms);

	  pst = hpread_end_psymtab (pst,
				    NULL,	/* psymtab_include_list */
				    0,	/* includes_used        */
				  end_sym * sizeof (struct dntt_type_block),
	  /* byte index in LNTT of end 
	     = capping symbol offset  
	     = LDSYMOFF of nextfile */
				    0,	/* text high            */
				    NULL,	/* dependency_list      */
				    0);		/* dependencies_used    */

	  global_syms = objfile->global_psymbols.next;
	  static_syms = objfile->static_psymbols.next;

	  curr_md++;
	}
      else if (VALID_CURR_MODULE &&
	       ((CURR_MODULE_START == 0) || (CURR_MODULE_START == -1) ||
		(CURR_MODULE_END == 0) || (CURR_MODULE_END == -1)))
	{
	  TELL_OBJFILE;
	  warning ("Module \"%s\" [0x%s] has non-standard addresses.  It starts at 0x%s, ends at 0x%s, and will be skipped.",
		   mod_name_string, paddr_nz (curr_md), paddr_nz (start_adr), paddr_nz (end_adr));
	  /* On to next module */
	  curr_md++;
	}
      else
	{
	  /* First check if we are looking at a file with code in it
	     that does not overlap the current module's code range */

	  if (VALID_CURR_FILE ? (VALID_CURR_MODULE ? (CURR_FILE_END < CURR_MODULE_START) : 1) : 0)
	    {

	      /* Looking at file not corresponding to any module,
	         create a psymtab for it */
	      full_name_string = &vt_bits[(long) qFD[curr_fd].sbFile];
	      start_adr = CURR_FILE_START;
	      end_adr = CURR_FILE_END;
	      start_sym = CURR_FILE_ISYM;

	      /* Check if there are any procedures not handled until now, that
	         begin before the start address of this file, and if so, adjust
	         this module's start address to include them.  This handles routines that
	         are in between file or module ranges for some reason (probably
	         indicates a compiler bug */

	      if (CURR_PROC_START < start_adr)
		{
		  TELL_OBJFILE;
		  warning ("Found procedure \"%s\" [0x%x] that is not in any file or module.",
			   &vt_bits[(long) qPD[curr_pd].sbProc], curr_pd);
		  start_adr = CURR_PROC_START;
		  if (CURR_PROC_ISYM < start_sym)
		    start_sym = CURR_PROC_ISYM;
		}

	      /* Sometimes (compiler bug -- COBOL) the module end address is higher
	         than the start address of the next module, so check for that and
	         adjust accordingly */

	      if (VALID_FILE (curr_fd + 1) && (FILE_START (curr_fd + 1) <= end_adr))
		{
		  TELL_OBJFILE;
		  warning ("File \"%s\" [0x%x] has ending address after starting address of next file; adjusting ending address down.",
			   full_name_string, curr_fd);
		  end_adr = FILE_START (curr_fd + 1) - 1;	/* Is -4 (or -8 for 64-bit) better? */
		}
	      if (VALID_MODULE (curr_md) && (CURR_MODULE_START <= end_adr))
		{
		  TELL_OBJFILE;
		  warning ("File \"%s\" [0x%x] has ending address after starting address of next module; adjusting ending address down.",
			   full_name_string, curr_fd);
		  end_adr = CURR_MODULE_START - 1;	/* Is -4 (or -8 for 64-bit) better? */
		}


#ifdef DUMPING
	      if (dumping)
		{
		  printf ("Make new psymtab for file %s (%x to %x).\n",
			  full_name_string, start_adr, end_adr);
		}
#endif
	      /* Create the basic psymtab, connecting it in the list
	         for this objfile and pointing its symbol entries
	         to the current end of the symbol areas in the objfile.

	         The "ldsymoff" parameter is the byte offset in the LNTT
	         of the first symbol in this file.  Some day we should
	         turn this into an index (fix in hp-symtab-read.c as well).
	         And it's not even the right byte offset, as we're using
	         the size of a union! FIXME!  */
	      pst = hpread_start_psymtab (objfile,
					  full_name_string,
					  start_adr,	/* Low text address */
			      (start_sym * sizeof (struct dntt_type_block)),
	      /* ldsymoff */
					  global_syms,
					  static_syms);

	      /* Set up to only enter each class referenced in this module once.  */
	      class_entered = xmalloc (B_BYTES (pxdb_header_p->cd_entries));
	      B_CLRALL (class_entered, pxdb_header_p->cd_entries);

	      /* Scan the procedure descriptors for procedures in the current
	         file, based on the starting addresses. */

	      syms_in_pst = scan_procs (&curr_pd, qPD, pxdb_header_p->pd_entries,
					start_adr, end_adr, pst, vt_bits, objfile);

	      /* Get ending symbol offset */

	      end_sym = 0;
	      /* First check for starting index before previous psymtab */
	      if (pst_syms_count && start_sym < pst_syms_array[pst_syms_count - 1].end)
		{
		  end_sym = find_next_pst_start (start_sym);
		}
	      /* Look for next start index of a file or module, or procedure */
	      if (!end_sym)
		{
		  int next_file_isym = find_next_file_isym (start_sym, qFD, curr_fd + 1, pxdb_header_p);
		  int next_module_isym = find_next_module_isym (start_sym, qMD, curr_md, pxdb_header_p);
		  int next_proc_isym = find_next_proc_isym (start_sym, qPD, curr_pd, pxdb_header_p);

		  if (next_file_isym && next_module_isym)
		    {
		      /* pick lower of next file or module start index */
		      end_sym = min (next_file_isym, next_module_isym);
		    }
		  else
		    {
		      /* one of them is zero, pick the other */
		      end_sym = max (next_file_isym, next_module_isym);
		    }

		  /* As a precaution, check next procedure index too */
		  if (!end_sym)
		    end_sym = next_proc_isym;
		  else
		    end_sym = min (end_sym, next_proc_isym);
		}

	      /* Couldn't find procedure, file, or module, use globals as default */
	      if (!end_sym)
		end_sym = pxdb_header_p->globals;

#ifdef DUMPING
	      if (dumping)
		{
		  printf ("File psymtab indices: %x to %x\n", start_sym, end_sym);
		}
#endif

	      pst = hpread_end_psymtab (pst,
					NULL,	/* psymtab_include_list */
					0,	/* includes_used        */
				  end_sym * sizeof (struct dntt_type_block),
	      /* byte index in LNTT of end 
	         = capping symbol offset   
	         = LDSYMOFF of nextfile */
					end_adr,	/* text high */
					NULL,	/* dependency_list */
					0);	/* dependencies_used */

	      record_pst_syms (start_sym, end_sym);

	      if (NULL == pst)
		warning ("No symbols in psymtab for file \"%s\" [0x%x].", full_name_string, curr_fd);

#ifdef DUMPING
	      if (dumping)
		{
		  printf ("Made new psymtab for file %s (%x to %x), sym %x to %x.\n",
			  full_name_string, start_adr, end_adr, CURR_FILE_ISYM, end_sym);
		}
#endif
	      /* Prepare for the next psymtab. */
	      global_syms = objfile->global_psymbols.next;
	      static_syms = objfile->static_psymbols.next;
	      xfree (class_entered);

	      curr_fd++;
	    }			/* Psymtab for file */
	  else
	    {
	      /* We have a module for which we create a psymtab */

	      mod_name_string = &vt_bits[(long) qMD[curr_md].sbMod];

	      /* We will include the code ranges of any files that happen to
	         overlap with this module */

	      /* So, first pick the lower of the file's and module's start addresses */
	      start_adr = CURR_MODULE_START;
	      if (VALID_CURR_FILE)
		{
		  if (CURR_FILE_START < CURR_MODULE_START)
		    {
		      TELL_OBJFILE;
		      warning ("File \"%s\" [0x%x] crosses beginning of module \"%s\".",
			       &vt_bits[(long) qFD[curr_fd].sbFile],
			       curr_fd, mod_name_string);

		      start_adr = CURR_FILE_START;
		    }
		}

	      /* Also pick the lower of the file's and the module's start symbol indices */
	      start_sym = CURR_MODULE_ISYM;
	      if (VALID_CURR_FILE && (CURR_FILE_ISYM < CURR_MODULE_ISYM))
		start_sym = CURR_FILE_ISYM;

	      /* For the end address, we scan through the files till we find one
	         that overlaps the current module but ends beyond it; if no such file exists we
	         simply use the module's start address.  
	         (Note, if file entries themselves overlap
	         we take the longest overlapping extension beyond the end of the module...)
	         We assume that modules never overlap. */

	      end_adr = CURR_MODULE_END;

	      if (VALID_CURR_FILE)
		{
		  while (VALID_CURR_FILE && (CURR_FILE_START < end_adr))
		    {

#ifdef DUMPING
		      if (dumping)
			printf ("Maybe skipping file %s which overlaps with module %s\n",
				&vt_bits[(long) qFD[curr_fd].sbFile], mod_name_string);
#endif
		      if (CURR_FILE_END > end_adr)
			{
			  TELL_OBJFILE;
			  warning ("File \"%s\" [0x%x] crosses end of module \"%s\".",
				   &vt_bits[(long) qFD[curr_fd].sbFile],
				   curr_fd, mod_name_string);
			  end_adr = CURR_FILE_END;
			}
		      curr_fd++;
		    }
		  curr_fd--;	/* back up after going too far */
		}

	      /* Sometimes (compiler bug -- COBOL) the module end address is higher
	         than the start address of the next module, so check for that and
	         adjust accordingly */

	      if (VALID_MODULE (curr_md + 1) && (MODULE_START (curr_md + 1) <= end_adr))
		{
		  TELL_OBJFILE;
		  warning ("Module \"%s\" [0x%x] has ending address after starting address of next module; adjusting ending address down.",
			   mod_name_string, curr_md);
		  end_adr = MODULE_START (curr_md + 1) - 1;	/* Is -4 (or -8 for 64-bit) better? */
		}
	      if (VALID_FILE (curr_fd + 1) && (FILE_START (curr_fd + 1) <= end_adr))
		{
		  TELL_OBJFILE;
		  warning ("Module \"%s\" [0x%x] has ending address after starting address of next file; adjusting ending address down.",
			   mod_name_string, curr_md);
		  end_adr = FILE_START (curr_fd + 1) - 1;	/* Is -4 (or -8 for 64-bit) better? */
		}

	      /* Use one file to get the full name for the module.  This
	         situation can arise if there is executable code in a #include
	         file.  Each file with code in it gets a qFD.  Files which don't
	         contribute code don't get a qFD, even if they include files
	         which do, e.g.: 

	         body.c:                    rtn.h:
	         int x;                     int main() {
	         #include "rtn.h"               return x;
	         }

	         There will a qFD for "rtn.h",and a qMD for "body.c",
	         but no qMD for "rtn.h" or qFD for "body.c"!

	         We pick the name of the last file to overlap with this
	         module.  C convention is to put include files first.  In a
	         perfect world, we could check names and use the file whose full
	         path name ends with the module name. */

	      if (VALID_CURR_FILE)
		full_name_string = &vt_bits[(long) qFD[curr_fd].sbFile];
	      else
		full_name_string = mod_name_string;

	      /* Check if there are any procedures not handled until now, that
	         begin before the start address we have now, and if so, adjust
	         this psymtab's start address to include them.  This handles routines that
	         are in between file or module ranges for some reason (probably
	         indicates a compiler bug */

	      if (CURR_PROC_START < start_adr)
		{
		  TELL_OBJFILE;
		  warning ("Found procedure \"%s\" [0x%x] that is not in any file or module.",
			   &vt_bits[(long) qPD[curr_pd].sbProc], curr_pd);
		  start_adr = CURR_PROC_START;
		  if (CURR_PROC_ISYM < start_sym)
		    start_sym = CURR_PROC_ISYM;
		}

#ifdef DUMPING
	      if (dumping)
		{
		  printf ("Make new psymtab for module %s (%x to %x), using file %s\n",
		     mod_name_string, start_adr, end_adr, full_name_string);
		}
#endif
	      /* Create the basic psymtab, connecting it in the list
	         for this objfile and pointing its symbol entries
	         to the current end of the symbol areas in the objfile.

	         The "ldsymoff" parameter is the byte offset in the LNTT
	         of the first symbol in this file.  Some day we should
	         turn this into an index (fix in hp-symtab-read.c as well).
	         And it's not even the right byte offset, as we're using
	         the size of a union! FIXME!  */
	      pst = hpread_start_psymtab (objfile,
					  full_name_string,
					  start_adr,	/* Low text address */
			      (start_sym * sizeof (struct dntt_type_block)),
	      /* ldsymoff */
					  global_syms,
					  static_syms);

	      /* Set up to only enter each class referenced in this module once.  */
	      class_entered = xmalloc (B_BYTES (pxdb_header_p->cd_entries));
	      B_CLRALL (class_entered, pxdb_header_p->cd_entries);

	      /* Scan the procedure descriptors for procedures in the current
	         module, based on the starting addresses. */

	      syms_in_pst = scan_procs (&curr_pd, qPD, pxdb_header_p->pd_entries,
					start_adr, end_adr, pst, vt_bits, objfile);

	      /* Get ending symbol offset */

	      end_sym = 0;
	      /* First check for starting index before previous psymtab */
	      if (pst_syms_count && start_sym < pst_syms_array[pst_syms_count - 1].end)
		{
		  end_sym = find_next_pst_start (start_sym);
		}
	      /* Look for next start index of a file or module, or procedure */
	      if (!end_sym)
		{
		  int next_file_isym = find_next_file_isym (start_sym, qFD, curr_fd + 1, pxdb_header_p);
		  int next_module_isym = find_next_module_isym (start_sym, qMD, curr_md + 1, pxdb_header_p);
		  int next_proc_isym = find_next_proc_isym (start_sym, qPD, curr_pd, pxdb_header_p);

		  if (next_file_isym && next_module_isym)
		    {
		      /* pick lower of next file or module start index */
		      end_sym = min (next_file_isym, next_module_isym);
		    }
		  else
		    {
		      /* one of them is zero, pick the other */
		      end_sym = max (next_file_isym, next_module_isym);
		    }

		  /* As a precaution, check next procedure index too */
		  if (!end_sym)
		    end_sym = next_proc_isym;
		  else
		    end_sym = min (end_sym, next_proc_isym);
		}

	      /* Couldn't find procedure, file, or module, use globals as default */
	      if (!end_sym)
		end_sym = pxdb_header_p->globals;

#ifdef DUMPING
	      if (dumping)
		{
		  printf ("Module psymtab indices: %x to %x\n", start_sym, end_sym);
		}
#endif

	      pst = hpread_end_psymtab (pst,
					NULL,	/* psymtab_include_list */
					0,	/* includes_used        */
				  end_sym * sizeof (struct dntt_type_block),
	      /* byte index in LNTT of end 
	         = capping symbol offset   
	         = LDSYMOFF of nextfile */
					end_adr,	/* text high */
					NULL,	/* dependency_list      */
					0);	/* dependencies_used    */

	      record_pst_syms (start_sym, end_sym);

	      if (NULL == pst)
		warning ("No symbols in psymtab for module \"%s\" [0x%x].", mod_name_string, curr_md);

#ifdef DUMPING
	      if (dumping)
		{
		  printf ("Made new psymtab for module %s (%x to %x), sym %x to %x.\n",
			  mod_name_string, start_adr, end_adr, CURR_MODULE_ISYM, end_sym);
		}
#endif

	      /* Prepare for the next psymtab. */
	      global_syms = objfile->global_psymbols.next;
	      static_syms = objfile->static_psymbols.next;
	      xfree (class_entered);

	      curr_md++;
	      curr_fd++;
	    }			/* psymtab for module */
	}			/* psymtab for non-bogus file or module */
    }				/* End of while loop over all files & modules */

  /* There may be some routines after all files and modules -- these will get
     inserted in a separate new module of their own */
  if (VALID_CURR_PROC)
    {
      start_adr = CURR_PROC_START;
      end_adr = qPD[pxdb_header_p->pd_entries - 1].adrEnd;
      TELL_OBJFILE;
      warning ("Found functions beyond end of all files and modules [0x%x].", curr_pd);
#ifdef DUMPING
      if (dumping)
	{
	  printf ("Orphan functions at end, PD %d and beyond (%x to %x)\n",
		  curr_pd, start_adr, end_adr);
	}
#endif
      pst = hpread_start_psymtab (objfile,
				  "orphans",
				  start_adr,	/* Low text address */
			 (CURR_PROC_ISYM * sizeof (struct dntt_type_block)),
      /* ldsymoff */
				  global_syms,
				  static_syms);

      scan_procs (&curr_pd, qPD, pxdb_header_p->pd_entries,
		  start_adr, end_adr, pst, vt_bits, objfile);

      pst = hpread_end_psymtab (pst,
				NULL,	/* psymtab_include_list */
				0,	/* includes_used */
		   pxdb_header_p->globals * sizeof (struct dntt_type_block),
      /* byte index in LNTT of end 
         = capping symbol offset   
         = LDSYMOFF of nextfile */
				end_adr,	/* text high  */
				NULL,	/* dependency_list */
				0);	/* dependencies_used */
    }


#ifdef NEVER_NEVER
  /* Now build psts for non-module things (in the tail of
     the LNTT, after the last END MODULE entry).

     If null psts were kept on the chain, this would be
     a solution.  FIXME */
  pst = hpread_start_psymtab (objfile,
			      "globals",
			      0,
			      (pxdb_header_p->globals
			       * sizeof (struct dntt_type_block)),
			      objfile->global_psymbols.next,
			      objfile->static_psymbols.next);
  hpread_end_psymtab (pst,
		      NULL, 0,
		      (max_LNTT_sym_index * sizeof (struct dntt_type_block)),
		      0,
		      NULL, 0);
#endif

  clear_pst_syms ();

  return 1;

}