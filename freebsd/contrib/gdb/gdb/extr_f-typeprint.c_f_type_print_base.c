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
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 int /*<<< orphan*/  QUIT ; 
 int /*<<< orphan*/  TYPE_ARRAY_UPPER_BOUND_TYPE (struct type*) ; 
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_ARRAY 141 
#define  TYPE_CODE_CHAR 140 
#define  TYPE_CODE_COMPLEX 139 
#define  TYPE_CODE_ERROR 138 
#define  TYPE_CODE_FLT 137 
#define  TYPE_CODE_FUNC 136 
#define  TYPE_CODE_INT 135 
#define  TYPE_CODE_PTR 134 
#define  TYPE_CODE_RANGE 133 
#define  TYPE_CODE_REF 132 
#define  TYPE_CODE_STRING 131 
#define  TYPE_CODE_TYPEDEF 130 
#define  TYPE_CODE_UNDEF 129 
#define  TYPE_CODE_VOID 128 
 int TYPE_LENGTH (struct type*) ; 
 char* TYPE_NAME (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  error (char*,int) ; 
 int f77_get_dynamic_upperbound (struct type*,int*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 int /*<<< orphan*/  print_equivalent_f77_float_type (struct type*,struct ui_file*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  wrap_here (char*) ; 

void
f_type_print_base (struct type *type, struct ui_file *stream, int show,
		   int level)
{
  int retcode;
  int upper_bound;

  QUIT;

  wrap_here ("    ");
  if (type == NULL)
    {
      fputs_filtered ("<type unknown>", stream);
      return;
    }

  /* When SHOW is zero or less, and there is a valid type name, then always
     just print the type name directly from the type. */

  if ((show <= 0) && (TYPE_NAME (type) != NULL))
    {
      if (TYPE_CODE (type) == TYPE_CODE_FLT)
	print_equivalent_f77_float_type (type, stream);
      else
	fputs_filtered (TYPE_NAME (type), stream);
      return;
    }

  if (TYPE_CODE (type) != TYPE_CODE_TYPEDEF)
    CHECK_TYPEDEF (type);

  switch (TYPE_CODE (type))
    {
    case TYPE_CODE_TYPEDEF:
      f_type_print_base (TYPE_TARGET_TYPE (type), stream, 0, level);
      break;

    case TYPE_CODE_ARRAY:
    case TYPE_CODE_FUNC:
      f_type_print_base (TYPE_TARGET_TYPE (type), stream, show, level);
      break;

    case TYPE_CODE_PTR:
      fprintf_filtered (stream, "PTR TO -> ( ");
      f_type_print_base (TYPE_TARGET_TYPE (type), stream, 0, level);
      break;

    case TYPE_CODE_REF:
      fprintf_filtered (stream, "REF TO -> ( ");
      f_type_print_base (TYPE_TARGET_TYPE (type), stream, 0, level);
      break;

    case TYPE_CODE_VOID:
      fprintf_filtered (stream, "VOID");
      break;

    case TYPE_CODE_UNDEF:
      fprintf_filtered (stream, "struct <unknown>");
      break;

    case TYPE_CODE_ERROR:
      fprintf_filtered (stream, "<unknown type>");
      break;

    case TYPE_CODE_RANGE:
      /* This should not occur */
      fprintf_filtered (stream, "<range type>");
      break;

    case TYPE_CODE_CHAR:
      /* Override name "char" and make it "character" */
      fprintf_filtered (stream, "character");
      break;

    case TYPE_CODE_INT:
      /* There may be some character types that attempt to come
         through as TYPE_CODE_INT since dbxstclass.h is so
         C-oriented, we must change these to "character" from "char".  */

      if (strcmp (TYPE_NAME (type), "char") == 0)
	fprintf_filtered (stream, "character");
      else
	goto default_case;
      break;

    case TYPE_CODE_COMPLEX:
      fprintf_filtered (stream, "complex*%d", TYPE_LENGTH (type));
      break;

    case TYPE_CODE_FLT:
      print_equivalent_f77_float_type (type, stream);
      break;

    case TYPE_CODE_STRING:
      /* Strings may have dynamic upperbounds (lengths) like arrays. */

      if (TYPE_ARRAY_UPPER_BOUND_TYPE (type) == BOUND_CANNOT_BE_DETERMINED)
	fprintf_filtered (stream, "character*(*)");
      else
	{
	  retcode = f77_get_dynamic_upperbound (type, &upper_bound);

	  if (retcode == BOUND_FETCH_ERROR)
	    fprintf_filtered (stream, "character*???");
	  else
	    fprintf_filtered (stream, "character*%d", upper_bound);
	}
      break;

    default_case:
    default:
      /* Handle types not explicitly handled by the other cases,
         such as fundamental types.  For these, just print whatever
         the type name is, as recorded in the type itself.  If there
         is no type name, then complain. */
      if (TYPE_NAME (type) != NULL)
	fputs_filtered (TYPE_NAME (type), stream);
      else
	error ("Invalid type code (%d) in symbol table.", TYPE_CODE (type));
      break;
    }
}