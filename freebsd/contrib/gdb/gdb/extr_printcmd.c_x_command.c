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
struct format_data {int count; int /*<<< orphan*/  format; int /*<<< orphan*/  size; } ;
struct expression {int dummy; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_CODE_FUNC ; 
 scalar_t__ TYPE_CODE_REF ; 
 int /*<<< orphan*/  VALUE_ADDRESS (struct value*) ; 
 scalar_t__ VALUE_BFD_SECTION (struct value*) ; 
 scalar_t__ VALUE_LAZY (struct value*) ; 
 scalar_t__ VALUE_LVAL (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 struct value* allocate_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  builtin_type_void ; 
 struct format_data decode_format (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  do_examine (struct format_data,int /*<<< orphan*/ ,scalar_t__) ; 
 struct value* evaluate_expression (struct expression*) ; 
 int /*<<< orphan*/  free_current_contents ; 
 int /*<<< orphan*/  last_examine_address ; 
 struct value* last_examine_value ; 
 int /*<<< orphan*/  last_format ; 
 int /*<<< orphan*/  last_size ; 
 int /*<<< orphan*/  lookup_internalvar (char*) ; 
 struct type* lookup_pointer_type (int /*<<< orphan*/ ) ; 
 scalar_t__ lval_memory ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct expression**) ; 
 int /*<<< orphan*/  next_address ; 
 scalar_t__ next_section ; 
 struct expression* parse_expression (char*) ; 
 int /*<<< orphan*/  set_internalvar (int /*<<< orphan*/ ,struct value*) ; 
 int /*<<< orphan*/  value_as_address (struct value*) ; 
 struct value* value_from_pointer (struct type*,int /*<<< orphan*/ ) ; 
 struct value* value_ind (struct value*) ; 

void
x_command (char *exp, int from_tty)
{
  struct expression *expr;
  struct format_data fmt;
  struct cleanup *old_chain;
  struct value *val;

  fmt.format = last_format;
  fmt.size = last_size;
  fmt.count = 1;

  if (exp && *exp == '/')
    {
      exp++;
      fmt = decode_format (&exp, last_format, last_size);
    }

  /* If we have an expression, evaluate it and use it as the address.  */

  if (exp != 0 && *exp != 0)
    {
      expr = parse_expression (exp);
      /* Cause expression not to be there any more
         if this command is repeated with Newline.
         But don't clobber a user-defined command's definition.  */
      if (from_tty)
	*exp = 0;
      old_chain = make_cleanup (free_current_contents, &expr);
      val = evaluate_expression (expr);
      if (TYPE_CODE (VALUE_TYPE (val)) == TYPE_CODE_REF)
	val = value_ind (val);
      /* In rvalue contexts, such as this, functions are coerced into
         pointers to functions.  This makes "x/i main" work.  */
      if (/* last_format == 'i'  && */ 
	  TYPE_CODE (VALUE_TYPE (val)) == TYPE_CODE_FUNC
	   && VALUE_LVAL (val) == lval_memory)
	next_address = VALUE_ADDRESS (val);
      else
	next_address = value_as_address (val);
      if (VALUE_BFD_SECTION (val))
	next_section = VALUE_BFD_SECTION (val);
      do_cleanups (old_chain);
    }

  do_examine (fmt, next_address, next_section);

  /* If the examine succeeds, we remember its size and format for next time.  */
  last_size = fmt.size;
  last_format = fmt.format;

  /* Set a couple of internal variables if appropriate. */
  if (last_examine_value)
    {
      /* Make last address examined available to the user as $_.  Use
         the correct pointer type.  */
      struct type *pointer_type
	= lookup_pointer_type (VALUE_TYPE (last_examine_value));
      set_internalvar (lookup_internalvar ("_"),
		       value_from_pointer (pointer_type,
					   last_examine_address));

      /* Make contents of last address examined available to the user as $__. */
      /* If the last value has not been fetched from memory then don't
         fetch it now - instead mark it by voiding the $__ variable. */
      if (VALUE_LAZY (last_examine_value))
	set_internalvar (lookup_internalvar ("__"),
			 allocate_value (builtin_type_void));
      else
	set_internalvar (lookup_internalvar ("__"), last_examine_value);
    }
}