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
 scalar_t__ DECL_EXTERNAL (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_EXTERN_C_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_NAMESPACE_SCOPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDENTIFIER_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_PUBLIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libc_name_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
nothrow_libfn_p (tree fn)
{
  tree id;

  if (TREE_PUBLIC (fn)
      && DECL_EXTERNAL (fn)
      && DECL_NAMESPACE_SCOPE_P (fn)
      && DECL_EXTERN_C_P (fn))
    /* OK */;
  else
    /* Can't be a C library function.  */
    return 0;

  /* Being a C library function, DECL_ASSEMBLER_NAME == DECL_NAME
     unless the system headers are playing rename tricks, and if
     they are, we don't want to be confused by them.  */
  id = DECL_NAME (fn);
  return !!libc_name_p (IDENTIFIER_POINTER (id), IDENTIFIER_LENGTH (id));
}