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
typedef  scalar_t__ LONGEST ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 int HOST_CHAR_BIT ; 
 int /*<<< orphan*/  QUIT ; 
 int TARGET_PTR_BIT ; 
 int const TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_ARRAY 134 
#define  TYPE_CODE_ENUM 133 
#define  TYPE_CODE_INT 132 
#define  TYPE_CODE_RANGE 131 
#define  TYPE_CODE_REF 130 
#define  TYPE_CODE_STRUCT 129 
 int const TYPE_CODE_UNDEF ; 
#define  TYPE_CODE_UNION 128 
 scalar_t__ TYPE_FIELD_BITPOS (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_FIELD_BITSIZE (struct type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_FIELD_NAME (struct type*,int) ; 
 unsigned int TYPE_LENGTH (struct type*) ; 
 unsigned int TYPE_NFIELDS (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  VALUE_ADDRESS (struct value*) ; 
 char* VALUE_CONTENTS (struct value*) ; 
 struct type* VALUE_TYPE (struct value*) ; 
 char* ada_aligned_value_addr (struct type*,char*) ; 
 struct value* ada_coerce_to_simple_array_ptr (struct value*) ; 
 char* ada_enum_name (int /*<<< orphan*/ ) ; 
 scalar_t__ ada_fixed_to_float (struct type*,scalar_t__) ; 
 scalar_t__ ada_is_array_descriptor (struct type*) ; 
 int /*<<< orphan*/  ada_is_bogus_array_descriptor (struct type*) ; 
 int /*<<< orphan*/  ada_is_character_type (struct type*) ; 
 int /*<<< orphan*/  ada_is_fixed_point_type (struct type*) ; 
 scalar_t__ ada_is_packed_array_type (struct type*) ; 
 int /*<<< orphan*/  ada_is_string_type (struct type*) ; 
 int /*<<< orphan*/  ada_is_vax_floating_type (struct type*) ; 
 int /*<<< orphan*/  ada_printchar (unsigned char,struct ui_file*) ; 
 struct value* ada_value_ind (int /*<<< orphan*/ ) ; 
 struct value* ada_vax_float_print_function (struct type*) ; 
 int /*<<< orphan*/  addressprint ; 
 int /*<<< orphan*/  builtin_type_char ; 
 int /*<<< orphan*/  builtin_type_int ; 
 struct type* builtin_type_void ; 
 int c_val_print (struct type*,char*,int,int /*<<< orphan*/ ,struct ui_file*,int,int,int,int) ; 
 struct value* call_function_by_hand (struct value*,int,struct value**) ; 
 int /*<<< orphan*/  char_at (char*,int,unsigned int) ; 
 struct type* check_typedef (struct type*) ; 
 int /*<<< orphan*/  create_array_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_range_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  extract_unsigned_integer (char*,int) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fputs_filtered (char const*,struct ui_file*) ; 
 int /*<<< orphan*/  gdb_flush (struct ui_file*) ; 
 int /*<<< orphan*/  lookup_pointer_type (struct type*) ; 
 struct type* make_pointer_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int output_format ; 
 int /*<<< orphan*/  prettyprint_arrays ; 
 int /*<<< orphan*/  print_address_numeric (int /*<<< orphan*/ ,int,struct ui_file*) ; 
 int /*<<< orphan*/  print_longest (struct ui_file*,char,int /*<<< orphan*/ ,scalar_t__) ; 
 int print_max ; 
 int /*<<< orphan*/  print_optional_low_bound (struct ui_file*,struct type*) ; 
 int /*<<< orphan*/  print_record (struct type*,char*,struct ui_file*,int,int,int) ; 
 int /*<<< orphan*/  print_scalar_formatted (char*,struct type*,int,int /*<<< orphan*/ ,struct ui_file*) ; 
 int /*<<< orphan*/  print_spaces_filtered (int,struct ui_file*) ; 
 struct type* printable_val_type (struct type*,char*) ; 
 int /*<<< orphan*/  printstr (struct ui_file*,char*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stop_print_at_null ; 
 scalar_t__ unpack_long (struct type*,char*) ; 
 int /*<<< orphan*/  unpack_pointer (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  val_print (struct type*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ui_file*,int,int,int,int) ; 
 int /*<<< orphan*/  val_print_array_elements (struct type*,char*,int /*<<< orphan*/ ,struct ui_file*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  val_print_packed_array_elements (struct type*,char*,int /*<<< orphan*/ ,struct ui_file*,int,int,int) ; 
 int /*<<< orphan*/  val_print_type_code_int (struct type*,char*,struct ui_file*) ; 
 struct value* value_cast (struct type*,struct value*) ; 
 int /*<<< orphan*/  value_free_to_mark (struct value*) ; 
 struct value* value_from_contents_and_address (struct type*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value_from_longest (int /*<<< orphan*/ ,scalar_t__) ; 
 struct value* value_ind (struct value*) ; 
 struct value* value_mark () ; 

__attribute__((used)) static int
ada_val_print_1 (struct type *type, char *valaddr0, int embedded_offset,
		 CORE_ADDR address, struct ui_file *stream, int format,
		 int deref_ref, int recurse, enum val_prettyprint pretty)
{
  unsigned int len;
  int i;
  struct type *elttype;
  unsigned int eltlen;
  LONGEST val;
  CORE_ADDR addr;
  char *valaddr = valaddr0 + embedded_offset;

  CHECK_TYPEDEF (type);

  if (ada_is_array_descriptor (type) || ada_is_packed_array_type (type))
    {
      int retn;
      struct value *mark = value_mark ();
      struct value *val;
      val = value_from_contents_and_address (type, valaddr, address);
      val = ada_coerce_to_simple_array_ptr (val);
      if (val == NULL)
	{
	  fprintf_filtered (stream, "(null)");
	  retn = 0;
	}
      else
	retn = ada_val_print_1 (VALUE_TYPE (val), VALUE_CONTENTS (val), 0,
				VALUE_ADDRESS (val), stream, format,
				deref_ref, recurse, pretty);
      value_free_to_mark (mark);
      return retn;
    }

  valaddr = ada_aligned_value_addr (type, valaddr);
  embedded_offset -= valaddr - valaddr0 - embedded_offset;
  type = printable_val_type (type, valaddr);

  switch (TYPE_CODE (type))
    {
    default:
      return c_val_print (type, valaddr0, embedded_offset, address, stream,
			  format, deref_ref, recurse, pretty);

    case TYPE_CODE_INT:
    case TYPE_CODE_RANGE:
      if (ada_is_fixed_point_type (type))
	{
	  LONGEST v = unpack_long (type, valaddr);
	  int len = TYPE_LENGTH (type);

	  fprintf_filtered (stream, len < 4 ? "%.11g" : "%.17g",
			    (double) ada_fixed_to_float (type, v));
	  return 0;
	}
      else if (ada_is_vax_floating_type (type))
	{
	  struct value *val =
	    value_from_contents_and_address (type, valaddr, address);
	  struct value *func = ada_vax_float_print_function (type);
	  if (func != 0)
	    {
	      static struct type *parray_of_char = NULL;
	      struct value *printable_val;

	      if (parray_of_char == NULL)
		parray_of_char =
		  make_pointer_type
		  (create_array_type
		   (NULL, builtin_type_char,
		    create_range_type (NULL, builtin_type_int, 0, 32)), NULL);

	      printable_val =
		value_ind (value_cast (parray_of_char,
				       call_function_by_hand (func, 1,
							      &val)));

	      fprintf_filtered (stream, "%s", VALUE_CONTENTS (printable_val));
	      return 0;
	    }
	  /* No special printing function.  Do as best we can. */
	}
      else if (TYPE_CODE (type) == TYPE_CODE_RANGE)
	{
	  struct type *target_type = TYPE_TARGET_TYPE (type);
	  if (TYPE_LENGTH (type) != TYPE_LENGTH (target_type))
	    {
	      /* Obscure case of range type that has different length from
	         its base type.  Perform a conversion, or we will get a
	         nonsense value.  Actually, we could use the same
	         code regardless of lengths; I'm just avoiding a cast. */
	      struct value *v = value_cast (target_type,
					    value_from_contents_and_address
					    (type, valaddr, 0));
	      return ada_val_print_1 (target_type, VALUE_CONTENTS (v), 0, 0,
				      stream, format, 0, recurse + 1, pretty);
	    }
	  else
	    return ada_val_print_1 (TYPE_TARGET_TYPE (type),
				    valaddr0, embedded_offset,
				    address, stream, format, deref_ref,
				    recurse, pretty);
	}
      else
	{
	  format = format ? format : output_format;
	  if (format)
	    {
	      print_scalar_formatted (valaddr, type, format, 0, stream);
	    }
	  else
	    {
	      val_print_type_code_int (type, valaddr, stream);
	      if (ada_is_character_type (type))
		{
		  fputs_filtered (" ", stream);
		  ada_printchar ((unsigned char) unpack_long (type, valaddr),
				 stream);
		}
	    }
	  return 0;
	}

    case TYPE_CODE_ENUM:
      if (format)
	{
	  print_scalar_formatted (valaddr, type, format, 0, stream);
	  break;
	}
      len = TYPE_NFIELDS (type);
      val = unpack_long (type, valaddr);
      for (i = 0; i < len; i++)
	{
	  QUIT;
	  if (val == TYPE_FIELD_BITPOS (type, i))
	    {
	      break;
	    }
	}
      if (i < len)
	{
	  const char *name = ada_enum_name (TYPE_FIELD_NAME (type, i));
	  if (name[0] == '\'')
	    fprintf_filtered (stream, "%ld %s", (long) val, name);
	  else
	    fputs_filtered (name, stream);
	}
      else
	{
	  print_longest (stream, 'd', 0, val);
	}
      break;

    case TYPE_CODE_UNION:
    case TYPE_CODE_STRUCT:
      if (ada_is_bogus_array_descriptor (type))
	{
	  fprintf_filtered (stream, "(...?)");
	  return 0;
	}
      else
	{
	  print_record (type, valaddr, stream, format, recurse, pretty);
	  return 0;
	}

    case TYPE_CODE_ARRAY:
      if (TYPE_LENGTH (type) > 0 && TYPE_LENGTH (TYPE_TARGET_TYPE (type)) > 0)
	{
	  elttype = TYPE_TARGET_TYPE (type);
	  eltlen = TYPE_LENGTH (elttype);
	  len = TYPE_LENGTH (type) / eltlen;

	  /* For an array of chars, print with string syntax.  */
	  if (ada_is_string_type (type) && (format == 0 || format == 's'))
	    {
	      if (prettyprint_arrays)
		{
		  print_spaces_filtered (2 + 2 * recurse, stream);
		}
	      /* If requested, look for the first null char and only print
	         elements up to it.  */
	      if (stop_print_at_null)
		{
		  int temp_len;

		  /* Look for a NULL char. */
		  for (temp_len = 0;
		       temp_len < len && temp_len < print_max
		       && char_at (valaddr, temp_len, eltlen) != 0;
		       temp_len += 1);
		  len = temp_len;
		}

	      printstr (stream, valaddr, len, 0, eltlen);
	    }
	  else
	    {
	      len = 0;
	      fprintf_filtered (stream, "(");
	      print_optional_low_bound (stream, type);
	      if (TYPE_FIELD_BITSIZE (type, 0) > 0)
		val_print_packed_array_elements (type, valaddr, 0, stream,
						 format, recurse, pretty);
	      else
		val_print_array_elements (type, valaddr, address, stream,
					  format, deref_ref, recurse,
					  pretty, 0);
	      fprintf_filtered (stream, ")");
	    }
	  gdb_flush (stream);
	  return len;
	}

    case TYPE_CODE_REF:
      elttype = check_typedef (TYPE_TARGET_TYPE (type));
      if (addressprint)
	{
	  fprintf_filtered (stream, "@");
	  /* Extract an address, assume that the address is unsigned.  */
	  print_address_numeric
	    (extract_unsigned_integer (valaddr,
				       TARGET_PTR_BIT / HOST_CHAR_BIT),
	     1, stream);
	  if (deref_ref)
	    fputs_filtered (": ", stream);
	}
      /* De-reference the reference */
      if (deref_ref)
	{
	  if (TYPE_CODE (elttype) != TYPE_CODE_UNDEF)
	    {
	      LONGEST deref_val_int = (LONGEST)
		unpack_pointer (lookup_pointer_type (builtin_type_void),
				valaddr);
	      if (deref_val_int != 0)
		{
		  struct value *deref_val =
		    ada_value_ind (value_from_longest
				   (lookup_pointer_type (elttype),
				    deref_val_int));
		  val_print (VALUE_TYPE (deref_val),
			     VALUE_CONTENTS (deref_val), 0,
			     VALUE_ADDRESS (deref_val), stream, format,
			     deref_ref, recurse + 1, pretty);
		}
	      else
		fputs_filtered ("(null)", stream);
	    }
	  else
	    fputs_filtered ("???", stream);
	}
      break;
    }
  return 0;
}