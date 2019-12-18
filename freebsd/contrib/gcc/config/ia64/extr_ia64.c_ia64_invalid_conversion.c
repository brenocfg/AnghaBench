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
 char const* N_ (char*) ; 
 scalar_t__ RFmode ; 
 scalar_t__ TYPE_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ VOIDmode ; 

__attribute__((used)) static const char *
ia64_invalid_conversion (tree fromtype, tree totype)
{
  /* Reject nontrivial conversion to or from __fpreg.  */
  if (TYPE_MODE (fromtype) == RFmode
      && TYPE_MODE (totype) != RFmode
      && TYPE_MODE (totype) != VOIDmode)
    return N_("invalid conversion from %<__fpreg%>");
  if (TYPE_MODE (totype) == RFmode
      && TYPE_MODE (fromtype) != RFmode)
    return N_("invalid conversion to %<__fpreg%>");
  return NULL;
}