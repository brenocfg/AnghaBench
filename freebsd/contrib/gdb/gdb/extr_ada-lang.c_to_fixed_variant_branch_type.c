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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_PTR ; 
 struct type* TYPE_FIELD_TYPE (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_OBJFILE (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  VALUE_CONTENTS (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 struct type* ada_find_parallel_type (struct type*,char*) ; 
 int ada_which_variant_applies (struct type*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ contains_variant_part (struct type*) ; 
 struct type* empty_record (int /*<<< orphan*/ ) ; 
 scalar_t__ is_dynamic_field (struct type*,int) ; 
 struct type* to_fixed_record_type (struct type*,char*,int /*<<< orphan*/ ,struct value*) ; 

__attribute__((used)) static struct type *
to_fixed_variant_branch_type (struct type *var_type0, char *valaddr,
			      CORE_ADDR address, struct value *dval)
{
  int which;
  struct type *templ_type;
  struct type *var_type;

  if (TYPE_CODE (var_type0) == TYPE_CODE_PTR)
    var_type = TYPE_TARGET_TYPE (var_type0);
  else
    var_type = var_type0;

  templ_type = ada_find_parallel_type (var_type, "___XVU");

  if (templ_type != NULL)
    var_type = templ_type;

  which =
    ada_which_variant_applies (var_type,
			       VALUE_TYPE (dval), VALUE_CONTENTS (dval));

  if (which < 0)
    return empty_record (TYPE_OBJFILE (var_type));
  else if (is_dynamic_field (var_type, which))
    return
      to_fixed_record_type
      (TYPE_TARGET_TYPE (TYPE_FIELD_TYPE (var_type, which)),
       valaddr, address, dval);
  else if (contains_variant_part (TYPE_FIELD_TYPE (var_type, which)))
    return
      to_fixed_record_type
      (TYPE_FIELD_TYPE (var_type, which), valaddr, address, dval);
  else
    return TYPE_FIELD_TYPE (var_type, which);
}