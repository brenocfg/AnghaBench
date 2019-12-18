#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* subvar_t ;
struct TYPE_3__ {int /*<<< orphan*/  var; struct TYPE_3__* next; } ;

/* Variables and functions */
#define  ARRAY_REF 130 
#define  COMPONENT_REF 129 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  VAR_DECL 128 
 TYPE_1__* get_subvars_for_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_call_clobbered (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
dest_safe_for_nrv_p (tree dest)
{
  switch (TREE_CODE (dest))
    {
      case VAR_DECL:
	{
	  subvar_t subvar;
	  if (is_call_clobbered (dest))
	    return false;
	  for (subvar = get_subvars_for_var (dest);
	       subvar;
	       subvar = subvar->next)
	    if (is_call_clobbered (subvar->var))
	      return false;
	  return true;
	}
      case ARRAY_REF:
      case COMPONENT_REF:
	return dest_safe_for_nrv_p (TREE_OPERAND (dest, 0));
      default:
	return false;
    }
}