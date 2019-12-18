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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  location_t ;

/* Variables and functions */
 scalar_t__ ANON_AGGR_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_NAME (scalar_t__) ; 
 int /*<<< orphan*/  DECL_SOURCE_LOCATION (scalar_t__) ; 
 scalar_t__ OVERLOAD ; 
 int /*<<< orphan*/  POP_TIMEVAR_AND_RETURN (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TV_NAME_LOOKUP ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ TYPE_FIELDS (int /*<<< orphan*/ ) ; 
 scalar_t__ get_first_fn (scalar_t__) ; 
 int /*<<< orphan*/  input_location ; 
 int push_class_level_binding (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  set_identifier_type_value (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

bool
pushdecl_class_level (tree x)
{
  tree name;
  bool is_valid = true;

  timevar_push (TV_NAME_LOOKUP);
  /* Get the name of X.  */
  if (TREE_CODE (x) == OVERLOAD)
    name = DECL_NAME (get_first_fn (x));
  else
    name = DECL_NAME (x);

  if (name)
    {
      is_valid = push_class_level_binding (name, x);
      if (TREE_CODE (x) == TYPE_DECL)
	set_identifier_type_value (name, x);
    }
  else if (ANON_AGGR_TYPE_P (TREE_TYPE (x)))
    {
      /* If X is an anonymous aggregate, all of its members are
	 treated as if they were members of the class containing the
	 aggregate, for naming purposes.  */
      tree f;

      for (f = TYPE_FIELDS (TREE_TYPE (x)); f; f = TREE_CHAIN (f))
	{
	  location_t save_location = input_location;
	  input_location = DECL_SOURCE_LOCATION (f);
	  if (!pushdecl_class_level (f))
	    is_valid = false;
	  input_location = save_location;
	}
    }
  POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, is_valid);
}