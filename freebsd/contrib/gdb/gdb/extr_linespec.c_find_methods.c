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
struct type {int dummy; } ;
struct symtab {int dummy; } ;
struct symbol {int dummy; } ;
struct block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 int /*<<< orphan*/  DMGL_ANSI ; 
 int /*<<< orphan*/  STRUCT_DOMAIN ; 
 struct type* TYPE_BASECLASS (struct type*,int) ; 
 char* TYPE_FN_FIELDLIST_NAME (struct type*,int) ; 
 int TYPE_NFN_FIELDS (struct type*) ; 
 int TYPE_N_BASECLASSES (struct type*) ; 
 scalar_t__ add_constructors (int,struct type*,struct symbol**) ; 
 scalar_t__ add_matching_methods (int,struct type*,struct symbol**) ; 
 scalar_t__ cplus_demangle_opname (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ lookup_symbol (char*,struct block*,int /*<<< orphan*/ ,int*,struct symtab**) ; 
 scalar_t__ strcmp_iw (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* type_name_no_tag (struct type*) ; 

__attribute__((used)) static int
find_methods (struct type *t, char *name, struct symbol **sym_arr)
{
  int i1 = 0;
  int ibase;
  char *class_name = type_name_no_tag (t);

  /* Ignore this class if it doesn't have a name.  This is ugly, but
     unless we figure out how to get the physname without the name of
     the class, then the loop can't do any good.  */
  if (class_name
      && (lookup_symbol (class_name, (struct block *) NULL,
			 STRUCT_DOMAIN, (int *) NULL,
			 (struct symtab **) NULL)))
    {
      int method_counter;
      int name_len = strlen (name);

      CHECK_TYPEDEF (t);

      /* Loop over each method name.  At this level, all overloads of a name
         are counted as a single name.  There is an inner loop which loops over
         each overload.  */

      for (method_counter = TYPE_NFN_FIELDS (t) - 1;
	   method_counter >= 0;
	   --method_counter)
	{
	  char *method_name = TYPE_FN_FIELDLIST_NAME (t, method_counter);
	  char dem_opname[64];

	  if (strncmp (method_name, "__", 2) == 0 ||
	      strncmp (method_name, "op", 2) == 0 ||
	      strncmp (method_name, "type", 4) == 0)
	    {
	      if (cplus_demangle_opname (method_name, dem_opname, DMGL_ANSI))
		method_name = dem_opname;
	      else if (cplus_demangle_opname (method_name, dem_opname, 0))
		method_name = dem_opname;
	    }

	  if (strcmp_iw (name, method_name) == 0)
	    /* Find all the overloaded methods with that name.  */
	    i1 += add_matching_methods (method_counter, t,
					sym_arr + i1);
	  else if (strncmp (class_name, name, name_len) == 0
		   && (class_name[name_len] == '\0'
		       || class_name[name_len] == '<'))
	    i1 += add_constructors (method_counter, t,
				    sym_arr + i1);
	}
    }

  /* Only search baseclasses if there is no match yet, since names in
     derived classes override those in baseclasses.

     FIXME: The above is not true; it is only true of member functions
     if they have the same number of arguments (??? - section 13.1 of the
     ARM says the function members are not in the same scope but doesn't
     really spell out the rules in a way I understand.  In any case, if
     the number of arguments differ this is a case in which we can overload
     rather than hiding without any problem, and gcc 2.4.5 does overload
     rather than hiding in this case).  */

  if (i1 == 0)
    for (ibase = 0; ibase < TYPE_N_BASECLASSES (t); ibase++)
      i1 += find_methods (TYPE_BASECLASS (t, ibase), name, sym_arr + i1);

  return i1;
}