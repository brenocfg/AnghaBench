#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int delay; int saved_r0; int saved_r2; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int) ; 
 int r0 () ; 
 int r1 () ; 
 int r2 () ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static int frpw_test_pnp ( PIA *pi )

/*  returns chip_type:   0 = Xilinx, 1 = ASIC   */

{	int olddelay, a, b;

#ifdef FRPW_HARD_RESET
        w0(0); w2(8); udelay(50); w2(0xc);   /* parallel bus reset */
        mdelay(1500);
#endif

	olddelay = pi->delay;
	pi->delay = 10;

	pi->saved_r0 = r0();
        pi->saved_r2 = r2();
	
	w2(4); w0(4); w2(6); w2(7);
	a = r1() & 0xff; w2(4); b = r1() & 0xff;
	w2(0xc); w2(0xe); w2(4);

	pi->delay = olddelay;
        w0(pi->saved_r0);
        w2(pi->saved_r2);

	return ((~a&0x40) && (b&0x40));
}