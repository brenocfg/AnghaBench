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
struct sh_sci_spi {int val; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSPTR (struct sh_sci_spi*) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void setbits(struct sh_sci_spi *sp, int bits, int on)
{
	/*
	 * We are the only user of SCSPTR so no locking is required.
	 * Reading bit 2 and 0 in SCSPTR gives pin state as input.
	 * Writing the same bits sets the output value.
	 * This makes regular read-modify-write difficult so we
	 * use sp->val to keep track of the latest register value.
	 */

	if (on)
		sp->val |= bits;
	else
		sp->val &= ~bits;

	iowrite8(sp->val, SCSPTR(sp));
}