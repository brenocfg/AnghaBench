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
struct l3_pins {int /*<<< orphan*/  clock_high; int /*<<< orphan*/  (* setclk ) (int) ;int /*<<< orphan*/  data_setup; int /*<<< orphan*/  (* setdat ) (unsigned int) ;int /*<<< orphan*/  data_hold; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (unsigned int) ; 
 int /*<<< orphan*/  stub3 (int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sendbyte(struct l3_pins *adap, unsigned int byte)
{
	int i;

	for (i = 0; i < 8; i++) {
		adap->setclk(0);
		udelay(adap->data_hold);
		adap->setdat(byte & 1);
		udelay(adap->data_setup);
		adap->setclk(1);
		udelay(adap->clock_high);
		byte >>= 1;
	}
}