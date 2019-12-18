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
 int /*<<< orphan*/  TYPE_FN_FIELD_PHYSNAME (struct fn_field*,int) ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 scalar_t__ destructor_name_p (char*,struct type*) ; 
 int find_methods (struct type*,char*,struct symbol**) ; 
 scalar_t__ get_destructor_fn_field (struct type*,int*,int*) ; 
 struct symbol* lookup_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,struct symtab**) ; 

__attribute__((used)) static int
collect_methods (char *copy, struct type *t,
		 struct symbol **sym_arr)
{
  int i1 = 0;	/*  Counter for the symbol array.  */

  if (destructor_name_p (copy, t))
    {
      /* Destructors are a special case.  */
      int m_index, f_index;

      if (get_destructor_fn_field (t, &m_index, &f_index))
	{
	  struct fn_field *f = TYPE_FN_FIELDLIST1 (t, m_index);

	  sym_arr[i1] =
	    lookup_symbol (TYPE_FN_FIELD_PHYSNAME (f, f_index),
			   NULL, VAR_DOMAIN, (int *) NULL,
			   (struct symtab **) NULL);
	  if (sym_arr[i1])
	    i1++;
	}
    }
  else
    i1 = find_methods (t, copy, sym_arr);

  return i1;
}