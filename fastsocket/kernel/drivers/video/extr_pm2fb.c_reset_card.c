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
struct pm2fb_par {scalar_t__ type; int mem_control; int boot_address; int mem_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int PM2F_BEING_RESET ; 
 int /*<<< orphan*/  PM2R_BOOT_ADDRESS ; 
 int /*<<< orphan*/  PM2R_FIFO_DISCON ; 
 int /*<<< orphan*/  PM2R_MEM_CONFIG ; 
 int /*<<< orphan*/  PM2R_MEM_CONTROL ; 
 int /*<<< orphan*/  PM2R_RESET_STATUS ; 
 int /*<<< orphan*/  PM2VR_RD_INDEX_HIGH ; 
 scalar_t__ PM2_TYPE_PERMEDIA2V ; 
 int /*<<< orphan*/  WAIT_FIFO (struct pm2fb_par*,int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  mb () ; 
 int pm2_RD (struct pm2fb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm2_WR (struct pm2fb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void reset_card(struct pm2fb_par *p)
{
	if (p->type == PM2_TYPE_PERMEDIA2V)
		pm2_WR(p, PM2VR_RD_INDEX_HIGH, 0);
	pm2_WR(p, PM2R_RESET_STATUS, 0);
	mb();
	while (pm2_RD(p, PM2R_RESET_STATUS) & PM2F_BEING_RESET)
		cpu_relax();
	mb();
#ifdef CONFIG_FB_PM2_FIFO_DISCONNECT
	DPRINTK("FIFO disconnect enabled\n");
	pm2_WR(p, PM2R_FIFO_DISCON, 1);
	mb();
#endif

	/* Restore stashed memory config information from probe */
	WAIT_FIFO(p, 3);
	pm2_WR(p, PM2R_MEM_CONTROL, p->mem_control);
	pm2_WR(p, PM2R_BOOT_ADDRESS, p->boot_address);
	wmb();
	pm2_WR(p, PM2R_MEM_CONFIG, p->mem_config);
}