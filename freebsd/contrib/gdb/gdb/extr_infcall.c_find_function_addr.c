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
typedef  enum type_code { ____Placeholder_type_code } type_code ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int TYPE_CODE (struct type*) ; 
 int TYPE_CODE_FUNC ; 
 int TYPE_CODE_INT ; 
 int TYPE_CODE_METHOD ; 
 int TYPE_CODE_PTR ; 
 int TYPE_LENGTH (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 scalar_t__ VALUE_ADDRESS (struct value*) ; 
 struct type* VALUE_TYPE (struct value*) ; 
 struct type* builtin_type_int ; 
 struct type* check_typedef (struct type*) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  current_target ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ gdbarch_convert_from_func_ptr_addr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 struct value* value_addr (struct value*) ; 
 scalar_t__ value_as_address (struct value*) ; 
 scalar_t__ value_as_long (struct value*) ; 

CORE_ADDR
find_function_addr (struct value *function, struct type **retval_type)
{
  struct type *ftype = check_typedef (VALUE_TYPE (function));
  enum type_code code = TYPE_CODE (ftype);
  struct type *value_type;
  CORE_ADDR funaddr;

  /* If it's a member function, just look at the function
     part of it.  */

  /* Determine address to call.  */
  if (code == TYPE_CODE_FUNC || code == TYPE_CODE_METHOD)
    {
      funaddr = VALUE_ADDRESS (function);
      value_type = TYPE_TARGET_TYPE (ftype);
    }
  else if (code == TYPE_CODE_PTR)
    {
      funaddr = value_as_address (function);
      ftype = check_typedef (TYPE_TARGET_TYPE (ftype));
      if (TYPE_CODE (ftype) == TYPE_CODE_FUNC
	  || TYPE_CODE (ftype) == TYPE_CODE_METHOD)
	{
	  funaddr = gdbarch_convert_from_func_ptr_addr (current_gdbarch,
							funaddr,
							&current_target);
	  value_type = TYPE_TARGET_TYPE (ftype);
	}
      else
	value_type = builtin_type_int;
    }
  else if (code == TYPE_CODE_INT)
    {
      /* Handle the case of functions lacking debugging info.
         Their values are characters since their addresses are char */
      if (TYPE_LENGTH (ftype) == 1)
	funaddr = value_as_address (value_addr (function));
      else
	/* Handle integer used as address of a function.  */
	funaddr = (CORE_ADDR) value_as_long (function);

      value_type = builtin_type_int;
    }
  else
    error ("Invalid data type for function to be called.");

  *retval_type = value_type;
  return funaddr;
}