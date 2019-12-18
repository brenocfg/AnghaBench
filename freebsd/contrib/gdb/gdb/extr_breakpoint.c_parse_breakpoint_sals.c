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
struct symtabs_and_lines {int nelts; struct symtab_and_line* sals; } ;
struct symtab_and_line {struct symtab* symtab; int /*<<< orphan*/  pc; int /*<<< orphan*/  section; int /*<<< orphan*/  line; } ;
struct symtab {int dummy; } ;

/* Variables and functions */
 struct symtabs_and_lines decode_line_1 (char**,int,struct symtab*,int /*<<< orphan*/ ,char***,int*) ; 
 int /*<<< orphan*/  default_breakpoint_address ; 
 int /*<<< orphan*/  default_breakpoint_line ; 
 struct symtab* default_breakpoint_symtab ; 
 scalar_t__ default_breakpoint_valid ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  find_pc_overlay (int /*<<< orphan*/ ) ; 
 struct symtab_and_line get_current_source_symtab_and_line () ; 
 int /*<<< orphan*/  init_sal (struct symtab_and_line*) ; 
 scalar_t__ isspace (char) ; 
 char* savestring (char*,int) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char** xcalloc (int,int) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
parse_breakpoint_sals (char **address,
		       struct symtabs_and_lines *sals,
		       char ***addr_string,
		       int *not_found_ptr)
{
  char *addr_start = *address;
  *addr_string = NULL;
  /* If no arg given, or if first arg is 'if ', use the default
     breakpoint. */
  if ((*address) == NULL
      || (strncmp ((*address), "if", 2) == 0 && isspace ((*address)[2])))
    {
      if (default_breakpoint_valid)
	{
	  struct symtab_and_line sal;
	  init_sal (&sal);		/* initialize to zeroes */
	  sals->sals = (struct symtab_and_line *)
	    xmalloc (sizeof (struct symtab_and_line));
	  sal.pc = default_breakpoint_address;
	  sal.line = default_breakpoint_line;
	  sal.symtab = default_breakpoint_symtab;
	  sal.section = find_pc_overlay (sal.pc);
	  sals->sals[0] = sal;
	  sals->nelts = 1;
	}
      else
	error ("No default breakpoint address now.");
    }
  else
    {
      /* Force almost all breakpoints to be in terms of the
         current_source_symtab (which is decode_line_1's default).  This
         should produce the results we want almost all of the time while
         leaving default_breakpoint_* alone.  
         ObjC: However, don't match an Objective-C method name which
         may have a '+' or '-' succeeded by a '[' */
	 
      struct symtab_and_line cursal = get_current_source_symtab_and_line ();
			
      if (default_breakpoint_valid
	  && (!cursal.symtab
 	      || ((strchr ("+-", (*address)[0]) != NULL)
 		  && ((*address)[1] != '['))))
	*sals = decode_line_1 (address, 1, default_breakpoint_symtab,
			       default_breakpoint_line, addr_string, 
			       not_found_ptr);
      else
	*sals = decode_line_1 (address, 1, (struct symtab *) NULL, 0,
		               addr_string, not_found_ptr);
    }
  /* For any SAL that didn't have a canonical string, fill one in. */
  if (sals->nelts > 0 && *addr_string == NULL)
    *addr_string = xcalloc (sals->nelts, sizeof (char **));
  if (addr_start != (*address))
    {
      int i;
      for (i = 0; i < sals->nelts; i++)
	{
	  /* Add the string if not present. */
	  if ((*addr_string)[i] == NULL)
	    (*addr_string)[i] = savestring (addr_start, (*address) - addr_start);
	}
    }
}