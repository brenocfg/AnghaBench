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
 int /*<<< orphan*/  GPIO (struct zoran*,int,int) ; 
 int default_mux ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
avs6eyes_init (struct zoran *zr)
{
	// AverMedia 6-Eyes original driver by Christer Weinigel

	// Lifted straight from Christer's old driver and
	// modified slightly by Martin Samuelsson.

	int mux = default_mux; /* 1 = BT866, 7 = VID1 */

	GPIO(zr, 4, 1); /* Bt866 SLEEP on */
	udelay(2);

	GPIO(zr, 0, 1); /* ZR36060 /RESET on */
	GPIO(zr, 1, 0); /* ZR36060 /SLEEP on */
	GPIO(zr, 2, mux & 1);   /* MUX S0 */
	GPIO(zr, 3, 0); /* /FRAME on */
	GPIO(zr, 4, 0); /* Bt866 SLEEP off */
	GPIO(zr, 5, mux & 2);   /* MUX S1 */
	GPIO(zr, 6, 0); /* ? */
	GPIO(zr, 7, mux & 4);   /* MUX S2 */

}