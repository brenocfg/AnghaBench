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
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_DECL ; 
 int /*<<< orphan*/  TYPE_PTRFN_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEMFUNC_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_REFFN_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
bad_specifiers (tree object,
		const char* type,
		int virtualp,
		int quals,
		int inlinep,
		int friendp,
		int raises)
{
  if (virtualp)
    error ("%qD declared as a %<virtual%> %s", object, type);
  if (inlinep)
    error ("%qD declared as an %<inline%> %s", object, type);
  if (quals)
    error ("%<const%> and %<volatile%> function specifiers on "
	   "%qD invalid in %s declaration",
	   object, type);
  if (friendp)
    error ("%q+D declared as a friend", object);
  if (raises
      && (TREE_CODE (object) == TYPE_DECL
	  || (!TYPE_PTRFN_P (TREE_TYPE (object))
	      && !TYPE_REFFN_P (TREE_TYPE (object))
	      && !TYPE_PTRMEMFUNC_P (TREE_TYPE (object)))))
    error ("%q+D declared with an exception specification", object);
}