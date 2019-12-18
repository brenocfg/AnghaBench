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
 scalar_t__ ARRAY_TYPE ; 
 scalar_t__ BINFO_BASE_ITERATE (scalar_t__,int,scalar_t__) ; 
 scalar_t__ BINFO_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  CLASS_TYPE_P (scalar_t__) ; 
 scalar_t__ DECL_ARTIFICIAL (scalar_t__) ; 
 scalar_t__ FIELD_DECL ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_BINFO (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 scalar_t__ TYPE_RAISES_EXCEPTIONS (scalar_t__) ; 
 scalar_t__ empty_except_spec ; 
 scalar_t__ merge_exception_specifiers (scalar_t__,scalar_t__) ; 
 scalar_t__ stub1 (scalar_t__,void*) ; 
 scalar_t__ stub2 (scalar_t__,void*) ; 

__attribute__((used)) static tree
synthesize_exception_spec (tree type, tree (*extractor) (tree, void*),
			   void *client)
{
  tree raises = empty_except_spec;
  tree fields = TYPE_FIELDS (type);
  tree binfo, base_binfo;
  int i;

  for (binfo = TYPE_BINFO (type), i = 0;
       BINFO_BASE_ITERATE (binfo, i, base_binfo); i++)
    {
      tree fn = (*extractor) (BINFO_TYPE (base_binfo), client);
      if (fn)
	{
	  tree fn_raises = TYPE_RAISES_EXCEPTIONS (TREE_TYPE (fn));

	  raises = merge_exception_specifiers (raises, fn_raises);
	}
    }
  for (; fields; fields = TREE_CHAIN (fields))
    {
      tree type = TREE_TYPE (fields);
      tree fn;

      if (TREE_CODE (fields) != FIELD_DECL || DECL_ARTIFICIAL (fields))
	continue;
      while (TREE_CODE (type) == ARRAY_TYPE)
	type = TREE_TYPE (type);
      if (!CLASS_TYPE_P (type))
	continue;

      fn = (*extractor) (type, client);
      if (fn)
	{
	  tree fn_raises = TYPE_RAISES_EXCEPTIONS (TREE_TYPE (fn));

	  raises = merge_exception_specifiers (raises, fn_raises);
	}
    }
  return raises;
}