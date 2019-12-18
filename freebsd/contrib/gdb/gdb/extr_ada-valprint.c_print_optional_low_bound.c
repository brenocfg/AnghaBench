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
#define  TYPE_CODE_ENUM 129 
 int TYPE_CODE_RANGE ; 
#define  TYPE_CODE_UNDEF 128 
 long TYPE_FIELD_BITPOS (struct type*,int /*<<< orphan*/ ) ; 
 struct type* TYPE_INDEX_TYPE (struct type*) ; 
 long TYPE_LOW_BOUND (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  ada_print_scalar (struct type*,int /*<<< orphan*/ ,struct ui_file*) ; 
 struct type* builtin_type_long ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*) ; 

__attribute__((used)) static int
print_optional_low_bound (struct ui_file *stream, struct type *type)
{
  struct type *index_type;
  long low_bound;

  index_type = TYPE_INDEX_TYPE (type);
  low_bound = 0;

  if (index_type == NULL)
    return 0;
  if (TYPE_CODE (index_type) == TYPE_CODE_RANGE)
    {
      low_bound = TYPE_LOW_BOUND (index_type);
      index_type = TYPE_TARGET_TYPE (index_type);
    }
  else
    return 0;

  switch (TYPE_CODE (index_type))
    {
    case TYPE_CODE_ENUM:
      if (low_bound == TYPE_FIELD_BITPOS (index_type, 0))
	return 0;
      break;
    case TYPE_CODE_UNDEF:
      index_type = builtin_type_long;
      /* FALL THROUGH */
    default:
      if (low_bound == 1)
	return 0;
      break;
    }

  ada_print_scalar (index_type, (LONGEST) low_bound, stream);
  fprintf_filtered (stream, " => ");
  return 1;
}