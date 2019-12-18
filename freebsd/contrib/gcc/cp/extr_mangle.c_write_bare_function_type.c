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
typedef  int /*<<< orphan*/ * tree ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_CONSTRUCTOR_P (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  DECL_CONTEXT (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  DECL_CONV_FN_P (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  DECL_DESTRUCTOR_P (int /*<<< orphan*/ * const) ; 
 scalar_t__ DECL_FUNCTION_MEMBER_P (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  MANGLE_TRACE_TREE (char*,int /*<<< orphan*/ * const) ; 
 scalar_t__ METHOD_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  TYPE_ARG_TYPES (int /*<<< orphan*/ * const) ; 
 scalar_t__ TYPE_FOR_JAVA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_char (char) ; 
 int /*<<< orphan*/  write_method_parms (int /*<<< orphan*/ ,int,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  write_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
write_bare_function_type (const tree type, const int include_return_type_p,
			  const tree decl)
{
  int java_method_p;

  MANGLE_TRACE_TREE ("bare-function-type", type);

  /* Detect Java methods and emit special encoding.  */
  if (decl != NULL
      && DECL_FUNCTION_MEMBER_P (decl)
      && TYPE_FOR_JAVA (DECL_CONTEXT (decl))
      && !DECL_CONSTRUCTOR_P (decl)
      && !DECL_DESTRUCTOR_P (decl)
      && !DECL_CONV_FN_P (decl))
    {
      java_method_p = 1;
      write_char ('J');
    }
  else
    {
      java_method_p = 0;
    }

  /* Mangle the return type, if requested.  */
  if (include_return_type_p || java_method_p)
    write_type (TREE_TYPE (type));

  /* Now mangle the types of the arguments.  */
  write_method_parms (TYPE_ARG_TYPES (type),
		      TREE_CODE (type) == METHOD_TYPE,
		      decl);
}