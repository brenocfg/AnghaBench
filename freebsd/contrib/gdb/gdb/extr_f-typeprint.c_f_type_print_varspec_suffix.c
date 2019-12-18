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
 int BOUND_FETCH_ERROR ; 
 int /*<<< orphan*/  QUIT ; 
 int /*<<< orphan*/  TYPE_ARRAY_UPPER_BOUND_TYPE (struct type*) ; 
 int const TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_ARRAY 149 
#define  TYPE_CODE_BITSTRING 148 
#define  TYPE_CODE_BOOL 147 
#define  TYPE_CODE_CHAR 146 
#define  TYPE_CODE_COMPLEX 145 
#define  TYPE_CODE_ENUM 144 
#define  TYPE_CODE_ERROR 143 
#define  TYPE_CODE_FLT 142 
#define  TYPE_CODE_FUNC 141 
#define  TYPE_CODE_INT 140 
#define  TYPE_CODE_MEMBER 139 
#define  TYPE_CODE_METHOD 138 
#define  TYPE_CODE_PTR 137 
#define  TYPE_CODE_RANGE 136 
#define  TYPE_CODE_REF 135 
#define  TYPE_CODE_SET 134 
#define  TYPE_CODE_STRING 133 
#define  TYPE_CODE_STRUCT 132 
#define  TYPE_CODE_TYPEDEF 131 
#define  TYPE_CODE_UNDEF 130 
#define  TYPE_CODE_UNION 129 
#define  TYPE_CODE_VOID 128 
 scalar_t__ TYPE_NAME (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int f77_get_dynamic_lowerbound (struct type*,int*) ; 
 int f77_get_dynamic_upperbound (struct type*,int*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 

__attribute__((used)) static void
f_type_print_varspec_suffix (struct type *type, struct ui_file *stream,
			     int show, int passed_a_ptr, int demangled_args)
{
  int upper_bound, lower_bound;
  int lower_bound_was_default = 0;
  static int arrayprint_recurse_level = 0;
  int retcode;

  if (type == 0)
    return;

  if (TYPE_NAME (type) && show <= 0)
    return;

  QUIT;

  switch (TYPE_CODE (type))
    {
    case TYPE_CODE_ARRAY:
      arrayprint_recurse_level++;

      if (arrayprint_recurse_level == 1)
	fprintf_filtered (stream, "(");

      if (TYPE_CODE (TYPE_TARGET_TYPE (type)) == TYPE_CODE_ARRAY)
	f_type_print_varspec_suffix (TYPE_TARGET_TYPE (type), stream, 0, 0, 0);

      retcode = f77_get_dynamic_lowerbound (type, &lower_bound);

      lower_bound_was_default = 0;

      if (retcode == BOUND_FETCH_ERROR)
	fprintf_filtered (stream, "???");
      else if (lower_bound == 1)	/* The default */
	lower_bound_was_default = 1;
      else
	fprintf_filtered (stream, "%d", lower_bound);

      if (lower_bound_was_default)
	lower_bound_was_default = 0;
      else
	fprintf_filtered (stream, ":");

      /* Make sure that, if we have an assumed size array, we
         print out a warning and print the upperbound as '*' */

      if (TYPE_ARRAY_UPPER_BOUND_TYPE (type) == BOUND_CANNOT_BE_DETERMINED)
	fprintf_filtered (stream, "*");
      else
	{
	  retcode = f77_get_dynamic_upperbound (type, &upper_bound);

	  if (retcode == BOUND_FETCH_ERROR)
	    fprintf_filtered (stream, "???");
	  else
	    fprintf_filtered (stream, "%d", upper_bound);
	}

      if (TYPE_CODE (TYPE_TARGET_TYPE (type)) != TYPE_CODE_ARRAY)
	f_type_print_varspec_suffix (TYPE_TARGET_TYPE (type), stream, 0, 0, 0);
      if (arrayprint_recurse_level == 1)
	fprintf_filtered (stream, ")");
      else
	fprintf_filtered (stream, ",");
      arrayprint_recurse_level--;
      break;

    case TYPE_CODE_PTR:
    case TYPE_CODE_REF:
      f_type_print_varspec_suffix (TYPE_TARGET_TYPE (type), stream, 0, 1, 0);
      fprintf_filtered (stream, ")");
      break;

    case TYPE_CODE_FUNC:
      f_type_print_varspec_suffix (TYPE_TARGET_TYPE (type), stream, 0,
				   passed_a_ptr, 0);
      if (passed_a_ptr)
	fprintf_filtered (stream, ")");

      fprintf_filtered (stream, "()");
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
    case TYPE_CODE_METHOD:
    case TYPE_CODE_MEMBER:
    case TYPE_CODE_COMPLEX:
    case TYPE_CODE_TYPEDEF:
      /* These types do not need a suffix.  They are listed so that
         gcc -Wall will report types that may not have been considered.  */
      break;
    }
}