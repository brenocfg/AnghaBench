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
typedef  enum built_in_class { ____Placeholder_built_in_class } built_in_class ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  builtin_function_1 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pop_namespace () ; 
 int /*<<< orphan*/  push_namespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  std_identifier ; 
 int /*<<< orphan*/  std_node ; 

tree
builtin_function (const char* name,
		  tree type,
		  int code,
		  enum built_in_class cl,
		  const char* libname,
		  tree attrs)
{
  /* All builtins that don't begin with an '_' should additionally
     go in the 'std' namespace.  */
  if (name[0] != '_')
    {
      push_namespace (std_identifier);
      builtin_function_1 (name, type, std_node, code, cl, libname, attrs);
      pop_namespace ();
    }

  return builtin_function_1 (name, type, NULL_TREE, code,
			     cl, libname, attrs);
}