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
typedef  char type ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 scalar_t__ TYPE_ADDRESS_CLASS_1 (char*) ; 
 scalar_t__ TYPE_ADDRESS_CLASS_2 (char*) ; 
 int /*<<< orphan*/  TYPE_ARRAY_LOWER_BOUND_TYPE (char*) ; 
 int /*<<< orphan*/  TYPE_ARRAY_UPPER_BOUND_TYPE (char*) ; 
 char* TYPE_CHAIN (char*) ; 
 int /*<<< orphan*/  TYPE_CODE (char*) ; 
#define  TYPE_CODE_ARRAY 152 
#define  TYPE_CODE_BITSTRING 151 
#define  TYPE_CODE_BOOL 150 
#define  TYPE_CODE_CHAR 149 
#define  TYPE_CODE_COMPLEX 148 
#define  TYPE_CODE_ENUM 147 
#define  TYPE_CODE_ERROR 146 
#define  TYPE_CODE_FLT 145 
#define  TYPE_CODE_FUNC 144 
#define  TYPE_CODE_INT 143 
#define  TYPE_CODE_MEMBER 142 
#define  TYPE_CODE_METHOD 141 
#define  TYPE_CODE_NAMESPACE 140 
#define  TYPE_CODE_PTR 139 
#define  TYPE_CODE_RANGE 138 
#define  TYPE_CODE_REF 137 
#define  TYPE_CODE_SET 136 
 scalar_t__ TYPE_CODE_SPACE (char*) ; 
