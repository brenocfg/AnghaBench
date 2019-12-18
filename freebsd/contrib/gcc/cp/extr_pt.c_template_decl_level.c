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
 int /*<<< orphan*/  DECL_INITIAL (int /*<<< orphan*/ ) ; 
#define  PARM_DECL 130 
#define  TEMPLATE_DECL 129 
 int TEMPLATE_PARM_LEVEL (int /*<<< orphan*/ ) ; 
 int TEMPLATE_TYPE_LEVEL (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
#define  TYPE_DECL 128 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static int
template_decl_level (tree decl)
{
  switch (TREE_CODE (decl))
    {
    case TYPE_DECL:
    case TEMPLATE_DECL:
      return TEMPLATE_TYPE_LEVEL (TREE_TYPE (decl));

    case PARM_DECL:
      return TEMPLATE_PARM_LEVEL (DECL_INITIAL (decl));

    default:
      gcc_unreachable ();
    }
  return 0;
}