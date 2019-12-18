#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int offsetT ;
struct TYPE_5__ {int fr_var; int /*<<< orphan*/  fr_subtype; } ;
typedef  TYPE_1__ fragS ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 scalar_t__ RELAX_BRANCH_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELAX_MIPS16_CLEAR_EXTENDED (int /*<<< orphan*/ ) ; 
 scalar_t__ RELAX_MIPS16_EXTENDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELAX_MIPS16_MARK_EXTENDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELAX_MIPS16_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ mips16_extended_frag (TYPE_1__*,int /*<<< orphan*/ *,long) ; 
 int relaxed_branch_length (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
mips_relax_frag (asection *sec, fragS *fragp, long stretch)
{
  if (RELAX_BRANCH_P (fragp->fr_subtype))
    {
      offsetT old_var = fragp->fr_var;

      fragp->fr_var = relaxed_branch_length (fragp, sec, TRUE);

      return fragp->fr_var - old_var;
    }

  if (! RELAX_MIPS16_P (fragp->fr_subtype))
    return 0;

  if (mips16_extended_frag (fragp, NULL, stretch))
    {
      if (RELAX_MIPS16_EXTENDED (fragp->fr_subtype))
	return 0;
      fragp->fr_subtype = RELAX_MIPS16_MARK_EXTENDED (fragp->fr_subtype);
      return 2;
    }
  else
    {
      if (! RELAX_MIPS16_EXTENDED (fragp->fr_subtype))
	return 0;
      fragp->fr_subtype = RELAX_MIPS16_CLEAR_EXTENDED (fragp->fr_subtype);
      return -2;
    }

  return 0;
}