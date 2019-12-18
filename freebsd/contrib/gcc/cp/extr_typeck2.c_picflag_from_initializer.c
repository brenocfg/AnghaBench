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

/* Variables and functions */
 int PICFLAG_ERRONEOUS ; 
 int PICFLAG_NOT_ALL_CONSTANT ; 
 int PICFLAG_NOT_ALL_SIMPLE ; 
 int /*<<< orphan*/  TREE_CONSTANT (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  initializer_constant_valid_p (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
picflag_from_initializer (tree init)
{
  if (init == error_mark_node)
    return PICFLAG_ERRONEOUS;
  else if (!TREE_CONSTANT (init))
    return PICFLAG_NOT_ALL_CONSTANT;
  else if (!initializer_constant_valid_p (init, TREE_TYPE (init)))
    return PICFLAG_NOT_ALL_SIMPLE;
  return 0;
}