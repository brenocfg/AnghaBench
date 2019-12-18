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
typedef  scalar_t__ LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 int /*<<< orphan*/  LA_PRINT_CHAR (unsigned char,struct ui_file*) ; 
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_ARRAY 146 
#define  TYPE_CODE_BOOL 145 
#define  TYPE_CODE_CHAR 144 
#define  TYPE_CODE_ENUM 143 
#define  TYPE_CODE_ERROR 142 
#define  TYPE_CODE_FLT 141 
#define  TYPE_CODE_FUNC 140 
#define  TYPE_CODE_INT 139 
#define  TYPE_CODE_MEMBER 138 
#define  TYPE_CODE_METHOD 137 
#define  TYPE_CODE_PTR 136 
#define  TYPE_CODE_RANGE 135 
#define  TYPE_CODE_REF 134 
#define  TYPE_CODE_SET 133 
#define  TYPE_CODE_STRING 132 
#define  TYPE_CODE_STRUCT 131 
#define  TYPE_CODE_UNDEF 130 
#define  TYPE_CODE_UNION 129 
#define  TYPE_CODE_VOID 128 
 scalar_t__ TYPE_FIELD_BITPOS (struct type*,unsigned int) ; 
 int /*<<< orphan*/  TYPE_FIELD_NAME (struct type*,unsigned int) ; 
 unsigned int TYPE_NFIELDS (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (struct type*) ; 
 int /*<<< orphan*/  ada_enum_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*) ; 
 int /*<<< orphan*/  fputs_filtered (int /*<<< orphan*/ ,struct ui_file*) ; 
 int /*<<< orphan*/  gdb_flush (struct ui_file*) ; 
 int /*<<< orphan*/  print_longest (struct ui_file*,unsigned char,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  warning (char*) ; 

void
ada_print_scalar (struct type *type, LONGEST val, struct ui_file *stream)
{
  unsigned int i;
  unsigned len;

  CHECK_TYPEDEF (type);

  switch (TYPE_CODE (type))
    {

    case TYPE_CODE_ENUM:
      len = TYPE_NFIELDS (type);
      for (i = 0; i < len; i++)
	{
	  if (TYPE_FIELD_BITPOS (type, i) == val)
	    {
	      break;
	    }
	}
      if (i < len)
	{
	  fputs_filtered (ada_enum_name (TYPE_FIELD_NAME (type, i)), stream);
	}
      else
	{
	  print_longest (stream, 'd', 0, val);
	}
      break;

    case TYPE_CODE_INT:
      print_longest (stream, TYPE_UNSIGNED (type) ? 'u' : 'd', 0, val);
      break;

    case TYPE_CODE_CHAR:
      LA_PRINT_CHAR ((unsigned char) val, stream);
      break;

    case TYPE_CODE_BOOL:
      fprintf_filtered (stream, val ? "true" : "false");
      break;

    case TYPE_CODE_RANGE:
      ada_print_scalar (TYPE_TARGET_TYPE (type), val, stream);
      return;

    case TYPE_CODE_UNDEF:
    case TYPE_CODE_PTR:
    case TYPE_CODE_ARRAY:
    case TYPE_CODE_STRUCT:
    case TYPE_CODE_UNION:
    case TYPE_CODE_FUNC:
    case TYPE_CODE_FLT:
    case TYPE_CODE_VOID:
    case TYPE_CODE_SET:
    case TYPE_CODE_STRING:
    case TYPE_CODE_ERROR:
    case TYPE_CODE_MEMBER:
    case TYPE_CODE_METHOD:
    case TYPE_CODE_REF:
      warning ("internal error: unhandled type in ada_print_scalar");
      break;

    default:
      error ("Invalid type code in symbol table.");
    }
  gdb_flush (stream);
}