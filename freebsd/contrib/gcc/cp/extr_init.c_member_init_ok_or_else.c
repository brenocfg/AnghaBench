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

/* Variables and functions */
 scalar_t__ FIELD_DECL ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  error (char*,scalar_t__,...) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ initializing_context (scalar_t__) ; 

__attribute__((used)) static int
member_init_ok_or_else (tree field, tree type, tree member_name)
{
  if (field == error_mark_node)
    return 0;
  if (!field)
    {
      error ("class %qT does not have any field named %qD", type,
	     member_name);
      return 0;
    }
  if (TREE_CODE (field) == VAR_DECL)
    {
      error ("%q#D is a static data member; it can only be "
	     "initialized at its definition",
	     field);
      return 0;
    }
  if (TREE_CODE (field) != FIELD_DECL)
    {
      error ("%q#D is not a non-static data member of %qT",
	     field, type);
      return 0;
    }
  if (initializing_context (field) != type)
    {
      error ("class %qT does not have any field named %qD", type,
		member_name);
      return 0;
    }

  return 1;
}