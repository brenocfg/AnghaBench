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

/* Variables and functions */
 int /*<<< orphan*/  BOUND_CANNOT_BE_DETERMINED ; 
 int /*<<< orphan*/  QUIT ; 
 int /*<<< orphan*/  TYPE_ARRAY_LOWER_BOUND_VALUE (struct type*) ; 
 int /*<<< orphan*/  TYPE_ARRAY_UPPER_BOUND_TYPE (struct type*) ; 
 int /*<<< orphan*/  TYPE_ARRAY_UPPER_BOUND_VALUE (struct type*) ; 
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_ARRAY 150 
#define  TYPE_CODE_BITSTRING 149 
#define  TYPE_CODE_BOOL 148 
#define  TYPE_CODE_CHAR 147 
#define  TYPE_CODE_COMPLEX 146 
#define  TYPE_CODE_ENUM 145 
#define  TYPE_CODE_ERROR 144 
#define  TYPE_CODE_FLT 143 
#define  TYPE_CODE_FUNC 142 
#define  TYPE_CODE_INT 141 
#define  TYPE_CODE_MEMBER 140 
#define  TYPE_CODE_METHOD 139 
#define  TYPE_CODE_PTR 138 
#define  TYPE_CODE_RANGE 137 
#define  TYPE_CODE_REF 136 
#define  TYPE_CODE_SET 135 
#define  TYPE_CODE_STRING 134 
#define  TYPE_CODE_STRUCT 133 
#define  TYPE_CODE_TEMPLATE 132 
#define  TYPE_CODE_TYPEDEF 131 
#define  TYPE_CODE_UNDEF 130 
#define  TYPE_CODE_UNION 129 
#define  TYPE_CODE_VOID 128 
 int /*<<< orphan*/  TYPE_DOMAIN_TYPE (struct type*) ; 
 int /*<<< orphan*/  TYPE_LENGTH (struct type*) ; 
 scalar_t__ TYPE_NAME (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 int /*<<< orphan*/  pascal_type_print_base (int /*<<< orphan*/ ,struct ui_file*,int /*<<< orphan*/ ,int) ; 
 char* type_name_no_tag (int /*<<< orphan*/ ) ; 

void
pascal_type_print_varspec_prefix (struct type *type, struct ui_file *stream,
				  int show, int passed_a_ptr)
{
  char *name;
  if (type == 0)
    return;

  if (TYPE_NAME (type) && show <= 0)
    return;

  QUIT;

  switch (TYPE_CODE (type))
    {
    case TYPE_CODE_PTR:
      fprintf_filtered (stream, "^");
      pascal_type_print_varspec_prefix (TYPE_TARGET_TYPE (type), stream, 0, 1);
      break;			/* pointer should be handled normally in pascal */

    case TYPE_CODE_MEMBER:
      if (passed_a_ptr)
	fprintf_filtered (stream, "(");
      pascal_type_print_varspec_prefix (TYPE_TARGET_TYPE (type), stream, 0, 0);
      fprintf_filtered (stream, " ");
      name = type_name_no_tag (TYPE_DOMAIN_TYPE (type));
      if (name)
	fputs_filtered (name, stream);
      else
	pascal_type_print_base (TYPE_DOMAIN_TYPE (type), stream, 0, passed_a_ptr);
      fprintf_filtered (stream, "::");
      break;

    case TYPE_CODE_METHOD:
      if (passed_a_ptr)
	fprintf_filtered (stream, "(");
      if (TYPE_CODE (TYPE_TARGET_TYPE (type)) != TYPE_CODE_VOID)
	{
	  fprintf_filtered (stream, "function  ");
	}
      else
	{
	  fprintf_filtered (stream, "procedure ");
	}

      if (passed_a_ptr)
	{
	  fprintf_filtered (stream, " ");
	  pascal_type_print_base (TYPE_DOMAIN_TYPE (type), stream, 0, passed_a_ptr);
	  fprintf_filtered (stream, "::");
	}
      break;

    case TYPE_CODE_REF:
      pascal_type_print_varspec_prefix (TYPE_TARGET_TYPE (type), stream, 0, 1);
      fprintf_filtered (stream, "&");
      break;

    case TYPE_CODE_FUNC:
      if (passed_a_ptr)
	fprintf_filtered (stream, "(");

      if (TYPE_CODE (TYPE_TARGET_TYPE (type)) != TYPE_CODE_VOID)
	{
	  fprintf_filtered (stream, "function  ");
	}
      else
	{
	  fprintf_filtered (stream, "procedure ");
	}

      break;

    case TYPE_CODE_ARRAY:
      if (passed_a_ptr)
	fprintf_filtered (stream, "(");
      fprintf_filtered (stream, "array ");
      if (TYPE_LENGTH (type) >= 0 && TYPE_LENGTH (TYPE_TARGET_TYPE (type)) > 0
	&& TYPE_ARRAY_UPPER_BOUND_TYPE (type) != BOUND_CANNOT_BE_DETERMINED)
	fprintf_filtered (stream, "[%d..%d] ",
			  TYPE_ARRAY_LOWER_BOUND_VALUE (type),
			  TYPE_ARRAY_UPPER_BOUND_VALUE (type)
	  );
      fprintf_filtered (stream, "of ");
      break;

    case TYPE_CODE_UNDEF:
    case TYPE_CODE_STRUCT:
    case TYPE_CODE_UNION:
    case TYPE_CODE_ENUM:
    case TYPE_CODE_INT:
    case TYPE_CODE_FLT:
    case TYPE_CODE_VOID:
    case TYPE_CODE_ERROR:
    case TYPE_CODE_CHAR:
    case TYPE_CODE_BOOL:
    case TYPE_CODE_SET:
    case TYPE_CODE_RANGE:
    case TYPE_CODE_STRING:
    case TYPE_CODE_BITSTRING:
    case TYPE_CODE_COMPLEX:
    case TYPE_CODE_TYPEDEF:
    case TYPE_CODE_TEMPLATE:
      /* These types need no prefix.  They are listed here so that
         gcc -Wall will reveal any types that haven't been handled.  */
      break;
    default:
      error ("type not handled in pascal_type_print_varspec_prefix()");
      break;
    }
}