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
 scalar_t__ MPSC_0_CHR_10_OFFSET ; 
 int MPSC_INTR_CAUSE_RCC ; 
 int in_8 (scalar_t__) ; 
 scalar_t__ mpsc_base ; 
 int /*<<< orphan*/  mpsc_intr_cause ; 
 int /*<<< orphan*/  mv64x60_udbg_testc () ; 
 int /*<<< orphan*/  out_8 (scalar_t__,int) ; 
 int /*<<< orphan*/  out_le32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mv64x60_udbg_getc(void)
{
	int cause = 0;
	int c;

	while (!mv64x60_udbg_testc())
		;

	c = in_8(mpsc_base + MPSC_0_CHR_10_OFFSET + 2);
	out_8(mpsc_base + MPSC_0_CHR_10_OFFSET + 2, c);
	out_le32(mpsc_intr_cause, cause & ~MPSC_INTR_CAUSE_RCC);
	return c;
}