#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vc_data {int dummy; } ;
struct TYPE_6__ {short xymove; } ;
struct TYPE_5__ {int drawmode0; short xystarti; short xyendi; } ;
struct TYPE_7__ {TYPE_2__ go; TYPE_1__ set; } ;

/* Variables and functions */
 int NPORT_DMODE0_BLOCK ; 
 int NPORT_DMODE0_DOSETUP ; 
 int NPORT_DMODE0_S2S ; 
 int NPORT_DMODE0_STOPX ; 
 int NPORT_DMODE0_STOPY ; 
 int /*<<< orphan*/  newport_wait (TYPE_3__*) ; 
 TYPE_3__* npregs ; 
 int topscan ; 

__attribute__((used)) static void newport_bmove(struct vc_data *vc, int sy, int sx, int dy,
			  int dx, int h, int w)
{
	short xs, ys, xe, ye, xoffs, yoffs, tmp;

	xs = sx << 3;
	xe = ((sx + w) << 3) - 1;
	/*
	 * as bmove is only used to move stuff around in the same line
	 * (h == 1), we don't care about wrap arounds caused by topscan != 0
	 */
	ys = ((sy << 4) + topscan) & 0x3ff;
	ye = (((sy + h) << 4) - 1 + topscan) & 0x3ff;
	xoffs = (dx - sx) << 3;
	yoffs = (dy - sy) << 4;
	if (xoffs > 0) {
		/* move to the right, exchange starting points */
		tmp = xe;
		xe = xs;
		xs = tmp;
	}
	newport_wait(npregs);
	npregs->set.drawmode0 = (NPORT_DMODE0_S2S | NPORT_DMODE0_BLOCK |
				 NPORT_DMODE0_DOSETUP | NPORT_DMODE0_STOPX
				 | NPORT_DMODE0_STOPY);
	npregs->set.xystarti = (xs << 16) | ys;
	npregs->set.xyendi = (xe << 16) | ye;
	npregs->go.xymove = (xoffs << 16) | yoffs;
}