#define  TYPE_CODE_STRING 135 
#define  TYPE_CODE_STRUCT 134 
#define  TYPE_CODE_TEMPLATE 133 
#define  TYPE_CODE_TEMPLATE_ARG 132 
#define  TYPE_CODE_TYPEDEF 131 
#define  TYPE_CODE_UNDEF 130 
#define  TYPE_CODE_UNION 129 
#define  TYPE_CODE_VOID 128 
 scalar_t__ TYPE_CONST (char*) ; 
 char* TYPE_CPLUS_SPECIFIC (char*) ; 
 scalar_t__ TYPE_DATA_SPACE (char*) ; 
 char* TYPE_FIELDS (char*) ; 
 int /*<<< orphan*/  TYPE_FIELD_BITPOS (char*,int) ; 
 int /*<<< orphan*/  TYPE_FIELD_BITSIZE (char*,int) ; 
 char* TYPE_FIELD_NAME (char*,int) ; 
 char* TYPE_FIELD_TYPE (char*,int) ; 
 int /*<<< orphan*/  TYPE_FLAGS (char*) ; 
 TYPE_1__* TYPE_FLOATFORMAT (char*) ; 
 scalar_t__ TYPE_INCOMPLETE (char*) ; 
 int /*<<< orphan*/  TYPE_INSTANCE_FLAGS (char*) ; 
 int /*<<< orphan*/  TYPE_LENGTH (char*) ; 
 char* TYPE_NAME (char*) ; 
 int TYPE_NFIELDS (char*) ; 
 scalar_t__ TYPE_NFN_FIELDS (char*) ; 
 scalar_t__ TYPE_NOSIGN (char*) ; 
 char* TYPE_OBJFILE (char*) ; 
 char* TYPE_POINTER_TYPE (char*) ; 
 scalar_t__ TYPE_PROTOTYPED (char*) ; 
 char* TYPE_REFERENCE_TYPE (char*) ; 
 scalar_t__ TYPE_STATIC (char*) ; 
 scalar_t__ TYPE_STUB (char*) ; 
 char* TYPE_TAG_NAME (char*) ; 
 scalar_t__ TYPE_TARGET_STUB (char*) ; 
 char* TYPE_TARGET_TYPE (char*) ; 
 scalar_t__ TYPE_UNSIGNED (char*) ; 
 scalar_t__ TYPE_VARARGS (char*) ; 
 scalar_t__ TYPE_VECTOR (char*) ; 
 scalar_t__ TYPE_VOLATILE (char*) ; 
 char* TYPE_VPTR_BASETYPE (char*) ; 
 int /*<<< orphan*/  TYPE_VPTR_FIELDNO (char*) ; 
 int /*<<< orphan*/  dont_print_type_obstack ; 
 int /*<<< orphan*/  gdb_print_host_address (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 scalar_t__ obstack_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obstack_begin (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ obstack_next_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obstack_ptr_grow (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_bound_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_cplus_stuff (char*,int) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  printfi_filtered (int,char*,...) ; 
 int /*<<< orphan*/  puts_filtered (char*) ; 

void
recursive_dump_type (struct type *type, int spaces)
{
  int idx;

  if (spaces == 0)
    obstack_begin (&dont_print_type_obstack, 0);

  if (TYPE_NFIELDS (type) > 0
      || (TYPE_CPLUS_SPECIFIC (type) && TYPE_NFN_FIELDS (type) > 0))
    {
      struct type **first_dont_print
      = (struct type **) obstack_base (&dont_print_type_obstack);

      int i = (struct type **) obstack_next_free (&dont_print_type_obstack)
      - first_dont_print;

      while (--i >= 0)
	{
	  if (type == first_dont_print[i])
	    {
	      printfi_filtered (spaces, "type node ");
	      gdb_print_host_address (type, gdb_stdout);
	      printf_filtered (" <same as already seen type>\n");
	      return;
	    }
	}

      obstack_ptr_grow (&dont_print_type_obstack, type);
    }

  printfi_filtered (spaces, "type node ");
  gdb_print_host_address (type, gdb_stdout);
  printf_filtered ("\n");
  printfi_filtered (spaces, "name '%s' (",
		    TYPE_NAME (type) ? TYPE_NAME (type) : "<NULL>");
  gdb_print_host_address (TYPE_NAME (type), gdb_stdout);
  printf_filtered (")\n");
  printfi_filtered (spaces, "tagname '%s' (",
		    TYPE_TAG_NAME (type) ? TYPE_TAG_NAME (type) : "<NULL>");
  gdb_print_host_address (TYPE_TAG_NAME (type), gdb_stdout);
  printf_filtered (")\n");
  printfi_filtered (spaces, "code 0x%x ", TYPE_CODE (type));
  switch (TYPE_CODE (type))
    {
    case TYPE_CODE_UNDEF:
      printf_filtered ("(TYPE_CODE_UNDEF)");
      break;
    case TYPE_CODE_PTR:
      printf_filtered ("(TYPE_CODE_PTR)");
      break;
    case TYPE_CODE_ARRAY:
      printf_filtered ("(TYPE_CODE_ARRAY)");
      break;
    case TYPE_CODE_STRUCT:
      printf_filtered ("(TYPE_CODE_STRUCT)");
      break;
    case TYPE_CODE_UNION:
      printf_filtered ("(TYPE_CODE_UNION)");
      break;
    case TYPE_CODE_ENUM:
      printf_filtered ("(TYPE_CODE_ENUM)");
      break;
    case TYPE_CODE_FUNC:
      printf_filtered ("(TYPE_CODE_FUNC)");
      break;
    case TYPE_CODE_INT:
      printf_filtered ("(TYPE_CODE_INT)");
      break;
    case TYPE_CODE_FLT:
      printf_filtered ("(TYPE_CODE_FLT)");
      break;
    case TYPE_CODE_VOID:
      printf_filtered ("(TYPE_CODE_VOID)");
      break;
    case TYPE_CODE_SET:
      printf_filtered ("(TYPE_CODE_SET)");
      break;
    case TYPE_CODE_RANGE:
      printf_filtered ("(TYPE_CODE_RANGE)");
      break;
    case TYPE_CODE_STRING:
      printf_filtered ("(TYPE_CODE_STRING)");
      break;
    case TYPE_CODE_BITSTRING:
      printf_filtered ("(TYPE_CODE_BITSTRING)");
      break;
    case TYPE_CODE_ERROR:
      printf_filtered ("(TYPE_CODE_ERROR)");
      break;
    case TYPE_CODE_MEMBER:
      printf_filtered ("(TYPE_CODE_MEMBER)");
      break;
    case TYPE_CODE_METHOD:
      printf_filtered ("(TYPE_CODE_METHOD)");
      break;
    case TYPE_CODE_REF:
      printf_filtered ("(TYPE_CODE_REF)");
      break;
    case TYPE_CODE_CHAR:
      printf_filtered ("(TYPE_CODE_CHAR)");
      break;
    case TYPE_CODE_BOOL:
      printf_filtered ("(TYPE_CODE_BOOL)");
      break;
    case TYPE_CODE_COMPLEX:
      printf_filtered ("(TYPE_CODE_COMPLEX)");
      break;
    case TYPE_CODE_TYPEDEF:
      printf_filtered ("(TYPE_CODE_TYPEDEF)");
      break;
    case TYPE_CODE_TEMPLATE:
      printf_filtered ("(TYPE_CODE_TEMPLATE)");
      break;
    case TYPE_CODE_TEMPLATE_ARG:
      printf_filtered ("(TYPE_CODE_TEMPLATE_ARG)");
      break;
    case TYPE_CODE_NAMESPACE:
      printf_filtered ("(TYPE_CODE_NAMESPACE)");
      break;
    default:
      printf_filtered ("(UNKNOWN TYPE CODE)");
      break;
    }
  puts_filtered ("\n");
  printfi_filtered (spaces, "length %d\n", TYPE_LENGTH (type));
  printfi_filtered (spaces, "upper_bound_type 0x%x ",
		    TYPE_ARRAY_UPPER_BOUND_TYPE (type));
  print_bound_type (TYPE_ARRAY_UPPER_BOUND_TYPE (type));
  puts_filtered ("\n");
  printfi_filtered (spaces, "lower_bound_type 0x%x ",
		    TYPE_ARRAY_LOWER_BOUND_TYPE (type));
  print_bound_type (TYPE_ARRAY_LOWER_BOUND_TYPE (type));
  puts_filtered ("\n");
  printfi_filtered (spaces, "objfile ");
  gdb_print_host_address (TYPE_OBJFILE (type), gdb_stdout);
  printf_filtered ("\n");
  printfi_filtered (spaces, "target_type ");
  gdb_print_host_address (TYPE_TARGET_TYPE (type), gdb_stdout);
  printf_filtered ("\n");
  if (TYPE_TARGET_TYPE (type) != NULL)
    {
      recursive_dump_type (TYPE_TARGET_TYPE (type), spaces + 2);
    }
  printfi_filtered (spaces, "pointer_type ");
  gdb_print_host_address (TYPE_POINTER_TYPE (type), gdb_stdout);
  printf_filtered ("\n");
  printfi_filtered (spaces, "reference_type ");
  gdb_print_host_address (TYPE_REFERENCE_TYPE (type), gdb_stdout);
  printf_filtered ("\n");
  printfi_filtered (spaces, "type_chain ");
  gdb_print_host_address (TYPE_CHAIN (type), gdb_stdout);
  printf_filtered ("\n");
  printfi_filtered (spaces, "instance_flags 0x%x", TYPE_INSTANCE_FLAGS (type));
  if (TYPE_CONST (type))
    {
      puts_filtered (" TYPE_FLAG_CONST");
    }
  if (TYPE_VOLATILE (type))
    {
      puts_filtered (" TYPE_FLAG_VOLATILE");
    }
  if (TYPE_CODE_SPACE (type))
    {
      puts_filtered (" TYPE_FLAG_CODE_SPACE");
    }
  if (TYPE_DATA_SPACE (type))
    {
      puts_filtered (" TYPE_FLAG_DATA_SPACE");
    }
  if (TYPE_ADDRESS_CLASS_1 (type))
    {
      puts_filtered (" TYPE_FLAG_ADDRESS_CLASS_1");
    }
  if (TYPE_ADDRESS_CLASS_2 (type))
    {
      puts_filtered (" TYPE_FLAG_ADDRESS_CLASS_2");
    }
  puts_filtered ("\n");
  printfi_filtered (spaces, "flags 0x%x", TYPE_FLAGS (type));
  if (TYPE_UNSIGNED (type))
    {
      puts_filtered (" TYPE_FLAG_UNSIGNED");
    }
  if (TYPE_NOSIGN (type))
    {
      puts_filtered (" TYPE_FLAG_NOSIGN");
    }
  if (TYPE_STUB (type))
    {
      puts_filtered (" TYPE_FLAG_STUB");
    }
  if (TYPE_TARGET_STUB (type))
    {
      puts_filtered (" TYPE_FLAG_TARGET_STUB");
    }
  if (TYPE_STATIC (type))
    {
      puts_filtered (" TYPE_FLAG_STATIC");
    }
  if (TYPE_PROTOTYPED (type))
    {
      puts_filtered (" TYPE_FLAG_PROTOTYPED");
    }
  if (TYPE_INCOMPLETE (type))
    {
      puts_filtered (" TYPE_FLAG_INCOMPLETE");
    }
  if (TYPE_VARARGS (type))
    {
      puts_filtered (" TYPE_FLAG_VARARGS");
    }
  /* This is used for things like AltiVec registers on ppc.  Gcc emits
     an attribute for the array type, which tells whether or not we
     have a vector, instead of a regular array.  */
  if (TYPE_VECTOR (type))
    {
      puts_filtered (" TYPE_FLAG_VECTOR");
    }
  puts_filtered ("\n");
  printfi_filtered (spaces, "nfields %d ", TYPE_NFIELDS (type));
  gdb_print_host_address (TYPE_FIELDS (type), gdb_stdout);
  puts_filtered ("\n");
  for (idx = 0; idx < TYPE_NFIELDS (type); idx++)
    {
      printfi_filtered (spaces + 2,
			"[%d] bitpos %d bitsize %d type ",
			idx, TYPE_FIELD_BITPOS (type, idx),
			TYPE_FIELD_BITSIZE (type, idx));
      gdb_print_host_address (TYPE_FIELD_TYPE (type, idx), gdb_stdout);
      printf_filtered (" name '%s' (",
		       TYPE_FIELD_NAME (type, idx) != NULL
		       ? TYPE_FIELD_NAME (type, idx)
		       : "<NULL>");
      gdb_print_host_address (TYPE_FIELD_NAME (type, idx), gdb_stdout);
      printf_filtered (")\n");
      if (TYPE_FIELD_TYPE (type, idx) != NULL)
	{
	  recursive_dump_type (TYPE_FIELD_TYPE (type, idx), spaces + 4);
	}
    }
  printfi_filtered (spaces, "vptr_basetype ");
  gdb_print_host_address (TYPE_VPTR_BASETYPE (type), gdb_stdout);
  puts_filtered ("\n");
  if (TYPE_VPTR_BASETYPE (type) != NULL)
    {
      recursive_dump_type (TYPE_VPTR_BASETYPE (type), spaces + 2);
    }
  printfi_filtered (spaces, "vptr_fieldno %d\n", TYPE_VPTR_FIELDNO (type));
  switch (TYPE_CODE (type))
    {
    case TYPE_CODE_STRUCT:
      printfi_filtered (spaces, "cplus_stuff ");
      gdb_print_host_address (TYPE_CPLUS_SPECIFIC (type), gdb_stdout);
      puts_filtered ("\n");
      print_cplus_stuff (type, spaces);
      break;

    case TYPE_CODE_FLT:
      printfi_filtered (spaces, "floatformat ");
      if (TYPE_FLOATFORMAT (type) == NULL
	  || TYPE_FLOATFORMAT (type)->name == NULL)
	puts_filtered ("(null)");
      else
	puts_filtered (TYPE_FLOATFORMAT (type)->name);
      puts_filtered ("\n");
      break;

    default:
      /* We have to pick one of the union types to be able print and test
         the value.  Pick cplus_struct_type, even though we know it isn't
         any particular one. */
      printfi_filtered (spaces, "type_specific ");
      gdb_print_host_address (TYPE_CPLUS_SPECIFIC (type), gdb_stdout);
      if (TYPE_CPLUS_SPECIFIC (type) != NULL)
	{
	  printf_filtered (" (unknown data form)");
	}
      printf_filtered ("\n");
      break;

    }
  if (spaces == 0)
    obstack_free (&dont_print_type_obstack, NULL);
}