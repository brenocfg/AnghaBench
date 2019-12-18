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
 int /*<<< orphan*/  check_function_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_function_nonnull (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_function_sentinel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ warn_format ; 
 scalar_t__ warn_missing_format_attribute ; 
 scalar_t__ warn_nonnull ; 

void
check_function_arguments (tree attrs, tree params, tree typelist)
{
  /* Check for null being passed in a pointer argument that must be
     non-null.  We also need to do this if format checking is enabled.  */

  if (warn_nonnull)
    check_function_nonnull (attrs, params);

  /* Check for errors in format strings.  */

  if (warn_format || warn_missing_format_attribute)
      check_function_format (attrs, params);

  if (warn_format)
    check_function_sentinel (attrs, params, typelist);
}