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
struct gemtek {int muted; int /*<<< orphan*/  lock; int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int /*<<< orphan*/  BU2614_FMES ; 
 int /*<<< orphan*/  BU2614_FMUN ; 
 int /*<<< orphan*/  BU2614_FREQ ; 
 int /*<<< orphan*/  BU2614_PORT ; 
 int /*<<< orphan*/  BU2614_STDF ; 
 int /*<<< orphan*/  BU2614_SWAL ; 
 int /*<<< orphan*/  BU2614_SWIN ; 
 int /*<<< orphan*/  BU2614_TEST ; 
 int GEMTEK_MT ; 
 int /*<<< orphan*/  GEMTEK_PLL_OFF ; 
 int /*<<< orphan*/  SHORT_DELAY ; 
 int /*<<< orphan*/  gemtek_bu2614_set (struct gemtek*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gemtek_bu2614_transmit (struct gemtek*) ; 
 scalar_t__ hardmute ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gemtek_mute(struct gemtek *gt)
{
	int i;

	gt->muted = 1;

	if (hardmute) {
		/* Turn off PLL, disable data output */
		gemtek_bu2614_set(gt, BU2614_PORT, 0);
		gemtek_bu2614_set(gt, BU2614_FMES, 0);	/* CT bit off	*/
		gemtek_bu2614_set(gt, BU2614_SWIN, 0);	/* FM-mode	*/
		gemtek_bu2614_set(gt, BU2614_SWAL, 0);
		gemtek_bu2614_set(gt, BU2614_FMUN, 0);	/* GT bit off	*/
		gemtek_bu2614_set(gt, BU2614_TEST, 0);
		gemtek_bu2614_set(gt, BU2614_STDF, GEMTEK_PLL_OFF);
		gemtek_bu2614_set(gt, BU2614_FREQ, 0);
		gemtek_bu2614_transmit(gt);
		return;
	}

	mutex_lock(&gt->lock);

	/* Read bus contents (CE, CK and DA). */
	i = inb_p(gt->io);
	/* Write it back with mute flag set. */
	outb_p((i >> 5) | GEMTEK_MT, gt->io);
	udelay(SHORT_DELAY);

	mutex_unlock(&gt->lock);
}