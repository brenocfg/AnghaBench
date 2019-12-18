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
struct cm4000_dev {int flags1; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ATR_VALID ; 
 int /*<<< orphan*/  IS_CMM_ABSENT ; 
 int /*<<< orphan*/  REG_FLAGS0 (unsigned int) ; 
 int /*<<< orphan*/  REG_FLAGS1 (unsigned int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xoutb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int io_detect_cm4000(unsigned int iobase, struct cm4000_dev *dev)
{

	/* note: statemachine is assumed to be reset */
	if (inb(REG_FLAGS0(iobase)) & 8) {
		clear_bit(IS_ATR_VALID, &dev->flags);
		set_bit(IS_CMM_ABSENT, &dev->flags);
		return 0;	/* detect CMM = 1 -> failure */
	}
	/* xoutb(0x40, REG_FLAGS1(iobase)); detectCMM */
	xoutb(dev->flags1 | 0x40, REG_FLAGS1(iobase));
	if ((inb(REG_FLAGS0(iobase)) & 8) == 0) {
		clear_bit(IS_ATR_VALID, &dev->flags);
		set_bit(IS_CMM_ABSENT, &dev->flags);
		return 0;	/* detect CMM=0 -> failure */
	}
	/* clear detectCMM again by restoring original flags1 */
	xoutb(dev->flags1, REG_FLAGS1(iobase));
	return 1;
}