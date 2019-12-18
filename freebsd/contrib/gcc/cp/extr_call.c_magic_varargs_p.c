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
#define  BUILT_IN_CLASSIFY_TYPE 132 
#define  BUILT_IN_CONSTANT_P 131 
#define  BUILT_IN_NEXT_ARG 130 
#define  BUILT_IN_STDARG_START 129 
#define  BUILT_IN_VA_START 128 
 scalar_t__ DECL_BUILT_IN (int /*<<< orphan*/ ) ; 
 int DECL_FUNCTION_CODE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
magic_varargs_p (tree fn)
{
  if (DECL_BUILT_IN (fn))
    switch (DECL_FUNCTION_CODE (fn))
      {
      case BUILT_IN_CLASSIFY_TYPE:
      case BUILT_IN_CONSTANT_P:
      case BUILT_IN_NEXT_ARG:
      case BUILT_IN_STDARG_START:
      case BUILT_IN_VA_START:
	return true;

      default:;
      }

  return false;
}