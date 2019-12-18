#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ global; } ;
union dnttentry {TYPE_1__ dfunc; } ;
struct partial_symtab {int dummy; } ;
struct objfile {int /*<<< orphan*/  section_offsets; int /*<<< orphan*/  static_psymbols; int /*<<< orphan*/  global_psymbols; } ;
struct TYPE_5__ {scalar_t__ language; scalar_t__ adrStart; int /*<<< orphan*/  isym; scalar_t__ sbProc; scalar_t__ sbAlias; } ;
typedef  TYPE_2__ quick_procedure_entry ;
typedef  enum hp_language { ____Placeholder_hp_language } hp_language ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 scalar_t__ ANOFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CURR_PROC_END ; 
 int CURR_PROC_START ; 
 int DMGL_ANSI ; 
 int DMGL_PARAMS ; 
 int /*<<< orphan*/  LOC_BLOCK ; 
 int /*<<< orphan*/  SECT_OFF_TEXT (struct objfile*) ; 
 int /*<<< orphan*/  TELL_OBJFILE ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 int /*<<< orphan*/  add_psymbol_with_dem_name_to_list (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,scalar_t__,struct objfile*) ; 
 char* cplus_demangle (char*,int) ; 
 union dnttentry* hpread_get_lntt (int /*<<< orphan*/ ,struct objfile*) ; 
 scalar_t__ language_cplus ; 
 char* main_string ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ trans_lang (int) ; 
 int /*<<< orphan*/  warning (char*,char*,int) ; 

__attribute__((used)) static int
scan_procs (int *curr_pd_p, quick_procedure_entry *qPD, int max_procs,
	    CORE_ADDR start_adr, CORE_ADDR end_adr, struct partial_symtab *pst,
	    char *vt_bits, struct objfile *objfile)
{
  union dnttentry *dn_bufp;
  int symbol_count = 0;		/* Total number of symbols in this psymtab */
  int curr_pd = *curr_pd_p;	/* Convenience variable -- avoid dereferencing pointer all the time */

#ifdef DUMPING
  /* Turn this on for lots of debugging information in this routine */
  static int dumping = 0;
#endif

#ifdef DUMPING
  if (dumping)
    {
      printf ("Scan_procs called, addresses %x to %x, proc %x\n", start_adr, end_adr, curr_pd);
    }
#endif

  while ((CURR_PROC_START <= end_adr) && (curr_pd < max_procs))
    {

      char *rtn_name;		/* mangled name */
      char *rtn_dem_name;	/* qualified demangled name */
      char *class_name;
      int class;

      if ((trans_lang ((enum hp_language) qPD[curr_pd].language) == language_cplus) &&
	  vt_bits[(long) qPD[curr_pd].sbAlias])		/* not a null string */
	{
	  /* Get mangled name for the procedure, and demangle it */
	  rtn_name = &vt_bits[(long) qPD[curr_pd].sbAlias];
	  rtn_dem_name = cplus_demangle (rtn_name, DMGL_ANSI | DMGL_PARAMS);
	}
      else
	{
	  rtn_name = &vt_bits[(long) qPD[curr_pd].sbProc];
	  rtn_dem_name = NULL;
	}

      /* Hack to get around HP C/C++ compilers' insistence on providing
         "_MAIN_" as an alternate name for "main" */
      if ((strcmp (rtn_name, "_MAIN_") == 0) &&
	  (strcmp (&vt_bits[(long) qPD[curr_pd].sbProc], "main") == 0))
	rtn_dem_name = rtn_name = main_string;

#ifdef DUMPING
      if (dumping)
	{
	  printf ("..add %s (demangled %s), index %x to this psymtab\n", rtn_name, rtn_dem_name, curr_pd);
	}
#endif

      /* Check for module-spanning routines. */
      if (CURR_PROC_END > end_adr)
	{
	  TELL_OBJFILE;
	  warning ("Procedure \"%s\" [0x%x] spans file or module boundaries.", rtn_name, curr_pd);
	}

      /* Add this routine symbol to the list in the objfile. 
         Unfortunately we have to go to the LNTT to determine the
         correct list to put it on. An alternative (which the
         code used to do) would be to not check and always throw
         it on the "static" list. But if we go that route, then
         symbol_lookup() needs to be tweaked a bit to account
         for the fact that the function might not be found on
         the correct list in the psymtab. - RT */
      dn_bufp = hpread_get_lntt (qPD[curr_pd].isym, objfile);
      if (dn_bufp->dfunc.global)
	add_psymbol_with_dem_name_to_list (rtn_name,
					   strlen (rtn_name),
					   rtn_dem_name,
					   strlen (rtn_dem_name),
					   VAR_DOMAIN,
					   LOC_BLOCK,	/* "I am a routine"        */
					   &objfile->global_psymbols,
					   (qPD[curr_pd].adrStart +	/* Starting address of rtn */
				 ANOFFSET (objfile->section_offsets, SECT_OFF_TEXT (objfile))),
					   0,	/* core addr?? */
		      trans_lang ((enum hp_language) qPD[curr_pd].language),
					   objfile);
      else
	add_psymbol_with_dem_name_to_list (rtn_name,
					   strlen (rtn_name),
					   rtn_dem_name,
					   strlen (rtn_dem_name),
					   VAR_DOMAIN,
					   LOC_BLOCK,	/* "I am a routine"        */
					   &objfile->static_psymbols,
					   (qPD[curr_pd].adrStart +	/* Starting address of rtn */
				 ANOFFSET (objfile->section_offsets, SECT_OFF_TEXT (objfile))),
					   0,	/* core addr?? */
		      trans_lang ((enum hp_language) qPD[curr_pd].language),
					   objfile);

      symbol_count++;
      *curr_pd_p = ++curr_pd;	/* bump up count & reflect in caller */
    }				/* loop over procedures */

#ifdef DUMPING
  if (dumping)
    {
      if (symbol_count == 0)
	printf ("Scan_procs: no symbols found!\n");
    }
#endif

  return symbol_count;
}