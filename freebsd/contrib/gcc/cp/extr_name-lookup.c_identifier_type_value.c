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
 int /*<<< orphan*/  LOOKUP_COMPLAIN ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  POP_TIMEVAR_AND_RETURN (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ REAL_IDENTIFIER_TYPE_VALUE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TV_NAME_LOOKUP ; 
 scalar_t__ global_type_node ; 
 scalar_t__ lookup_name_real (scalar_t__,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

tree
identifier_type_value (tree id)
{
  timevar_push (TV_NAME_LOOKUP);
  /* There is no type with that name, anywhere.  */
  if (REAL_IDENTIFIER_TYPE_VALUE (id) == NULL_TREE)
    POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, NULL_TREE);
  /* This is not the type marker, but the real thing.  */
  if (REAL_IDENTIFIER_TYPE_VALUE (id) != global_type_node)
    POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, REAL_IDENTIFIER_TYPE_VALUE (id));
  /* Have to search for it. It must be on the global level, now.
     Ask lookup_name not to return non-types.  */
  id = lookup_name_real (id, 2, 1, /*block_p=*/true, 0, LOOKUP_COMPLAIN);
  if (id)
    POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, TREE_TYPE (id));
  POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, NULL_TREE);
}