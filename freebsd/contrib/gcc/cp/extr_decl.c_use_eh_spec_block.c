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
 int /*<<< orphan*/  DECL_ARTIFICIAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_CLONED_FUNCTION_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_RAISES_EXCEPTIONS (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_enforce_eh_specs ; 
 scalar_t__ flag_exceptions ; 
 int /*<<< orphan*/  processing_template_decl ; 

__attribute__((used)) static bool
use_eh_spec_block (tree fn)
{
  return (flag_exceptions && flag_enforce_eh_specs
	  && !processing_template_decl
	  && TYPE_RAISES_EXCEPTIONS (TREE_TYPE (fn))
	  /* We insert the EH_SPEC_BLOCK only in the original
	     function; then, it is copied automatically to the
	     clones.  */
	  && !DECL_CLONED_FUNCTION_P (fn)
	  /* Implicitly-generated constructors and destructors have
	     exception specifications.  However, those specifications
	     are the union of the possible exceptions specified by the
	     constructors/destructors for bases and members, so no
	     unallowed exception will ever reach this function.  By
	     not creating the EH_SPEC_BLOCK we save a little memory,
	     and we avoid spurious warnings about unreachable
	     code.  */
	  && !DECL_ARTIFICIAL (fn));
}