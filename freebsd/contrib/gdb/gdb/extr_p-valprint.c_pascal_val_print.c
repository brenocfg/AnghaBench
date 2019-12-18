#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct value {int dummy; } ;
struct ui_file {int dummy; } ;
struct type {int dummy; } ;
struct symbol {int dummy; } ;
struct minimal_symbol {int dummy; } ;
struct block {int dummy; } ;
typedef  enum val_prettyprint { ____Placeholder_val_prettyprint } val_prettyprint ;
typedef  int ULONGEST ;
struct TYPE_2__ {int /*<<< orphan*/  la_language; } ;
typedef  int LONGEST ;
typedef  void* CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 int /*<<< orphan*/  DEPRECATED_SYMBOL_NAME (struct minimal_symbol*) ; 
 int HOST_CHAR_BIT ; 
 int /*<<< orphan*/  LA_PRINT_CHAR (unsigned char,struct ui_file*) ; 
 int /*<<< orphan*/  LA_PRINT_STRING (struct ui_file*,char*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUIT ; 
 char* SYMBOL_PRINT_NAME (struct minimal_symbol*) ; 
 struct type* SYMBOL_TYPE (struct symbol*) ; 
 void* SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 int TARGET_PTR_BIT ; 
 int const TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_ARRAY 145 
#define  TYPE_CODE_BITSTRING 144 
#define  TYPE_CODE_BOOL 143 
#define  TYPE_CODE_CHAR 142 
#define  TYPE_CODE_ENUM 141 
#define  TYPE_CODE_ERROR 140 
#define  TYPE_CODE_FLT 139 
#define  TYPE_CODE_FUNC 138 
#define  TYPE_CODE_INT 137 
#define  TYPE_CODE_MEMBER 136 
 int const TYPE_CODE_METHOD ; 
#define  TYPE_CODE_PTR 135 
#define  TYPE_CODE_RANGE 134 
#define  TYPE_CODE_REF 133 
#define  TYPE_CODE_SET 132 
#define  TYPE_CODE_STRUCT 131 
#define  TYPE_CODE_UNDEF 130 
#define  TYPE_CODE_UNION 129 
#define  TYPE_CODE_VOID 128 
 int /*<<< orphan*/  TYPE_DOMAIN_TYPE (struct type*) ; 
 int TYPE_FIELD_BITPOS (struct type*,unsigned int) ; 
 char* TYPE_FIELD_NAME (struct type*,unsigned int) ; 
 struct type* TYPE_FIELD_TYPE (struct type*,unsigned int) ; 
 struct type* TYPE_INDEX_TYPE (struct type*) ; 
 int TYPE_LENGTH (struct type*) ; 
 unsigned int TYPE_NFIELDS (struct type*) ; 
 int /*<<< orphan*/  TYPE_STUB (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (struct type*) ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 unsigned int VTBL_FNADDR_OFFSET ; 
 int /*<<< orphan*/  addressprint ; 
 int /*<<< orphan*/  builtin_type_void ; 
 struct type* check_typedef (struct type*) ; 
 int /*<<< orphan*/  common_val_print (struct value*,struct ui_file*,int,int,int,int) ; 
 TYPE_1__* current_language ; 
 int /*<<< orphan*/  demangle ; 
 int /*<<< orphan*/  error (char*,...) ; 
 void* extract_unsigned_integer (char*,int) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 int /*<<< orphan*/  gdb_flush (struct ui_file*) ; 
 int get_discrete_bounds (struct type*,int*,int*) ; 
 int /*<<< orphan*/  is_pascal_string_type (struct type*,int*,int*,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  language_m2 ; 
 struct minimal_symbol* lookup_minimal_symbol_by_pc (void*) ; 
 struct type* lookup_pointer_type (int /*<<< orphan*/ ) ; 
 struct symbol* lookup_symbol (int /*<<< orphan*/ ,struct block*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int output_format ; 
 int /*<<< orphan*/  pascal_object_is_vtbl_member (struct type*) ; 
 int /*<<< orphan*/  pascal_object_is_vtbl_ptr_type (struct type*) ; 
 int /*<<< orphan*/  pascal_object_print_class_member (char*,int /*<<< orphan*/ ,struct ui_file*,char*) ; 
 int /*<<< orphan*/  pascal_object_print_class_method (char*,struct type*,struct ui_file*) ; 
 int /*<<< orphan*/  pascal_object_print_value_fields (struct type*,char*,void*,struct ui_file*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prettyprint_arrays ; 
 int /*<<< orphan*/  print_address_demangle (void*,struct ui_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_address_numeric (void*,int,struct ui_file*) ; 
 int /*<<< orphan*/  print_floating (char*,struct type*,struct ui_file*) ; 
 int /*<<< orphan*/  print_longest (struct ui_file*,char,int /*<<< orphan*/ ,int) ; 
 unsigned int print_max ; 
 int /*<<< orphan*/  print_scalar_formatted (char*,struct type*,int,int /*<<< orphan*/ ,struct ui_file*) ; 
 int /*<<< orphan*/  print_spaces_filtered (int,struct ui_file*) ; 
 int /*<<< orphan*/  print_type_scalar (struct type*,int,struct ui_file*) ; 
 int /*<<< orphan*/  read_memory (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  stop_print_at_null ; 
 int /*<<< orphan*/  type_print (struct type*,char*,struct ui_file*,int) ; 
 int /*<<< orphan*/  unionprint ; 
 int unpack_long (struct type*,char*) ; 
 void* unpack_pointer (struct type*,char*) ; 
 int /*<<< orphan*/  val_print_array_elements (struct type*,char*,void*,struct ui_file*,int,int,int,int,unsigned int) ; 
 unsigned int val_print_string (void*,int,int,struct ui_file*) ; 
 int /*<<< orphan*/  val_print_type_code_int (struct type*,char*,struct ui_file*) ; 
 struct value* value_at (struct type*,void*,int /*<<< orphan*/ *) ; 
 int value_bit_index (struct type*,char*,int) ; 
 int /*<<< orphan*/  vtblprint ; 
 int /*<<< orphan*/  xfree (void*) ; 
 void* xmalloc (int) ; 

int
pascal_val_print (struct type *type, char *valaddr, int embedded_offset,
		  CORE_ADDR address, struct ui_file *stream, int format,
		  int deref_ref, int recurse, enum val_prettyprint pretty)
{
  unsigned int i = 0;	/* Number of characters printed */
  unsigned len;
  struct type *elttype;
  unsigned eltlen;
  int length_pos, length_size, string_pos;
  int char_size;
  LONGEST val;
  CORE_ADDR addr;

  CHECK_TYPEDEF (type);
  switch (TYPE_CODE (type))
    {
    case TYPE_CODE_ARRAY:
      if (TYPE_LENGTH (type) > 0 && TYPE_LENGTH (TYPE_TARGET_TYPE (type)) > 0)
	{
	  elttype = check_typedef (TYPE_TARGET_TYPE (type));
	  eltlen = TYPE_LENGTH (elttype);
	  len = TYPE_LENGTH (type) / eltlen;
	  if (prettyprint_arrays)
	    {
	      print_spaces_filtered (2 + 2 * recurse, stream);
	    }
	  /* For an array of chars, print with string syntax.  */
	  if (eltlen == 1 &&
	      ((TYPE_CODE (elttype) == TYPE_CODE_INT)
	       || ((current_language->la_language == language_m2)
		   && (TYPE_CODE (elttype) == TYPE_CODE_CHAR)))
	      && (format == 0 || format == 's'))
	    {
	      /* If requested, look for the first null char and only print
	         elements up to it.  */
	      if (stop_print_at_null)
		{
		  unsigned int temp_len;

		  /* Look for a NULL char. */
		  for (temp_len = 0;
		       (valaddr + embedded_offset)[temp_len]
		       && temp_len < len && temp_len < print_max;
		       temp_len++);
		  len = temp_len;
		}

	      LA_PRINT_STRING (stream, valaddr + embedded_offset, len, 1, 0);
	      i = len;
	    }
	  else
	    {
	      fprintf_filtered (stream, "{");
	      /* If this is a virtual function table, print the 0th
	         entry specially, and the rest of the members normally.  */
	      if (pascal_object_is_vtbl_ptr_type (elttype))
		{
		  i = 1;
		  fprintf_filtered (stream, "%d vtable entries", len - 1);
		}
	      else
		{
		  i = 0;
		}
	      val_print_array_elements (type, valaddr + embedded_offset, address, stream,
				     format, deref_ref, recurse, pretty, i);
	      fprintf_filtered (stream, "}");
	    }
	  break;
	}
      /* Array of unspecified length: treat like pointer to first elt.  */
      addr = address;
      goto print_unpacked_pointer;

    case TYPE_CODE_PTR:
      if (format && format != 's')
	{
	  print_scalar_formatted (valaddr + embedded_offset, type, format, 0, stream);
	  break;
	}
      if (vtblprint && pascal_object_is_vtbl_ptr_type (type))
	{
	  /* Print the unmangled name if desired.  */
	  /* Print vtable entry - we only get here if we ARE using
	     -fvtable_thunks.  (Otherwise, look under TYPE_CODE_STRUCT.) */
	  /* Extract the address, assume that it is unsigned.  */
	  print_address_demangle (extract_unsigned_integer (valaddr + embedded_offset, TYPE_LENGTH (type)),
				  stream, demangle);
	  break;
	}
      elttype = check_typedef (TYPE_TARGET_TYPE (type));
      if (TYPE_CODE (elttype) == TYPE_CODE_METHOD)
	{
	  pascal_object_print_class_method (valaddr + embedded_offset, type, stream);
	}
      else if (TYPE_CODE (elttype) == TYPE_CODE_MEMBER)
	{
	  pascal_object_print_class_member (valaddr + embedded_offset,
				 TYPE_DOMAIN_TYPE (TYPE_TARGET_TYPE (type)),
					    stream, "&");
	}
      else
	{
	  addr = unpack_pointer (type, valaddr + embedded_offset);
	print_unpacked_pointer:
	  elttype = check_typedef (TYPE_TARGET_TYPE (type));

	  if (TYPE_CODE (elttype) == TYPE_CODE_FUNC)
	    {
	      /* Try to print what function it points to.  */
	      print_address_demangle (addr, stream, demangle);
	      /* Return value is irrelevant except for string pointers.  */
	      return (0);
	    }

	  if (addressprint && format != 's')
	    {
	      print_address_numeric (addr, 1, stream);
	    }

	  /* For a pointer to char or unsigned char, also print the string
	     pointed to, unless pointer is null.  */
	  if (TYPE_LENGTH (elttype) == 1
	      && TYPE_CODE (elttype) == TYPE_CODE_INT
	      && (format == 0 || format == 's')
	      && addr != 0)
	    {
	      /* no wide string yet */
	      i = val_print_string (addr, -1, 1, stream);
	    }
	  /* also for pointers to pascal strings */
	  /* Note: this is Free Pascal specific:
	     as GDB does not recognize stabs pascal strings
	     Pascal strings are mapped to records
	     with lowercase names PM  */
          if (is_pascal_string_type (elttype, &length_pos, &length_size,
                                     &string_pos, &char_size, NULL)
	      && addr != 0)
	    {
	      ULONGEST string_length;
              void *buffer;
              buffer = xmalloc (length_size);
              read_memory (addr + length_pos, buffer, length_size);
	      string_length = extract_unsigned_integer (buffer, length_size);
              xfree (buffer);
              i = val_print_string (addr + string_pos, string_length, char_size, stream);
	    }
	  else if (pascal_object_is_vtbl_member (type))
	    {
	      /* print vtbl's nicely */
	      CORE_ADDR vt_address = unpack_pointer (type, valaddr + embedded_offset);

	      struct minimal_symbol *msymbol =
	      lookup_minimal_symbol_by_pc (vt_address);
	      if ((msymbol != NULL)
		  && (vt_address == SYMBOL_VALUE_ADDRESS (msymbol)))
		{
		  fputs_filtered (" <", stream);
		  fputs_filtered (SYMBOL_PRINT_NAME (msymbol), stream);
		  fputs_filtered (">", stream);
		}
	      if (vt_address && vtblprint)
		{
		  struct value *vt_val;
		  struct symbol *wsym = (struct symbol *) NULL;
		  struct type *wtype;
		  struct block *block = (struct block *) NULL;
		  int is_this_fld;

		  if (msymbol != NULL)
		    wsym = lookup_symbol (DEPRECATED_SYMBOL_NAME (msymbol), block,
					  VAR_DOMAIN, &is_this_fld, NULL);

		  if (wsym)
		    {
		      wtype = SYMBOL_TYPE (wsym);
		    }
		  else
		    {
		      wtype = TYPE_TARGET_TYPE (type);
		    }
		  vt_val = value_at (wtype, vt_address, NULL);
		  common_val_print (vt_val, stream, format, deref_ref,
				    recurse + 1, pretty);
		  if (pretty)
		    {
		      fprintf_filtered (stream, "\n");
		      print_spaces_filtered (2 + 2 * recurse, stream);
		    }
		}
	    }

	  /* Return number of characters printed, including the terminating
	     '\0' if we reached the end.  val_print_string takes care including
	     the terminating '\0' if necessary.  */
	  return i;
	}
      break;

    case TYPE_CODE_MEMBER:
      error ("not implemented: member type in pascal_val_print");
      break;

    case TYPE_CODE_REF:
      elttype = check_typedef (TYPE_TARGET_TYPE (type));
      if (TYPE_CODE (elttype) == TYPE_CODE_MEMBER)
	{
	  pascal_object_print_class_member (valaddr + embedded_offset,
					    TYPE_DOMAIN_TYPE (elttype),
					    stream, "");
	  break;
	}
      if (addressprint)
	{
	  fprintf_filtered (stream, "@");
	  /* Extract the address, assume that it is unsigned.  */
	  print_address_numeric
	    (extract_unsigned_integer (valaddr + embedded_offset,
				       TARGET_PTR_BIT / HOST_CHAR_BIT),
	     1, stream);
	  if (deref_ref)
	    fputs_filtered (": ", stream);
	}
      /* De-reference the reference.  */
      if (deref_ref)
	{
	  if (TYPE_CODE (elttype) != TYPE_CODE_UNDEF)
	    {
	      struct value *deref_val =
	      value_at
	      (TYPE_TARGET_TYPE (type),
	       unpack_pointer (lookup_pointer_type (builtin_type_void),
			       valaddr + embedded_offset),
	       NULL);
	      common_val_print (deref_val, stream, format, deref_ref,
				recurse + 1, pretty);
	    }
	  else
	    fputs_filtered ("???", stream);
	}
      break;

    case TYPE_CODE_UNION:
      if (recurse && !unionprint)
	{
	  fprintf_filtered (stream, "{...}");
	  break;
	}
      /* Fall through.  */
    case TYPE_CODE_STRUCT:
      if (vtblprint && pascal_object_is_vtbl_ptr_type (type))
	{
	  /* Print the unmangled name if desired.  */
	  /* Print vtable entry - we only get here if NOT using
	     -fvtable_thunks.  (Otherwise, look under TYPE_CODE_PTR.) */
	  /* Extract the address, assume that it is unsigned.  */
	  print_address_demangle
	    (extract_unsigned_integer (valaddr + embedded_offset + TYPE_FIELD_BITPOS (type, VTBL_FNADDR_OFFSET) / 8,
				       TYPE_LENGTH (TYPE_FIELD_TYPE (type, VTBL_FNADDR_OFFSET))),
	     stream, demangle);
	}
      else
	{
          if (is_pascal_string_type (type, &length_pos, &length_size,
                                     &string_pos, &char_size, NULL))
	    {
	      len = extract_unsigned_integer (valaddr + embedded_offset + length_pos, length_size);
	      LA_PRINT_STRING (stream, valaddr + embedded_offset + string_pos, len, char_size, 0);
	    }
	  else
	    pascal_object_print_value_fields (type, valaddr + embedded_offset, address, stream, format,
					      recurse, pretty, NULL, 0);
	}
      break;

    case TYPE_CODE_ENUM:
      if (format)
	{
	  print_scalar_formatted (valaddr + embedded_offset, type, format, 0, stream);
	  break;
	}
      len = TYPE_NFIELDS (type);
      val = unpack_long (type, valaddr + embedded_offset);
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
	  fputs_filtered (TYPE_FIELD_NAME (type, i), stream);
	}
      else
	{
	  print_longest (stream, 'd', 0, val);
	}
      break;

    case TYPE_CODE_FUNC:
      if (format)
	{
	  print_scalar_formatted (valaddr + embedded_offset, type, format, 0, stream);
	  break;
	}
      /* FIXME, we should consider, at least for ANSI C language, eliminating
         the distinction made between FUNCs and POINTERs to FUNCs.  */
      fprintf_filtered (stream, "{");
      type_print (type, "", stream, -1);
      fprintf_filtered (stream, "} ");
      /* Try to print what function it points to, and its address.  */
      print_address_demangle (address, stream, demangle);
      break;

    case TYPE_CODE_BOOL:
      format = format ? format : output_format;
      if (format)
	print_scalar_formatted (valaddr + embedded_offset, type, format, 0, stream);
      else
	{
	  val = unpack_long (type, valaddr + embedded_offset);
	  if (val == 0)
	    fputs_filtered ("false", stream);
	  else if (val == 1)
	    fputs_filtered ("true", stream);
	  else
	    {
	      fputs_filtered ("true (", stream);
	      fprintf_filtered (stream, "%ld)", (long int) val);
	    }
	}
      break;

    case TYPE_CODE_RANGE:
      /* FIXME: create_range_type does not set the unsigned bit in a
         range type (I think it probably should copy it from the target
         type), so we won't print values which are too large to
         fit in a signed integer correctly.  */
      /* FIXME: Doesn't handle ranges of enums correctly.  (Can't just
         print with the target type, though, because the size of our type
         and the target type might differ).  */
      /* FALLTHROUGH */

    case TYPE_CODE_INT:
      format = format ? format : output_format;
      if (format)
	{
	  print_scalar_formatted (valaddr + embedded_offset, type, format, 0, stream);
	}
      else
	{
	  val_print_type_code_int (type, valaddr + embedded_offset, stream);
	}
      break;

    case TYPE_CODE_CHAR:
      format = format ? format : output_format;
      if (format)
	{
	  print_scalar_formatted (valaddr + embedded_offset, type, format, 0, stream);
	}
      else
	{
	  val = unpack_long (type, valaddr + embedded_offset);
	  if (TYPE_UNSIGNED (type))
	    fprintf_filtered (stream, "%u", (unsigned int) val);
	  else
	    fprintf_filtered (stream, "%d", (int) val);
	  fputs_filtered (" ", stream);
	  LA_PRINT_CHAR ((unsigned char) val, stream);
	}
      break;

    case TYPE_CODE_FLT:
      if (format)
	{
	  print_scalar_formatted (valaddr + embedded_offset, type, format, 0, stream);
	}
      else
	{
	  print_floating (valaddr + embedded_offset, type, stream);
	}
      break;

    case TYPE_CODE_BITSTRING:
    case TYPE_CODE_SET:
      elttype = TYPE_INDEX_TYPE (type);
      CHECK_TYPEDEF (elttype);
      if (TYPE_STUB (elttype))
	{
	  fprintf_filtered (stream, "<incomplete type>");
	  gdb_flush (stream);
	  break;
	}
      else
	{
	  struct type *range = elttype;
	  LONGEST low_bound, high_bound;
	  int i;
	  int is_bitstring = TYPE_CODE (type) == TYPE_CODE_BITSTRING;
	  int need_comma = 0;

	  if (is_bitstring)
	    fputs_filtered ("B'", stream);
	  else
	    fputs_filtered ("[", stream);

	  i = get_discrete_bounds (range, &low_bound, &high_bound);
	maybe_bad_bstring:
	  if (i < 0)
	    {
	      fputs_filtered ("<error value>", stream);
	      goto done;
	    }

	  for (i = low_bound; i <= high_bound; i++)
	    {
	      int element = value_bit_index (type, valaddr + embedded_offset, i);
	      if (element < 0)
		{
		  i = element;
		  goto maybe_bad_bstring;
		}
	      if (is_bitstring)
		fprintf_filtered (stream, "%d", element);
	      else if (element)
		{
		  if (need_comma)
		    fputs_filtered (", ", stream);
		  print_type_scalar (range, i, stream);
		  need_comma = 1;

		  if (i + 1 <= high_bound && value_bit_index (type, valaddr + embedded_offset, ++i))
		    {
		      int j = i;
		      fputs_filtered ("..", stream);
		      while (i + 1 <= high_bound
			     && value_bit_index (type, valaddr + embedded_offset, ++i))
			j = i;
		      print_type_scalar (range, j, stream);
		    }
		}
	    }
	done:
	  if (is_bitstring)
	    fputs_filtered ("'", stream);
	  else
	    fputs_filtered ("]", stream);
	}
      break;

    case TYPE_CODE_VOID:
      fprintf_filtered (stream, "void");
      break;

    case TYPE_CODE_ERROR:
      fprintf_filtered (stream, "<error type>");
      break;

    case TYPE_CODE_UNDEF:
      /* This happens (without TYPE_FLAG_STUB set) on systems which don't use
         dbx xrefs (NO_DBX_XREFS in gcc) if a file has a "struct foo *bar"
         and no complete type for struct foo in that file.  */
      fprintf_filtered (stream, "<incomplete type>");
      break;

    default:
      error ("Invalid pascal type code %d in symbol table.", TYPE_CODE (type));
    }
  gdb_flush (stream);
  return (0);
}