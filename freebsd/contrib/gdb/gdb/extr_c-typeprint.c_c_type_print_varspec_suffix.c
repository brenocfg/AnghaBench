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
struct ui_file {int dummy; } ;
struct type {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  la_language; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOUND_CANNOT_BE_DETERMINED ; 
 int /*<<< orphan*/  QUIT ; 
 int /*<<< orphan*/  TYPE_ARRAY_UPPER_BOUND_TYPE (struct type*) ; 
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_ARRAY 151 
#define  TYPE_CODE_BITSTRING 150 
#define  TYPE_CODE_BOOL 149 
#define  TYPE_CODE_CHAR 148 
#define  TYPE_CODE_COMPLEX 147 
#define  TYPE_CODE_ENUM 146 
#define  TYPE_CODE_ERROR 145 
#define  TYPE_CODE_FLT 144 
#define  TYPE_CODE_FUNC 143 
#define  TYPE_CODE_INT 142 
#define  TYPE_CODE_MEMBER 141 
#define  TYPE_CODE_METHOD 140 
#define  TYPE_CODE_NAMESPACE 139 
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
 int /*<<< orphan*/  TYPE_FIELD_TYPE (struct type*,int) ; 
 int TYPE_LENGTH (struct type*) ; 
 scalar_t__ TYPE_NAME (struct type*) ; 
 int TYPE_NFIELDS (struct type*) ; 
 int /*<<< orphan*/  TYPE_PROTOTYPED (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  c_print_type (int /*<<< orphan*/ ,char*,struct ui_file*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_type_print_args (struct type*,struct ui_file*) ; 
 TYPE_1__* current_language ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 int /*<<< orphan*/  language_cplus ; 
 int /*<<< orphan*/  wrap_here (char*) ; 

void
c_type_print_varspec_suffix (struct type *type, struct ui_file *stream,
			     int show, int passed_a_ptr, int demangled_args)
{
  if (type == 0)
    return;

  if (TYPE_NAME (type) && show <= 0)
    return;

  QUIT;

  switch (TYPE_CODE (type))
    {
    case TYPE_CODE_ARRAY:
      if (passed_a_ptr)
	fprintf_filtered (stream, ")");

      fprintf_filtered (stream, "[");
      if (TYPE_LENGTH (type) >= 0 && TYPE_LENGTH (TYPE_TARGET_TYPE (type)) > 0
	&& TYPE_ARRAY_UPPER_BOUND_TYPE (type) != BOUND_CANNOT_BE_DETERMINED)
	fprintf_filtered (stream, "%d",
			  (TYPE_LENGTH (type)
			   / TYPE_LENGTH (TYPE_TARGET_TYPE (type))));
      fprintf_filtered (stream, "]");

      c_type_print_varspec_suffix (TYPE_TARGET_TYPE (type), stream, show,
				   0, 0);
      break;

    case TYPE_CODE_MEMBER:
      if (passed_a_ptr)
	fprintf_filtered (stream, ")");
      c_type_print_varspec_suffix (TYPE_TARGET_TYPE (type), stream, show,
				   0, 0);
      break;

    case TYPE_CODE_METHOD:
      if (passed_a_ptr)
	fprintf_filtered (stream, ")");
      c_type_print_varspec_suffix (TYPE_TARGET_TYPE (type), stream, show,
				   0, 0);
      if (passed_a_ptr)
	{
	  c_type_print_args (type, stream);
	}
      break;

    case TYPE_CODE_PTR:
    case TYPE_CODE_REF:
      c_type_print_varspec_suffix (TYPE_TARGET_TYPE (type), stream, show,
				   1, 0);
      break;

    case TYPE_CODE_FUNC:
      if (passed_a_ptr)
	fprintf_filtered (stream, ")");
      if (!demangled_args)
	{
	  int i, len = TYPE_NFIELDS (type);
	  fprintf_filtered (stream, "(");
	  if (len == 0
              && (TYPE_PROTOTYPED (type)
                  || current_language->la_language == language_cplus))
	    {
	      fprintf_filtered (stream, "void");
	    }
	  else
	    for (i = 0; i < len; i++)
	      {
		if (i > 0)
		  {
		    fputs_filtered (", ", stream);
		    wrap_here ("    ");
		  }
		c_print_type (TYPE_FIELD_TYPE (type, i), "", stream, -1, 0);
	      }
	  fprintf_filtered (stream, ")");
	}
      c_type_print_varspec_suffix (TYPE_TARGET_TYPE (type), stream, show,
				   passed_a_ptr, 0);
      break;

    case TYPE_CODE_TYPEDEF:
      c_type_print_varspec_suffix (TYPE_TARGET_TYPE (type), stream, show,
				   passed_a_ptr, 0);
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
    case TYPE_CODE_TEMPLATE:
    case TYPE_CODE_NAMESPACE:
      /* These types do not need a suffix.  They are listed so that
         gcc -Wall will report types that may not have been considered.  */
      break;
    default:
      error ("type not handled in c_type_print_varspec_suffix()");
      break;
    }
}