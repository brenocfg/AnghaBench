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
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ IS_FAKE_BASE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_CONTEXT (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PTRMEMFUNC_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_common_get_alias_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_alias_set (int /*<<< orphan*/ ) ; 

HOST_WIDE_INT
cxx_get_alias_set (tree t)
{
  if (IS_FAKE_BASE_TYPE (t))
    /* The base variant of a type must be in the same alias set as the
       complete type.  */
    return get_alias_set (TYPE_CONTEXT (t));

  /* Punt on PMFs until we canonicalize functions properly.  */
  if (TYPE_PTRMEMFUNC_P (t))
    return 0;

  return c_common_get_alias_set (t);
}