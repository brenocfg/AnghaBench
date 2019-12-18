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
 scalar_t__ TYPE_CODE_ARRAY ; 
 scalar_t__ TYPE_CODE_PTR ; 
 int /*<<< orphan*/  TYPE_LENGTH (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 scalar_t__ VALUE_CONTENTS (struct value*) ; 
 scalar_t__ VALUE_CONTENTS_RAW (struct value*) ; 
 scalar_t__ VALUE_LVAL (struct value*) ; 
 struct type* VALUE_TYPE (struct value*) ; 
 scalar_t__ ada_is_array_descriptor (struct type*) ; 
 struct value* ada_value_ind (struct value*) ; 
 struct value* allocate_value (struct type*) ; 
 struct type* check_typedef (struct type*) ; 
 struct value* desc_data (struct value*) ; 
 scalar_t__ lval_memory ; 
 struct value* make_array_descriptor (struct type*,struct value*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 struct value* place_on_stack (struct value*,int /*<<< orphan*/ *) ; 
 struct value* value_addr (struct value*) ; 

__attribute__((used)) static struct value *
convert_actual (struct value *actual, struct type *formal_type0,
		CORE_ADDR *sp)
{
  struct type *actual_type = check_typedef (VALUE_TYPE (actual));
  struct type *formal_type = check_typedef (formal_type0);
  struct type *formal_target =
    TYPE_CODE (formal_type) == TYPE_CODE_PTR
    ? check_typedef (TYPE_TARGET_TYPE (formal_type)) : formal_type;
  struct type *actual_target =
    TYPE_CODE (actual_type) == TYPE_CODE_PTR
    ? check_typedef (TYPE_TARGET_TYPE (actual_type)) : actual_type;

  if (ada_is_array_descriptor (formal_target)
      && TYPE_CODE (actual_target) == TYPE_CODE_ARRAY)
    return make_array_descriptor (formal_type, actual, sp);
  else if (TYPE_CODE (formal_type) == TYPE_CODE_PTR)
    {
      if (TYPE_CODE (formal_target) == TYPE_CODE_ARRAY
	  && ada_is_array_descriptor (actual_target))
	return desc_data (actual);
      else if (TYPE_CODE (actual_type) != TYPE_CODE_PTR)
	{
	  if (VALUE_LVAL (actual) != lval_memory)
	    {
	      struct value *val;
	      actual_type = check_typedef (VALUE_TYPE (actual));
	      val = allocate_value (actual_type);
	      memcpy ((char *) VALUE_CONTENTS_RAW (val),
		      (char *) VALUE_CONTENTS (actual),
		      TYPE_LENGTH (actual_type));
	      actual = place_on_stack (val, sp);
	    }
	  return value_addr (actual);
	}
    }
  else if (TYPE_CODE (actual_type) == TYPE_CODE_PTR)
    return ada_value_ind (actual);

  return actual;
}