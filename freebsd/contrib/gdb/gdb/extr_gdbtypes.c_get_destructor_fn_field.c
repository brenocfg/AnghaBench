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
struct fn_field {int dummy; } ;

/* Variables and functions */
 struct fn_field* TYPE_FN_FIELDLIST1 (struct type*,int) ; 
 int TYPE_FN_FIELDLIST_LENGTH (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_FN_FIELD_PHYSNAME (struct fn_field*,int) ; 
 int TYPE_NFN_FIELDS (struct type*) ; 
 scalar_t__ is_destructor_name (int /*<<< orphan*/ ) ; 

int
get_destructor_fn_field (struct type *t, int *method_indexp, int *field_indexp)
{
  int i;

  for (i = 0; i < TYPE_NFN_FIELDS (t); i++)
    {
      int j;
      struct fn_field *f = TYPE_FN_FIELDLIST1 (t, i);

      for (j = 0; j < TYPE_FN_FIELDLIST_LENGTH (t, i); j++)
	{
	  if (is_destructor_name (TYPE_FN_FIELD_PHYSNAME (f, j)) != 0)
	    {
	      *method_indexp = i;
	      *field_indexp = j;
	      return 1;
	    }
	}
    }
  return 0;
}