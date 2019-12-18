#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* fbdev; int /*<<< orphan*/  dss1_fck; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__ dispc ; 
 int max (int,int) ; 

__attribute__((used)) static void calc_ck_div(int is_tft, int pck, int *lck_div, int *pck_div)
{
	unsigned long fck, lck;

	*lck_div = 1;
	pck = max(1, pck);
	fck = clk_get_rate(dispc.dss1_fck);
	lck = fck;
	*pck_div = (lck + pck - 1) / pck;
	if (is_tft)
		*pck_div = max(2, *pck_div);
	else
		*pck_div = max(3, *pck_div);
	if (*pck_div > 255) {
		*pck_div = 255;
		lck = pck * *pck_div;
		*lck_div = fck / lck;
		BUG_ON(*lck_div < 1);
		if (*lck_div > 255) {
			*lck_div = 255;
			dev_warn(dispc.fbdev->dev, "pixclock %d kHz too low.\n",
				 pck / 1000);
		}
	}
}