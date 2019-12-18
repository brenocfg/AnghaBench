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
typedef  int /*<<< orphan*/  tree ;
typedef  int DECL_UNINLINABLE ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_ATTRIBUTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_DECLARED_INLINE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_INLINE (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_REPLACEABLE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_TEMPLATE_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_TEMPLATE_RESULT (int /*<<< orphan*/ ) ; 
 scalar_t__ TI_PENDING_TEMPLATE_FLAG (scalar_t__) ; 
 scalar_t__ flag_really_no_inline ; 
 int /*<<< orphan*/  function_attribute_inlinable_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  instantiate_decl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lookup_attribute (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  template_for_substitution (int /*<<< orphan*/ ) ; 
 scalar_t__ varargs_function_p (int /*<<< orphan*/ ) ; 

int
cp_cannot_inline_tree_fn (tree* fnp)
{
  tree fn = *fnp;

  /* We can inline a template instantiation only if it's fully
     instantiated.  */
  if (DECL_TEMPLATE_INFO (fn)
      && TI_PENDING_TEMPLATE_FLAG (DECL_TEMPLATE_INFO (fn)))
    {
      /* Don't instantiate functions that are not going to be
	 inlined.  */
      if (!DECL_INLINE (DECL_TEMPLATE_RESULT
			(template_for_substitution (fn))))
	return 1;

      fn = *fnp = instantiate_decl (fn, /*defer_ok=*/0, /*undefined_ok=*/0);

      if (TI_PENDING_TEMPLATE_FLAG (DECL_TEMPLATE_INFO (fn)))
	return 1;
    }

  if (flag_really_no_inline
      && lookup_attribute ("always_inline", DECL_ATTRIBUTES (fn)) == NULL)
    return 1;

  /* Don't auto-inline functions that might be replaced at link-time
     with an alternative definition.  */ 
  if (!DECL_DECLARED_INLINE_P (fn) && DECL_REPLACEABLE_P (fn))
    {
      DECL_UNINLINABLE (fn) = 1;
      return 1;
    }

  if (varargs_function_p (fn))
    {
      DECL_UNINLINABLE (fn) = 1;
      return 1;
    }

  if (! function_attribute_inlinable_p (fn))
    {
      DECL_UNINLINABLE (fn) = 1;
      return 1;
    }

  return 0;
}