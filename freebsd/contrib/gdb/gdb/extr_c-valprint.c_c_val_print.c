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
struct TYPE_2__ {int /*<<< orphan*/  la_language; } ;
typedef  int LONGEST ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 int /*<<< orphan*/  DEPRECATED_SYMBOL_NAME (struct minimal_symbol*) ; 
 int /*<<< orphan*/  LA_PRINT_CHAR (unsigned char,struct ui_file*) ; 
 int /*<<< orphan*/  LA_PRINT_STRING (struct ui_file*,char*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUIT ; 
 char* SYMBOL_PRINT_NAME (struct minimal_symbol*) ; 
 struct type* SYMBOL_TYPE (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_ARRAY 145 
#define  TYPE_CODE_BOOL 144 
#define  TYPE_CODE_CHAR 143 
#define  TYPE_CODE_COMPLEX 142 
#define  TYPE_CODE_ENUM 141 
#define  TYPE_CODE_ERROR 140 
#define  TYPE_CODE_FLT 139 
#define  TYPE_CODE_FUNC 138 
#define  TYPE_CODE_INT 137 
#define  TYPE_CODE_MEMBER 136 
#define  TYPE_CODE_METHOD 135 
#define  TYPE_CODE_PTR 134 
#define  TYPE_CODE_RANGE 133 
#define  TYPE_CODE_REF 132 
#define  TYPE_CODE_STRUCT 131 
#define  TYPE_CODE_UNDEF 130 
#define  TYPE_CODE_UNION 129 
#define  TYPE_CODE_VOID 128 
 int /*<<< orphan*/  TYPE_DOMAIN_TYPE (struct type*) ; 
 int TYPE_FIELD_BITPOS (struct type*,unsigned int) ; 
 char* TYPE_FIELD_NAME (struct type*,unsigned int) ; 
 struct type* TYPE_FIELD_TYPE (struct type*,unsigned int) ; 
 int TYPE_LENGTH (struct type*) ; 
 unsigned int TYPE_NFIELDS (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (struct type*) ; 
 char* VALUE_CONTENTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 unsigned int VTBL_FNADDR_OFFSET ; 
 int /*<<< orphan*/  addressprint ; 
 struct type* builtin_type_void ; 
 struct type* check_typedef (struct type*) ; 
 int /*<<< orphan*/  common_val_print (struct value*,struct ui_file*,int,int,int,int) ; 
 int /*<<< orphan*/  cp_is_vtbl_member (struct type*) ; 
 int /*<<< orphan*/  cp_is_vtbl_ptr_type (struct type*) ; 
 int /*<<< orphan*/  cp_print_class_member (char*,int /*<<< orphan*/ ,struct ui_file*,char*) ; 
 int /*<<< orphan*/  cp_print_class_method (char*,struct type*,struct ui_file*) ; 
 int /*<<< orphan*/  cp_print_value_fields (struct type*,struct type*,char*,int,int /*<<< orphan*/ ,struct ui_file*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* current_language ; 
 int /*<<< orphan*/  demangle ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  extract_typed_address (char*,struct type*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 int /*<<< orphan*/  gdb_flush (struct ui_file*) ; 
 int /*<<< orphan*/  language_m2 ; 
 struct minimal_symbol* lookup_minimal_symbol_by_pc (int /*<<< orphan*/ ) ; 
 struct type* lookup_pointer_type (struct type*) ; 
 struct symbol* lookup_symbol (int /*<<< orphan*/ ,struct block*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int output_format ; 
 int /*<<< orphan*/  prettyprint_arrays ; 
 int /*<<< orphan*/  print_address_demangle (int /*<<< orphan*/ ,struct ui_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_address_numeric (int /*<<< orphan*/ ,int,struct ui_file*) ; 
 int /*<<< orphan*/  print_floating (char*,struct type*,struct ui_file*) ; 
 int /*<<< orphan*/  print_function_pointer_address (int /*<<< orphan*/ ,struct ui_file*) ; 
 int /*<<< orphan*/  print_longest (struct ui_file*,char,int /*<<< orphan*/ ,int) ; 
 unsigned int print_max ; 
 int /*<<< orphan*/  print_scalar_formatted (char*,struct type*,int,int /*<<< orphan*/ ,struct ui_file*) ; 
 int /*<<< orphan*/  print_spaces_filtered (int,struct ui_file*) ; 
 int /*<<< orphan*/  stop_print_at_null ; 
 int /*<<< orphan*/  type_print (struct type*,char*,struct ui_file*,int) ; 
 int /*<<< orphan*/  unionprint ; 
 int unpack_long (struct type*,char*) ; 
 int /*<<< orphan*/  unpack_pointer (struct type*,char*) ; 
 int /*<<< orphan*/  val_print_array_elements (struct type*,char*,int /*<<< orphan*/ ,struct ui_file*,int,int,int,int,unsigned int) ; 
 unsigned int val_print_string (int /*<<< orphan*/ ,int,int,struct ui_file*) ; 
 int /*<<< orphan*/  val_print_type_code_int (struct type*,char*,struct ui_file*) ; 
 int /*<<< orphan*/  value_addr (struct value*) ; 
 struct value* value_at (struct type*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtblprint ; 

int
c_val_print (struct type *type, char *valaddr, int embedded_offset,
	     CORE_ADDR address, struct ui_file *stream, int format,
	     int deref_ref, int recurse, enum val_prettyprint pretty)
{
  unsigned int i = 0;	/* Number of characters printed */
  unsigned len;
  struct type *elttype;
  unsigned eltlen;
  LONGEST val;
  CORE_ADDR addr;

  CHECK_TYPEDEF (type);
  switch (TYPE_CODE (type))
    {
    case TYPE_CODE_ARRAY:
      elttype = check_typedef (TYPE_TARGET_TYPE (type));
      if (TYPE_LENGTH (type) > 0 && TYPE_LENGTH (TYPE_TARGET_TYPE (type)) > 0)
	{
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

	      LA_PRINT_STRING (stream, valaddr + embedded_offset, len, eltlen, 0);
	      i = len;
	    }
	  else
	    {
	      fprintf_filtered (stream, "{");
	      /* If this is a virtual function table, print the 0th
	         entry specially, and the rest of the members normally.  */
	      if (cp_is_vtbl_ptr_type (elttype))
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
      if (vtblprint && cp_is_vtbl_ptr_type (type))
	{
	  /* Print the unmangled name if desired.  */
	  /* Print vtable entry - we only get here if we ARE using
	     -fvtable_thunks.  (Otherwise, look under TYPE_CODE_STRUCT.) */
	  CORE_ADDR addr
	    = extract_typed_address (valaddr + embedded_offset, type);
	  print_function_pointer_address (addr, stream);
	  break;
	}
      elttype = check_typedef (TYPE_TARGET_TYPE (type));
      if (TYPE_CODE (elttype) == TYPE_CODE_METHOD)
	{
	  cp_print_class_method (valaddr + embedded_offset, type, stream);
	}
      else if (TYPE_CODE (elttype) == TYPE_CODE_MEMBER)
	{
	  cp_print_class_member (valaddr + embedded_offset,
				 TYPE_DOMAIN_TYPE (TYPE_TARGET_TYPE (type)),
				 stream, "&");
	}
      else
	{
	  addr = unpack_pointer (type, valaddr + embedded_offset);
	print_unpacked_pointer:

	  if (TYPE_CODE (elttype) == TYPE_CODE_FUNC)
	    {
	      /* Try to print what function it points to.  */
	      print_function_pointer_address (addr, stream);
	      /* Return value is irrelevant except for string pointers.  */
	      return (0);
	    }

	  if (addressprint && format != 's')
	    {
	      print_address_numeric (addr, 1, stream);
	    }

	  /* For a pointer to char or unsigned char, also print the string
	     pointed to, unless pointer is null.  */
	  /* FIXME: need to handle wchar_t here... */

	  if (TYPE_LENGTH (elttype) == 1
	      && TYPE_CODE (elttype) == TYPE_CODE_INT
	      && (format == 0 || format == 's')
	      && addr != 0)
	    {
	      i = val_print_string (addr, -1, TYPE_LENGTH (elttype), stream);
	    }
	  else if (cp_is_vtbl_member (type))
	    {
	      /* print vtbl's nicely */
	      CORE_ADDR vt_address = unpack_pointer (type, valaddr + embedded_offset);

	      struct minimal_symbol *msymbol =
	      lookup_minimal_symbol_by_pc (vt_address);
	      if ((msymbol != NULL) &&
		  (vt_address == SYMBOL_VALUE_ADDRESS (msymbol)))
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
		  common_val_print (vt_val, stream, format,
				    deref_ref, recurse + 1, pretty);
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
      error ("not implemented: member type in c_val_print");
      break;

    case TYPE_CODE_REF:
      elttype = check_typedef (TYPE_TARGET_TYPE (type));
      if (TYPE_CODE (elttype) == TYPE_CODE_MEMBER)
	{
	  cp_print_class_member (valaddr + embedded_offset,
				 TYPE_DOMAIN_TYPE (elttype),
				 stream, "");
	  break;
	}
      if (addressprint)
	{
	  CORE_ADDR addr
	    = extract_typed_address (valaddr + embedded_offset, type);
	  fprintf_filtered (stream, "@");
	  print_address_numeric (addr, 1, stream);
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
				recurse, pretty);
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
      /*FIXME: Abstract this away */
      if (vtblprint && cp_is_vtbl_ptr_type (type))
	{
	  /* Print the unmangled name if desired.  */
	  /* Print vtable entry - we only get here if NOT using
	     -fvtable_thunks.  (Otherwise, look under TYPE_CODE_PTR.) */
	  int offset = (embedded_offset +
			TYPE_FIELD_BITPOS (type, VTBL_FNADDR_OFFSET) / 8);
	  struct type *field_type = TYPE_FIELD_TYPE (type, VTBL_FNADDR_OFFSET);
	  CORE_ADDR addr
	    = extract_typed_address (valaddr + offset, field_type);

	  print_function_pointer_address (addr, stream);
	}
      else
	cp_print_value_fields (type, type, valaddr, embedded_offset, address, stream, format,
			       recurse, pretty, NULL, 0);
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
	    print_longest (stream, 'd', 0, val);
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
	  /* C and C++ has no single byte int type, char is used instead.
	     Since we don't know whether the value is really intended to
	     be used as an integer or a character, print the character
	     equivalent as well. */
	  if (TYPE_LENGTH (type) == 1)
	    {
	      fputs_filtered (" ", stream);
	      LA_PRINT_CHAR ((unsigned char) unpack_long (type, valaddr + embedded_offset),
			     stream);
	    }
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

    case TYPE_CODE_METHOD:
      {
	struct value *v = value_at (type, address, NULL);
	cp_print_class_method (VALUE_CONTENTS (value_addr (v)),
			       lookup_pointer_type (type), stream);
	break;
      }

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

    case TYPE_CODE_COMPLEX:
      if (format)
	print_scalar_formatted (valaddr + embedded_offset,
				TYPE_TARGET_TYPE (type),
				format, 0, stream);
      else
	print_floating (valaddr + embedded_offset, TYPE_TARGET_TYPE (type),
			stream);
      fprintf_filtered (stream, " + ");
      if (format)
	print_scalar_formatted (valaddr + embedded_offset
				+ TYPE_LENGTH (TYPE_TARGET_TYPE (type)),
				TYPE_TARGET_TYPE (type),
				format, 0, stream);
      else
	print_floating (valaddr + embedded_offset
			+ TYPE_LENGTH (TYPE_TARGET_TYPE (type)),
			TYPE_TARGET_TYPE (type),
			stream);
      fprintf_filtered (stream, " * I");
      break;

    default:
      error ("Invalid C/C++ type code %d in symbol table.", TYPE_CODE (type));
    }
  gdb_flush (stream);
  return (0);
}