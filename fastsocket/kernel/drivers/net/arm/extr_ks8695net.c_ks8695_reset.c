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
struct ks8695_priv {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DRXC_RB ; 
 int DRXC_RU ; 
 int DTXC_TAC ; 
 int DTXC_TEP ; 
 int DTXC_TRST ; 
 int /*<<< orphan*/  KS8695_DRXC ; 
 int /*<<< orphan*/  KS8695_DTXC ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*) ; 
 int ks8695_readreg (struct ks8695_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks8695_writereg (struct ks8695_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int watchdog ; 

__attribute__((used)) static void
ks8695_reset(struct ks8695_priv *ksp)
{
	int reset_timeout = watchdog;
	/* Issue the reset via the TX DMA control register */
	ks8695_writereg(ksp, KS8695_DTXC, DTXC_TRST);
	while (reset_timeout--) {
		if (!(ks8695_readreg(ksp, KS8695_DTXC) & DTXC_TRST))
			break;
		msleep(1);
	}

	if (reset_timeout < 0) {
		dev_crit(ksp->dev,
			 "Timeout waiting for DMA engines to reset\n");
		/* And blithely carry on */
	}

	/* Definitely wait long enough before attempting to program
	 * the engines
	 */
	msleep(10);

	/* RX: unicast and broadcast */
	ks8695_writereg(ksp, KS8695_DRXC, DRXC_RU | DRXC_RB);
	/* TX: pad and add CRC */
	ks8695_writereg(ksp, KS8695_DTXC, DTXC_TEP | DTXC_TAC);
}