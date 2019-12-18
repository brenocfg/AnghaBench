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
struct tagged_tu_seen_cache {scalar_t__ t1; scalar_t__ t2; int val; struct tagged_tu_seen_cache* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_FIELD_BIT_OFFSET (scalar_t__) ; 
 int /*<<< orphan*/ * DECL_NAME (scalar_t__) ; 
 scalar_t__ DECL_ORIGINAL_TYPE (scalar_t__) ; 
#define  ENUMERAL_TYPE 130 
 int FIELD_DECL ; 
 scalar_t__ NULL_TREE ; 
#define  RECORD_TYPE 129 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_PURPOSE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 int TYPE_DECL ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 scalar_t__ TYPE_NAME (scalar_t__) ; 
 int /*<<< orphan*/ * TYPE_SIZE (scalar_t__) ; 
 scalar_t__ TYPE_VALUES (scalar_t__) ; 
#define  UNION_TYPE 128 
 struct tagged_tu_seen_cache* alloc_tagged_tu_seen_cache (scalar_t__,scalar_t__) ; 
 int comptypes_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ flag_isoc99 ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  list_length (scalar_t__) ; 
 scalar_t__ purpose_member (int /*<<< orphan*/ ,scalar_t__) ; 
 int simple_cst_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tagged_tu_seen_cache* tagged_tu_seen_base ; 

__attribute__((used)) static int
tagged_types_tu_compatible_p (tree t1, tree t2)
{
  tree s1, s2;
  bool needs_warning = false;

  /* We have to verify that the tags of the types are the same.  This
     is harder than it looks because this may be a typedef, so we have
     to go look at the original type.  It may even be a typedef of a
     typedef...
     In the case of compiler-created builtin structs the TYPE_DECL
     may be a dummy, with no DECL_ORIGINAL_TYPE.  Don't fault.  */
  while (TYPE_NAME (t1)
	 && TREE_CODE (TYPE_NAME (t1)) == TYPE_DECL
	 && DECL_ORIGINAL_TYPE (TYPE_NAME (t1)))
    t1 = DECL_ORIGINAL_TYPE (TYPE_NAME (t1));

  while (TYPE_NAME (t2)
	 && TREE_CODE (TYPE_NAME (t2)) == TYPE_DECL
	 && DECL_ORIGINAL_TYPE (TYPE_NAME (t2)))
    t2 = DECL_ORIGINAL_TYPE (TYPE_NAME (t2));

  /* C90 didn't have the requirement that the two tags be the same.  */
  if (flag_isoc99 && TYPE_NAME (t1) != TYPE_NAME (t2))
    return 0;

  /* C90 didn't say what happened if one or both of the types were
     incomplete; we choose to follow C99 rules here, which is that they
     are compatible.  */
  if (TYPE_SIZE (t1) == NULL
      || TYPE_SIZE (t2) == NULL)
    return 1;

  {
    const struct tagged_tu_seen_cache * tts_i;
    for (tts_i = tagged_tu_seen_base; tts_i != NULL; tts_i = tts_i->next)
      if (tts_i->t1 == t1 && tts_i->t2 == t2)
	return tts_i->val;
  }

  switch (TREE_CODE (t1))
    {
    case ENUMERAL_TYPE:
      {
	struct tagged_tu_seen_cache *tu = alloc_tagged_tu_seen_cache (t1, t2);
	/* Speed up the case where the type values are in the same order.  */
	tree tv1 = TYPE_VALUES (t1);
	tree tv2 = TYPE_VALUES (t2);

	if (tv1 == tv2)
	  {
	    return 1;
	  }

	for (;tv1 && tv2; tv1 = TREE_CHAIN (tv1), tv2 = TREE_CHAIN (tv2))
	  {
	    if (TREE_PURPOSE (tv1) != TREE_PURPOSE (tv2))
	      break;
	    if (simple_cst_equal (TREE_VALUE (tv1), TREE_VALUE (tv2)) != 1)
	      {
		tu->val = 0;
		return 0;
	      }
	  }

	if (tv1 == NULL_TREE && tv2 == NULL_TREE)
	  {
	    return 1;
	  }
	if (tv1 == NULL_TREE || tv2 == NULL_TREE)
	  {
	    tu->val = 0;
	    return 0;
	  }

	if (list_length (TYPE_VALUES (t1)) != list_length (TYPE_VALUES (t2)))
	  {
	    tu->val = 0;
	    return 0;
	  }

	for (s1 = TYPE_VALUES (t1); s1; s1 = TREE_CHAIN (s1))
	  {
	    s2 = purpose_member (TREE_PURPOSE (s1), TYPE_VALUES (t2));
	    if (s2 == NULL
		|| simple_cst_equal (TREE_VALUE (s1), TREE_VALUE (s2)) != 1)
	      {
		tu->val = 0;
		return 0;
	      }
	  }
	return 1;
      }

    case UNION_TYPE:
      {
	struct tagged_tu_seen_cache *tu = alloc_tagged_tu_seen_cache (t1, t2);
	if (list_length (TYPE_FIELDS (t1)) != list_length (TYPE_FIELDS (t2)))
	  {
	    tu->val = 0;
	    return 0;
	  }

	/*  Speed up the common case where the fields are in the same order. */
	for (s1 = TYPE_FIELDS (t1), s2 = TYPE_FIELDS (t2); s1 && s2;
	     s1 = TREE_CHAIN (s1), s2 = TREE_CHAIN (s2))
	  {
	    int result;


	    if (DECL_NAME (s1) == NULL
		|| DECL_NAME (s1) != DECL_NAME (s2))
	      break;
	    result = comptypes_internal (TREE_TYPE (s1), TREE_TYPE (s2));
	    if (result == 0)
	      {
		tu->val = 0;
		return 0;
	      }
	    if (result == 2)
	      needs_warning = true;

	    if (TREE_CODE (s1) == FIELD_DECL
		&& simple_cst_equal (DECL_FIELD_BIT_OFFSET (s1),
				     DECL_FIELD_BIT_OFFSET (s2)) != 1)
	      {
		tu->val = 0;
		return 0;
	      }
	  }
	if (!s1 && !s2)
	  {
	    tu->val = needs_warning ? 2 : 1;
	    return tu->val;
	  }

	for (s1 = TYPE_FIELDS (t1); s1; s1 = TREE_CHAIN (s1))
	  {
	    bool ok = false;

	    if (DECL_NAME (s1) != NULL)
	      for (s2 = TYPE_FIELDS (t2); s2; s2 = TREE_CHAIN (s2))
		if (DECL_NAME (s1) == DECL_NAME (s2))
		  {
		    int result;
		    result = comptypes_internal (TREE_TYPE (s1), TREE_TYPE (s2));
		    if (result == 0)
		      {
			tu->val = 0;
			return 0;
		      }
		    if (result == 2)
		      needs_warning = true;

		    if (TREE_CODE (s1) == FIELD_DECL
			&& simple_cst_equal (DECL_FIELD_BIT_OFFSET (s1),
					     DECL_FIELD_BIT_OFFSET (s2)) != 1)
		      break;

		    ok = true;
		    break;
		  }
	    if (!ok)
	      {
		tu->val = 0;
		return 0;
	      }
	  }
	tu->val = needs_warning ? 2 : 10;
	return tu->val;
      }

    case RECORD_TYPE:
      {
	struct tagged_tu_seen_cache *tu = alloc_tagged_tu_seen_cache (t1, t2);

	for (s1 = TYPE_FIELDS (t1), s2 = TYPE_FIELDS (t2);
	     s1 && s2;
	     s1 = TREE_CHAIN (s1), s2 = TREE_CHAIN (s2))
	  {
	    int result;
	    if (TREE_CODE (s1) != TREE_CODE (s2)
		|| DECL_NAME (s1) != DECL_NAME (s2))
	      break;
	    result = comptypes_internal (TREE_TYPE (s1), TREE_TYPE (s2));
	    if (result == 0)
	      break;
	    if (result == 2)
	      needs_warning = true;

	    if (TREE_CODE (s1) == FIELD_DECL
		&& simple_cst_equal (DECL_FIELD_BIT_OFFSET (s1),
				     DECL_FIELD_BIT_OFFSET (s2)) != 1)
	      break;
	  }
	if (s1 && s2)
	  tu->val = 0;
	else
	  tu->val = needs_warning ? 2 : 1;
	return tu->val;
      }

    default:
      gcc_unreachable ();
    }
}