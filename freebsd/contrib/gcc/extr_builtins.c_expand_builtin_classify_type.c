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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  no_type_class ; 
 int /*<<< orphan*/  type_to_class (int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
expand_builtin_classify_type (tree arglist)
{
  if (arglist != 0)
    return GEN_INT (type_to_class (TREE_TYPE (TREE_VALUE (arglist))));
  return GEN_INT (no_type_class);
}