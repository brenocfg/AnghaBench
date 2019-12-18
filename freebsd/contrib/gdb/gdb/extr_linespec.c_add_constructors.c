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
 int /*<<< orphan*/  is_constructor_name (char*) ; 
 struct symbol* lookup_symbol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,struct symtab**) ; 

__attribute__((used)) static int
add_constructors (int method_counter, struct type *t,
		  struct symbol **sym_arr)
{
  int field_counter;
  int i1 = 0;

  /* For GCC 3.x and stabs, constructors and destructors
     have names like __base_ctor and __complete_dtor.
     Check the physname for now if we're looking for a
     constructor.  */
  for (field_counter
	 = TYPE_FN_FIELDLIST_LENGTH (t, method_counter) - 1;
       field_counter >= 0;
       --field_counter)
    {
      struct fn_field *f;
      char *phys_name;
		  
      f = TYPE_FN_FIELDLIST1 (t, method_counter);

      /* GCC 3.x will never produce stabs stub methods, so
	 we don't need to handle this case.  */
      if (TYPE_FN_FIELD_STUB (f, field_counter))
	continue;
      phys_name = TYPE_FN_FIELD_PHYSNAME (f, field_counter);
      if (! is_constructor_name (phys_name))
	continue;

      /* If this method is actually defined, include it in the
	 list.  */
      sym_arr[i1] = lookup_symbol (phys_name,
				   NULL, VAR_DOMAIN,
				   (int *) NULL,
				   (struct symtab **) NULL);
      if (sym_arr[i1])
	i1++;
    }

  return i1;
}