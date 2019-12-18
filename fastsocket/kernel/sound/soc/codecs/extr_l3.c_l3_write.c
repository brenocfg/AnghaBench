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
typedef  int /*<<< orphan*/  u8 ;
struct l3_pins {int /*<<< orphan*/  (* setmode ) (int) ;int /*<<< orphan*/  (* setdat ) (int) ;int /*<<< orphan*/  (* setclk ) (int) ;int /*<<< orphan*/  mode_hold; int /*<<< orphan*/  mode_setup; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  sendbyte (struct l3_pins*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sendbytes (struct l3_pins*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 
 int /*<<< orphan*/  stub3 (int) ; 
 int /*<<< orphan*/  stub4 (int) ; 
 int /*<<< orphan*/  stub5 (int) ; 
 int /*<<< orphan*/  stub6 (int) ; 
 int /*<<< orphan*/  stub7 (int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

int l3_write(struct l3_pins *adap, u8 addr, u8 *data, int len)
{
	adap->setclk(1);
	adap->setdat(1);
	adap->setmode(1);
	udelay(adap->mode);

	adap->setmode(0);
	udelay(adap->mode_setup);
	sendbyte(adap, addr);
	udelay(adap->mode_hold);

	sendbytes(adap, data, len);

	adap->setclk(1);
	adap->setdat(1);
	adap->setmode(0);

	return len;
}