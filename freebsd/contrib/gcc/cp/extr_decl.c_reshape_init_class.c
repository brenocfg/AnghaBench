#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_6__ {TYPE_1__* cur; TYPE_1__* end; } ;
typedef  TYPE_2__ reshape_iter ;
struct TYPE_5__ {char* index; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  CONSTRUCTOR_APPEND_ELT (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  CONSTRUCTOR_ELTS (scalar_t__) ; 
 scalar_t__ FIELD_DECL ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_FIELDS (scalar_t__) ; 
 scalar_t__ UNION_TYPE ; 
 scalar_t__ build_constructor (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*,scalar_t__,...) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ lookup_field_1 (scalar_t__,char*,int) ; 
 scalar_t__ next_initializable_field (int /*<<< orphan*/ ) ; 
 scalar_t__ reshape_init_r (int /*<<< orphan*/ ,TYPE_2__*,int) ; 

__attribute__((used)) static tree
reshape_init_class (tree type, reshape_iter *d, bool first_initializer_p)
{
  tree field;
  tree new_init;

  gcc_assert (CLASS_TYPE_P (type));

  /* The initializer for a class is always a CONSTRUCTOR.  */
  new_init = build_constructor (NULL_TREE, NULL);
  field = next_initializable_field (TYPE_FIELDS (type));

  if (!field)
    {
      /* [dcl.init.aggr]

	An initializer for an aggregate member that is an
	empty class shall have the form of an empty
	initializer-list {}.  */
      if (!first_initializer_p)
	{
	  error ("initializer for %qT must be brace-enclosed", type);
	  return error_mark_node;
	}
      return new_init;
    }

  /* Loop through the initializable fields, gathering initializers.  */
  while (d->cur != d->end)
    {
      tree field_init;

      /* Handle designated initializers, as an extension.  */
      if (d->cur->index)
	{
	  field = lookup_field_1 (type, d->cur->index, /*want_type=*/false);

	  if (!field || TREE_CODE (field) != FIELD_DECL)
	    {
	      error ("%qT has no non-static data member named %qD", type,
		    d->cur->index);
	      return error_mark_node;
	    }
	}

      /* If we processed all the member of the class, we are done.  */
      if (!field)
	break;

      field_init = reshape_init_r (TREE_TYPE (field), d,
				   /*first_initializer_p=*/false);
      CONSTRUCTOR_APPEND_ELT (CONSTRUCTOR_ELTS (new_init), field, field_init);

      /* [dcl.init.aggr]

	When a union  is  initialized with a brace-enclosed
	initializer, the braces shall only contain an
	initializer for the first member of the union.  */
      if (TREE_CODE (type) == UNION_TYPE)
	break;

      field = next_initializable_field (TREE_CHAIN (field));
    }

  return new_init;
}