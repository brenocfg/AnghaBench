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
typedef  int /*<<< orphan*/  template_parm_index ;
struct tree_overload {int dummy; } ;
struct tree_default_arg {int dummy; } ;
struct tree_baselink {int dummy; } ;
struct tinst_level_s {int dummy; } ;
struct ptrmem_cst {int dummy; } ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
#define  BASELINK 133 
#define  DEFAULT_ARG 132 
#define  OVERLOAD 131 
#define  PTRMEM_CST 130 
#define  TEMPLATE_PARM_INDEX 129 
#define  TINST_LEVEL 128 
 int /*<<< orphan*/  gcc_unreachable () ; 

size_t
cp_tree_size (enum tree_code code)
{
  switch (code)
    {
    case TINST_LEVEL:		return sizeof (struct tinst_level_s);
    case PTRMEM_CST:		return sizeof (struct ptrmem_cst);
    case BASELINK:		return sizeof (struct tree_baselink);
    case TEMPLATE_PARM_INDEX:	return sizeof (template_parm_index);
    case DEFAULT_ARG:		return sizeof (struct tree_default_arg);
    case OVERLOAD:		return sizeof (struct tree_overload);
    default:
      gcc_unreachable ();
    }
  /* NOTREACHED */
}