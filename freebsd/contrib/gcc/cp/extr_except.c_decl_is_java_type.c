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
 int /*<<< orphan*/  DERIVED_FROM_P (scalar_t__,scalar_t__) ; 
 scalar_t__ IDENTIFIER_GLOBAL_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ REFERENCE_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_FOR_JAVA (scalar_t__) ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 int /*<<< orphan*/  fatal_error (char*) ; 
 int /*<<< orphan*/  get_identifier (char*) ; 

__attribute__((used)) static bool
decl_is_java_type (tree decl, int err)
{
  bool r = (TREE_CODE (decl) == POINTER_TYPE
	    && TREE_CODE (TREE_TYPE (decl)) == RECORD_TYPE
	    && TYPE_FOR_JAVA (TREE_TYPE (decl)));

  if (err)
    {
      if (TREE_CODE (decl) == REFERENCE_TYPE
	  && TREE_CODE (TREE_TYPE (decl)) == RECORD_TYPE
	  && TYPE_FOR_JAVA (TREE_TYPE (decl)))
	{
	  /* Can't throw a reference.  */
	  error ("type %qT is disallowed in Java %<throw%> or %<catch%>",
		 decl);
	}

      if (r)
	{
	  tree jthrow_node
	    = IDENTIFIER_GLOBAL_VALUE (get_identifier ("jthrowable"));

	  if (jthrow_node == NULL_TREE)
	    fatal_error
	      ("call to Java %<catch%> or %<throw%> with %<jthrowable%> undefined");

	  jthrow_node = TREE_TYPE (TREE_TYPE (jthrow_node));

	  if (! DERIVED_FROM_P (jthrow_node, TREE_TYPE (decl)))
	    {
	      /* Thrown object must be a Throwable.  */
	      error ("type %qT is not derived from %<java::lang::Throwable%>",
		     TREE_TYPE (decl));
	    }
	}
    }

  return r;
}