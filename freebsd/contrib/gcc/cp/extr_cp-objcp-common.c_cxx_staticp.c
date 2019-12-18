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
#define  BASELINK 128 
 int /*<<< orphan*/  BASELINK_FUNCTIONS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  staticp (int /*<<< orphan*/ ) ; 

tree
cxx_staticp (tree arg)
{
  switch (TREE_CODE (arg))
    {
    case BASELINK:
      return staticp (BASELINK_FUNCTIONS (arg));

    default:
      break;
    }
  
  return NULL_TREE;
}