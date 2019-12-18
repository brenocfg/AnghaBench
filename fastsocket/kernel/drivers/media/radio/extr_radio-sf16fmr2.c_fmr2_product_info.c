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
struct fmr2 {int card_type; int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fmr2_product_info(struct fmr2 *dev)
{
	int n = inb(dev->io);

	n &= 0xC1;
	if (n == 0) {
		/* this should support volume set */
		dev->card_type = 12;
		return 0;
	}
	/* not volume (mine is 11) */
	dev->card_type = (n == 128) ? 11 : 0;
	return n;
}