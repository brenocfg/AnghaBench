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
struct ui_file {int dummy; } ;
struct type {int dummy; } ;
typedef  enum val_prettyprint { ____Placeholder_val_prettyprint } val_prettyprint ;
typedef  int /*<<< orphan*/  ULONGEST ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 int /*<<< orphan*/  LA_PRINT_CHAR (int,struct ui_file*) ; 
 int const TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_CHAR 131 
 int const TYPE_CODE_FUNC ; 
#define  TYPE_CODE_INT 130 
#define  TYPE_CODE_PTR 129 
#define  TYPE_CODE_STRUCT 128 
 int TYPE_LENGTH (struct type*) ; 
 int /*<<< orphan*/  TYPE_NAME (struct type*) ; 
 int /*<<< orphan*/  TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  addressprint ; 
 int c_val_print (struct type*,char*,int,int /*<<< orphan*/ ,struct ui_file*,int,int,int,int) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_is_vtbl_ptr_type (struct type*) ; 
 int /*<<< orphan*/  demangle ; 
 int /*<<< orphan*/  extract_unsigned_integer (char*,int) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 int /*<<< orphan*/  java_print_value_fields (struct type*,char*,int /*<<< orphan*/ ,struct ui_file*,int,int,int) ; 
 int output_format ; 
 int /*<<< orphan*/  print_address_demangle (int /*<<< orphan*/ ,struct ui_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_longest (struct ui_file*,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_scalar_formatted (char*,struct type*,int,int /*<<< orphan*/ ,struct ui_file*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unpack_long (struct type*,char*) ; 
 int /*<<< orphan*/  unpack_pointer (struct type*,char*) ; 
 int /*<<< orphan*/  val_print_type_code_int (struct type*,char*,struct ui_file*) ; 
 int /*<<< orphan*/  vtblprint ; 

int
java_val_print (struct type *type, char *valaddr, int embedded_offset,
		CORE_ADDR address, struct ui_file *stream, int format,
		int deref_ref, int recurse, enum val_prettyprint pretty)
{
  unsigned int i = 0;	/* Number of characters printed */
  struct type *target_type;
  CORE_ADDR addr;

  CHECK_TYPEDEF (type);
  switch (TYPE_CODE (type))
    {
    case TYPE_CODE_PTR:
      if (format && format != 's')
	{
	  print_scalar_formatted (valaddr, type, format, 0, stream);
	  break;
	}
#if 0
      if (vtblprint && cp_is_vtbl_ptr_type (type))
	{
	  /* Print the unmangled name if desired.  */
	  /* Print vtable entry - we only get here if we ARE using
	     -fvtable_thunks.  (Otherwise, look under TYPE_CODE_STRUCT.) */
	  /* Extract an address, assume that it is unsigned.  */
	  print_address_demangle (extract_unsigned_integer (valaddr, TYPE_LENGTH (type)),
				  stream, demangle);
	  break;
	}
#endif
      addr = unpack_pointer (type, valaddr);
      if (addr == 0)
	{
	  fputs_filtered ("null", stream);
	  return i;
	}
      target_type = check_typedef (TYPE_TARGET_TYPE (type));

      if (TYPE_CODE (target_type) == TYPE_CODE_FUNC)
	{
	  /* Try to print what function it points to.  */
	  print_address_demangle (addr, stream, demangle);
	  /* Return value is irrelevant except for string pointers.  */
	  return (0);
	}

      if (addressprint && format != 's')
	{
	  fputs_filtered ("@", stream);
	  print_longest (stream, 'x', 0, (ULONGEST) addr);
	}

      return i;

    case TYPE_CODE_CHAR:
    case TYPE_CODE_INT:
      /* Can't just call c_val_print because that prints bytes as C
	 chars.  */
      format = format ? format : output_format;
      if (format)
	print_scalar_formatted (valaddr, type, format, 0, stream);
      else if (TYPE_CODE (type) == TYPE_CODE_CHAR
	       || (TYPE_CODE (type) == TYPE_CODE_INT
		   && TYPE_LENGTH (type) == 2
		   && strcmp (TYPE_NAME (type), "char") == 0))
	LA_PRINT_CHAR ((int) unpack_long (type, valaddr), stream);
      else
	val_print_type_code_int (type, valaddr, stream);
      break;

    case TYPE_CODE_STRUCT:
      java_print_value_fields (type, valaddr, address, stream, format,
			       recurse, pretty);
      break;

    default:
      return c_val_print (type, valaddr, embedded_offset, address, stream,
			  format, deref_ref, recurse, pretty);
    }

  return 0;
}