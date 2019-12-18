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
struct mcp {int dummy; } ;

/* Variables and functions */
 int Ser4MCCR0 ; 

__attribute__((used)) static void
mcp_sa11x0_set_audio_divisor(struct mcp *mcp, unsigned int divisor)
{
	unsigned int mccr0;

	divisor /= 32;

	mccr0 = Ser4MCCR0 & ~0x0000007f;
	mccr0 |= divisor;
	Ser4MCCR0 = mccr0;
}