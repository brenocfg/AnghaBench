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
 scalar_t__ MPSC_0_CR1_OFFSET ; 
 scalar_t__ MPSC_0_CR2_OFFSET ; 
 int MPSC_CHR_2_TCS ; 
 int in_le32 (scalar_t__) ; 
 scalar_t__ mpsc_base ; 
 int /*<<< orphan*/  out_le32 (scalar_t__,int) ; 

__attribute__((used)) static void mv64x60_udbg_putc(char c)
{
	if (c == '\n')
		mv64x60_udbg_putc('\r');

	while(in_le32(mpsc_base + MPSC_0_CR2_OFFSET) & MPSC_CHR_2_TCS)
		;
	out_le32(mpsc_base + MPSC_0_CR1_OFFSET, c);
	out_le32(mpsc_base + MPSC_0_CR2_OFFSET, MPSC_CHR_2_TCS);
}