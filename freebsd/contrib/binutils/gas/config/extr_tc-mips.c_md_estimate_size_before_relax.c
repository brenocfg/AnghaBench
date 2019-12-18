#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int fr_var; int /*<<< orphan*/  fr_subtype; int /*<<< orphan*/  fr_symbol; } ;
typedef  TYPE_1__ fragS ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NO_PIC ; 
 scalar_t__ RELAX_BRANCH_P (int /*<<< orphan*/ ) ; 
 int RELAX_FIRST (int /*<<< orphan*/ ) ; 
 scalar_t__ RELAX_MIPS16_EXTENDED (int /*<<< orphan*/ ) ; 
 scalar_t__ RELAX_MIPS16_P (int /*<<< orphan*/ ) ; 
 int RELAX_SECOND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELAX_USE_SECOND ; 
 scalar_t__ SVR4_PIC ; 
 scalar_t__ VXWORKS_PIC ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ mips_pic ; 
 int nopic_need_relax (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pic_need_relax (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int relaxed_branch_length (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
md_estimate_size_before_relax (fragS *fragp, asection *segtype)
{
  int change;

  if (RELAX_BRANCH_P (fragp->fr_subtype))
    {

      fragp->fr_var = relaxed_branch_length (fragp, segtype, FALSE);

      return fragp->fr_var;
    }

  if (RELAX_MIPS16_P (fragp->fr_subtype))
    /* We don't want to modify the EXTENDED bit here; it might get us
       into infinite loops.  We change it only in mips_relax_frag().  */
    return (RELAX_MIPS16_EXTENDED (fragp->fr_subtype) ? 4 : 2);

  if (mips_pic == NO_PIC)
    change = nopic_need_relax (fragp->fr_symbol, 0);
  else if (mips_pic == SVR4_PIC)
    change = pic_need_relax (fragp->fr_symbol, segtype);
  else if (mips_pic == VXWORKS_PIC)
    /* For vxworks, GOT16 relocations never have a corresponding LO16.  */
    change = 0;
  else
    abort ();

  if (change)
    {
      fragp->fr_subtype |= RELAX_USE_SECOND;
      return -RELAX_FIRST (fragp->fr_subtype);
    }
  else
    return -RELAX_SECOND (fragp->fr_subtype);
}