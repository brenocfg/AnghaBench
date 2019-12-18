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
 int /*<<< orphan*/  QUIT ; 
 int TYPE_CODE (struct type*) ; 
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
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*) ; 

void
f_type_print_varspec_prefix (struct type *type, struct ui_file *stream,
			     int show, int passed_a_ptr)
{
  if (type == 0)
    return;

  if (TYPE_NAME (type) && show <= 0)
    return;

  QUIT;

  switch (TYPE_CODE (type))
    {
    case TYPE_CODE_PTR:
      f_type_print_varspec_prefix (TYPE_TARGET_TYPE (type), stream, 0, 1);
      break;

    case TYPE_CODE_FUNC:
      f_type_print_varspec_prefix (TYPE_TARGET_TYPE (type), stream, 0, 0);
      if (passed_a_ptr)
	fprintf_filtered (stream, "(");
      break;

    case TYPE_CODE_ARRAY:
      f_type_print_varspec_prefix (TYPE_TARGET_TYPE (type), stream, 0, 0);
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
    case TYPE_CODE_REF:
    case TYPE_CODE_COMPLEX:
    case TYPE_CODE_TYPEDEF:
      /* These types need no prefix.  They are listed here so that
         gcc -Wall will reveal any types that haven't been handled.  */
      break;
    }
}