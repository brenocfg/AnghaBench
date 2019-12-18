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
 int /*<<< orphan*/  mips_promote_ready (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ vr4130_swap_insns_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vr4130_reorder (rtx *ready, int nready)
{
  if (vr4130_swap_insns_p (ready[nready - 1], ready[nready - 2]))
    mips_promote_ready (ready, nready - 2, nready - 1);
}