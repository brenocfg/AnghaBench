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
struct value {int dummy; } ;
struct type {int dummy; } ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_PTR ; 
 scalar_t__ TYPE_CODE_REF ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 scalar_t__ TYPE_CODE_UNION ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 struct value* ada_coerce_ref (struct value*) ; 
 struct value* ada_search_struct_field (char*,struct value*,int /*<<< orphan*/ ,struct type*) ; 
 struct value* ada_value_ind (struct value*) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,char*) ; 

struct value *
ada_value_struct_elt (struct value *arg, char *name, char *err)
{
  struct type *t;
  struct value *v;

  arg = ada_coerce_ref (arg);
  t = check_typedef (VALUE_TYPE (arg));

  /* Follow pointers until we get to a non-pointer.  */

  while (TYPE_CODE (t) == TYPE_CODE_PTR || TYPE_CODE (t) == TYPE_CODE_REF)
    {
      arg = ada_value_ind (arg);
      t = check_typedef (VALUE_TYPE (arg));
    }

  if (TYPE_CODE (t) != TYPE_CODE_STRUCT && TYPE_CODE (t) != TYPE_CODE_UNION)
    error ("Attempt to extract a component of a value that is not a %s.",
	   err);

  v = ada_search_struct_field (name, arg, 0, t);
  if (v == NULL)
    error ("There is no member named %s.", name);

  return v;
}