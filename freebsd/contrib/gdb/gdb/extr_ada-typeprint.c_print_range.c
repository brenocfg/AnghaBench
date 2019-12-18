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
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_BOOL 132 
#define  TYPE_CODE_CHAR 131 
#define  TYPE_CODE_ENUM 130 
#define  TYPE_CODE_INT 129 
#define  TYPE_CODE_RANGE 128 
 int /*<<< orphan*/  TYPE_FIELD_BITPOS (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_LOW_BOUND (struct type*) ; 
 int /*<<< orphan*/  TYPE_NAME (struct type*) ; 
 int TYPE_NFIELDS (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  ada_name_prefix_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ada_print_scalar (struct type*,int /*<<< orphan*/  const,struct ui_file*) ; 
 struct type* builtin_type_ada_int ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 

__attribute__((used)) static void
print_range (struct type *type, struct ui_file *stream)
{
  struct type *target_type;
  target_type = TYPE_TARGET_TYPE (type);
  if (target_type == NULL)
    target_type = type;

  switch (TYPE_CODE (target_type))
    {
    case TYPE_CODE_RANGE:
    case TYPE_CODE_INT:
    case TYPE_CODE_BOOL:
    case TYPE_CODE_CHAR:
    case TYPE_CODE_ENUM:
      break;
    default:
      target_type = builtin_type_ada_int;
      break;
    }

  if (TYPE_NFIELDS (type) < 2)
    {
      /* A range needs at least 2 bounds to be printed. If there are less
         than 2, just print the type name instead of the range itself.
         This check handles cases such as characters, for example. 

         Note that if the name is not defined, then we don't print anything.
       */
      fprintf_filtered (stream, "%.*s",
			ada_name_prefix_len (TYPE_NAME (type)),
			TYPE_NAME (type));
    }
  else
    {
      /* We extract the range type bounds respectively from the first element
         and the last element of the type->fields array */
      const LONGEST lower_bound = (LONGEST) TYPE_LOW_BOUND (type);
      const LONGEST upper_bound =
	(LONGEST) TYPE_FIELD_BITPOS (type, TYPE_NFIELDS (type) - 1);

      ada_print_scalar (target_type, lower_bound, stream);
      fprintf_filtered (stream, " .. ");
      ada_print_scalar (target_type, upper_bound, stream);
    }
}