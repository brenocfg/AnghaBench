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

/* Variables and functions */
 int /*<<< orphan*/  alpha_fill_fp_regs (int,char*,char*) ; 

void
alphabsd_fill_fpreg (char *fpregs, int regno)
{
  /* FPCR is at slot 33; slot 32 unused.  */
  alpha_fill_fp_regs (regno, fpregs, fpregs + 32*8);
}