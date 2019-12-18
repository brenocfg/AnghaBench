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

/* Variables and functions */
 int /*<<< orphan*/  MANGLE_TRACE_TREE (char*,int /*<<< orphan*/  const) ; 
 scalar_t__ METHOD_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ARG_TYPES (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  write_CV_qualifiers_for_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_bare_function_type (int /*<<< orphan*/  const,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_char (char) ; 

__attribute__((used)) static void
write_function_type (const tree type)
{
  MANGLE_TRACE_TREE ("function-type", type);

  /* For a pointer to member function, the function type may have
     cv-qualifiers, indicating the quals for the artificial 'this'
     parameter.  */
  if (TREE_CODE (type) == METHOD_TYPE)
    {
      /* The first parameter must be a POINTER_TYPE pointing to the
	 `this' parameter.  */
      tree this_type = TREE_TYPE (TREE_VALUE (TYPE_ARG_TYPES (type)));
      write_CV_qualifiers_for_type (this_type);
    }

  write_char ('F');
  /* We don't track whether or not a type is `extern "C"'.  Note that
     you can have an `extern "C"' function that does not have
     `extern "C"' type, and vice versa:

       extern "C" typedef void function_t();
       function_t f; // f has C++ linkage, but its type is
		     // `extern "C"'

       typedef void function_t();
       extern "C" function_t f; // Vice versa.

     See [dcl.link].  */
  write_bare_function_type (type, /*include_return_type_p=*/1,
			    /*decl=*/NULL);
  write_char ('E');
}