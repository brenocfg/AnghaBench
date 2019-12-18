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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ get_attr_may_clobber_hilo (int /*<<< orphan*/ ) ; 
 scalar_t__ mips_linked_madd_p (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mips_macc_chains_last_hilo ; 
 int /*<<< orphan*/  mips_promote_ready (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ recog_memoized (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mips_macc_chains_reorder (rtx *ready, int nready)
{
  int i, j;

  if (mips_macc_chains_last_hilo != 0)
    for (i = nready - 1; i >= 0; i--)
      if (mips_linked_madd_p (mips_macc_chains_last_hilo, ready[i]))
	{
	  for (j = nready - 1; j > i; j--)
	    if (recog_memoized (ready[j]) >= 0
		&& get_attr_may_clobber_hilo (ready[j]))
	      {
		mips_promote_ready (ready, i, j);
		break;
	      }
	  break;
	}
}