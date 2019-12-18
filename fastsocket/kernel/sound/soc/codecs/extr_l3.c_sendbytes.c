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
struct l3_pins {int /*<<< orphan*/  mode_setup; int /*<<< orphan*/  (* setmode ) (int) ;int /*<<< orphan*/  mode; int /*<<< orphan*/  mode_hold; } ;

/* Variables and functions */
 int /*<<< orphan*/  sendbyte (struct l3_pins*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sendbytes(struct l3_pins *adap, const u8 *buf,
		      int len)
{
	int i;

	for (i = 0; i < len; i++) {
		if (i) {
			udelay(adap->mode_hold);
			adap->setmode(0);
			udelay(adap->mode);
		}
		adap->setmode(1);
		udelay(adap->mode_setup);
		sendbyte(adap, buf[i]);
	}
}