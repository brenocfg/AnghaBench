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
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_ARRAY 130 
#define  TYPE_CODE_STRUCT 129 
#define  TYPE_CODE_UNION 128 
 struct type* to_fixed_array_type (struct type*,struct value*,int /*<<< orphan*/ ) ; 
 struct type* to_fixed_record_type (struct type*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct type* to_fixed_variant_branch_type (struct type*,char*,int /*<<< orphan*/ ,struct value*) ; 

struct type *
ada_to_fixed_type (struct type *type, char *valaddr, CORE_ADDR address,
		   struct value *dval)
{
  CHECK_TYPEDEF (type);
  switch (TYPE_CODE (type))
    {
    default:
      return type;
    case TYPE_CODE_STRUCT:
      return to_fixed_record_type (type, valaddr, address, NULL);
    case TYPE_CODE_ARRAY:
      return to_fixed_array_type (type, dval, 0);
    case TYPE_CODE_UNION:
      if (dval == NULL)
	return type;
      else
	return to_fixed_variant_branch_type (type, valaddr, address, dval);
    }
}