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
typedef  enum val_prettyprint { ____Placeholder_val_prettyprint } val_prettyprint ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_INT ; 
 scalar_t__ TYPE_CODE_PTR ; 
 scalar_t__ TYPE_CODE_REF ; 
 int TYPE_LENGTH (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (struct type*) ; 
 scalar_t__ VALUE_ADDRESS (struct value*) ; 
 char* VALUE_CONTENTS (struct value*) ; 
 scalar_t__ VALUE_OFFSET (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 scalar_t__ ada_is_array_descriptor (struct type*) ; 
 scalar_t__ ada_is_bogus_array_descriptor (struct type*) ; 
 struct type* ada_to_fixed_type (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*) ; 
 int /*<<< orphan*/  type_print (struct type*,char*,struct ui_file*,int) ; 
 int val_print (struct type*,char*,int /*<<< orphan*/ ,scalar_t__,struct ui_file*,int,int,int /*<<< orphan*/ ,int) ; 
 struct value* value_from_contents_and_address (struct type*,char*,scalar_t__) ; 

int
ada_value_print (struct value *val0, struct ui_file *stream, int format,
		 enum val_prettyprint pretty)
{
  char *valaddr = VALUE_CONTENTS (val0);
  CORE_ADDR address = VALUE_ADDRESS (val0) + VALUE_OFFSET (val0);
  struct type *type =
    ada_to_fixed_type (VALUE_TYPE (val0), valaddr, address, NULL);
  struct value *val =
    value_from_contents_and_address (type, valaddr, address);

  /* If it is a pointer, indicate what it points to. */
  if (TYPE_CODE (type) == TYPE_CODE_PTR || TYPE_CODE (type) == TYPE_CODE_REF)
    {
      /* Hack:  remove (char *) for char strings.  Their
         type is indicated by the quoted string anyway. */
      if (TYPE_CODE (type) == TYPE_CODE_PTR &&
	  TYPE_LENGTH (TYPE_TARGET_TYPE (type)) == sizeof (char) &&
	  TYPE_CODE (TYPE_TARGET_TYPE (type)) == TYPE_CODE_INT &&
	  !TYPE_UNSIGNED (TYPE_TARGET_TYPE (type)))
	{
	  /* Print nothing */
	}
      else
	{
	  fprintf_filtered (stream, "(");
	  type_print (type, "", stream, -1);
	  fprintf_filtered (stream, ") ");
	}
    }
  else if (ada_is_array_descriptor (type))
    {
      fprintf_filtered (stream, "(");
      type_print (type, "", stream, -1);
      fprintf_filtered (stream, ") ");
    }
  else if (ada_is_bogus_array_descriptor (type))
    {
      fprintf_filtered (stream, "(");
      type_print (type, "", stream, -1);
      fprintf_filtered (stream, ") (...?)");
      return 0;
    }
  return (val_print (type, VALUE_CONTENTS (val), 0, address,
		     stream, format, 1, 0, pretty));
}