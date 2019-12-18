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
struct fn_field {int dummy; } ;

/* Variables and functions */
 struct fn_field* TYPE_FN_FIELDLIST1 (struct type*,int) ; 
 int TYPE_FN_FIELDLIST_LENGTH (struct type*,int) ; 
 char* TYPE_FN_FIELD_PHYSNAME (struct fn_field*,int) ; 
 scalar_t__ TYPE_FN_FIELD_STUB (struct fn_field*,int) ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 char* alloca (scalar_t__) ; 
 char* gdb_mangle_name (struct type*,int,int) ; 
 scalar_t__ is_destructor_name (char*) ; 
 struct symbol* lookup_symbol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,struct symtab**) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

__attribute__((used)) static int
add_matching_methods (int method_counter, struct type *t,
		      struct symbol **sym_arr)
{
  int field_counter;
  int i1 = 0;

  for (field_counter = TYPE_FN_FIELDLIST_LENGTH (t, method_counter) - 1;
       field_counter >= 0;
       --field_counter)
    {
      struct fn_field *f;
      char *phys_name;

      f = TYPE_FN_FIELDLIST1 (t, method_counter);

      if (TYPE_FN_FIELD_STUB (f, field_counter))
	{
	  char *tmp_name;

	  tmp_name = gdb_mangle_name (t,
				      method_counter,
				      field_counter);
	  phys_name = alloca (strlen (tmp_name) + 1);
	  strcpy (phys_name, tmp_name);
	  xfree (tmp_name);
	}
      else
	phys_name = TYPE_FN_FIELD_PHYSNAME (f, field_counter);
		
      /* Destructor is handled by caller, don't add it to
	 the list.  */
      if (is_destructor_name (phys_name) != 0)
	continue;

      sym_arr[i1] = lookup_symbol (phys_name,
				   NULL, VAR_DOMAIN,
				   (int *) NULL,
				   (struct symtab **) NULL);
      if (sym_arr[i1])
	i1++;
      else
	{
	  /* This error message gets printed, but the method
	     still seems to be found
	     fputs_filtered("(Cannot find method ", gdb_stdout);
	     fprintf_symbol_filtered (gdb_stdout, phys_name,
	     language_cplus,
	     DMGL_PARAMS | DMGL_ANSI);
	     fputs_filtered(" - possibly inlined.)\n", gdb_stdout);
	  */
	}
    }

  return i1;
}