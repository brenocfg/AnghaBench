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
typedef  scalar_t__ tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_2__ {scalar_t__ implicit; } ;

/* Variables and functions */
#define  ARRAY_TYPE 130 
#define  RECORD_TYPE 129 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
#define  UNION_TYPE 128 
 int constructor_designated ; 
 scalar_t__ constructor_fields ; 
 int /*<<< orphan*/  constructor_range_stack ; 
 TYPE_1__* constructor_stack ; 
 scalar_t__ constructor_type ; 
 int /*<<< orphan*/  designator_depth ; 
 scalar_t__ designator_erroneous ; 
 int /*<<< orphan*/  error_init (char*) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  pop_init_level (int) ; 
 int /*<<< orphan*/  process_init_element (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_init_level (int) ; 

__attribute__((used)) static int
set_designator (int array)
{
  tree subtype;
  enum tree_code subcode;

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level.  */
  if (constructor_type == 0)
    return 1;

  /* If there were errors in this designator list already, bail out
     silently.  */
  if (designator_erroneous)
    return 1;

  if (!designator_depth)
    {
      gcc_assert (!constructor_range_stack);

      /* Designator list starts at the level of closest explicit
	 braces.  */
      while (constructor_stack->implicit)
	process_init_element (pop_init_level (1));
      constructor_designated = 1;
      return 0;
    }

  switch (TREE_CODE (constructor_type))
    {
    case  RECORD_TYPE:
    case  UNION_TYPE:
      subtype = TREE_TYPE (constructor_fields);
      if (subtype != error_mark_node)
	subtype = TYPE_MAIN_VARIANT (subtype);
      break;
    case ARRAY_TYPE:
      subtype = TYPE_MAIN_VARIANT (TREE_TYPE (constructor_type));
      break;
    default:
      gcc_unreachable ();
    }

  subcode = TREE_CODE (subtype);
  if (array && subcode != ARRAY_TYPE)
    {
      error_init ("array index in non-array initializer");
      return 1;
    }
  else if (!array && subcode != RECORD_TYPE && subcode != UNION_TYPE)
    {
      error_init ("field name not in record or union initializer");
      return 1;
    }

  constructor_designated = 1;
  push_init_level (2);
  return 0;
}