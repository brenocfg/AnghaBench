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
struct zoran {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZR36057_GPPGCR1 ; 
 int /*<<< orphan*/  ZR36057_JPC ; 
 int /*<<< orphan*/  ZR36057_SPGPPCR ; 
 int ZR36057_SPGPPCR_SoftReset ; 
 int /*<<< orphan*/  btor (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

void
zr36057_restart (struct zoran *zr)
{
	btwrite(0, ZR36057_SPGPPCR);
	mdelay(1);
	btor(ZR36057_SPGPPCR_SoftReset, ZR36057_SPGPPCR);
	mdelay(1);

	/* assert P_Reset */
	btwrite(0, ZR36057_JPC);
	/* set up GPIO direction - all output */
	btwrite(ZR36057_SPGPPCR_SoftReset | 0, ZR36057_SPGPPCR);

	/* set up GPIO pins and guest bus timing */
	btwrite((0x81 << 24) | 0x8888, ZR36057_GPPGCR1);
}