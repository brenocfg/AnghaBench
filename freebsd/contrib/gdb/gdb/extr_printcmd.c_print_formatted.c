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
struct ui_file {int dummy; } ;
struct type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_CODE (struct type*) ; 
 int /*<<< orphan*/  TYPE_CODE_ARRAY ; 
 int /*<<< orphan*/  TYPE_CODE_NAMESPACE ; 
 int /*<<< orphan*/  TYPE_CODE_STRING ; 
 int /*<<< orphan*/  TYPE_CODE_STRUCT ; 
 int /*<<< orphan*/  TYPE_CODE_UNION ; 
 int TYPE_LENGTH (struct type*) ; 
 scalar_t__ VALUE_ADDRESS (struct value*) ; 
 int /*<<< orphan*/  VALUE_BFD_SECTION (struct value*) ; 
 int /*<<< orphan*/  VALUE_CONTENTS (struct value*) ; 
 scalar_t__ VALUE_LVAL (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  Val_pretty_default ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 scalar_t__ gdb_print_insn (scalar_t__,struct ui_file*) ; 
 scalar_t__ lval_memory ; 
 scalar_t__ next_address ; 
 int /*<<< orphan*/  next_section ; 
 int /*<<< orphan*/  print_scalar_formatted (int /*<<< orphan*/ ,struct type*,int,int,struct ui_file*) ; 
 scalar_t__ val_print_string (scalar_t__,int,int,struct ui_file*) ; 
 int /*<<< orphan*/  value_print (struct value*,struct ui_file*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrap_here (char*) ; 

__attribute__((used)) static void
print_formatted (struct value *val, int format, int size,
		 struct ui_file *stream)
{
  struct type *type = check_typedef (VALUE_TYPE (val));
  int len = TYPE_LENGTH (type);

  if (VALUE_LVAL (val) == lval_memory)
    {
      next_address = VALUE_ADDRESS (val) + len;
      next_section = VALUE_BFD_SECTION (val);
    }

  switch (format)
    {
    case 's':
      /* FIXME: Need to handle wchar_t's here... */
      next_address = VALUE_ADDRESS (val)
	+ val_print_string (VALUE_ADDRESS (val), -1, 1, stream);
      next_section = VALUE_BFD_SECTION (val);
      break;

    case 'i':
      /* The old comment says
         "Force output out, print_insn not using _filtered".
         I'm not completely sure what that means, I suspect most print_insn
         now do use _filtered, so I guess it's obsolete.
         --Yes, it does filter now, and so this is obsolete.  -JB  */

      /* We often wrap here if there are long symbolic names.  */
      wrap_here ("    ");
      next_address = VALUE_ADDRESS (val)
	+ gdb_print_insn (VALUE_ADDRESS (val), stream);
      next_section = VALUE_BFD_SECTION (val);
      break;

    default:
      if (format == 0
	  || TYPE_CODE (type) == TYPE_CODE_ARRAY
	  || TYPE_CODE (type) == TYPE_CODE_STRING
	  || TYPE_CODE (type) == TYPE_CODE_STRUCT
	  || TYPE_CODE (type) == TYPE_CODE_UNION
	  || TYPE_CODE (type) == TYPE_CODE_NAMESPACE)
	/* If format is 0, use the 'natural' format for
	 * that type of value.  If the type is non-scalar,
	 * we have to use language rules to print it as
	 * a series of scalars.
	 */
	value_print (val, stream, format, Val_pretty_default);
      else
	/* User specified format, so don't look to the
	 * the type to tell us what to do.
	 */
	print_scalar_formatted (VALUE_CONTENTS (val), type,
				format, size, stream);
    }
}