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
struct pm2fb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM2R_RD_PALETTE_DATA ; 
 int /*<<< orphan*/  PM2R_RD_PALETTE_WRITE_ADDRESS ; 
 int /*<<< orphan*/  WAIT_FIFO (struct pm2fb_par*,int) ; 
 int /*<<< orphan*/  pm2_WR (struct pm2fb_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void clear_palette(struct pm2fb_par *p)
{
	int i = 256;

	WAIT_FIFO(p, 1);
	pm2_WR(p, PM2R_RD_PALETTE_WRITE_ADDRESS, 0);
	wmb();
	while (i--) {
		WAIT_FIFO(p, 3);
		pm2_WR(p, PM2R_RD_PALETTE_DATA, 0);
		pm2_WR(p, PM2R_RD_PALETTE_DATA, 0);
		pm2_WR(p, PM2R_RD_PALETTE_DATA, 0);
	}
}