#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct carmine_fb {TYPE_1__* res; } ;
struct TYPE_2__ {int hdp; int vdp; int htp; int hsp; int hsw; int vtr; int vsp; int vsw; int disp_mode; } ;

/* Variables and functions */
 int CARMINE_DEN ; 
 int CARMINE_DISP_DCM_MASK ; 
 int CARMINE_DISP_HDB_SHIFT ; 
 int CARMINE_DISP_HSW_SHIFT ; 
 int CARMINE_DISP_HTP_SHIFT ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_DCM1 ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_H_PERIOD ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_H_TOTAL ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_V_H_W_H_POS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_V_PERIOD_POS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_V_TOTAL ; 
 int CARMINE_DISP_VDP_SHIFT ; 
 int CARMINE_DISP_VSW_SHIFT ; 
 int CARMINE_DISP_VTR_SHIFT ; 
 int CARMINE_L0E ; 
 int c_get_disp_reg (struct carmine_fb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_set_disp_reg (struct carmine_fb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_display_parameters(struct carmine_fb *par)
{
	u32 mode;
	u32 hdp, vdp, htp, hsp, hsw, vtr, vsp, vsw;

	/*
	 * display timing. Parameters are decreased by one because hardware
	 * spec is 0 to (n - 1)
	 * */
	hdp = par->res->hdp - 1;
	vdp = par->res->vdp - 1;
	htp = par->res->htp - 1;
	hsp = par->res->hsp - 1;
	hsw = par->res->hsw - 1;
	vtr = par->res->vtr - 1;
	vsp = par->res->vsp - 1;
	vsw = par->res->vsw - 1;

	c_set_disp_reg(par, CARMINE_DISP_REG_H_TOTAL,
			htp << CARMINE_DISP_HTP_SHIFT);
	c_set_disp_reg(par, CARMINE_DISP_REG_H_PERIOD,
			(hdp << CARMINE_DISP_HDB_SHIFT)	| hdp);
	c_set_disp_reg(par, CARMINE_DISP_REG_V_H_W_H_POS,
			(vsw << CARMINE_DISP_VSW_SHIFT) |
			(hsw << CARMINE_DISP_HSW_SHIFT) |
			(hsp));
	c_set_disp_reg(par, CARMINE_DISP_REG_V_TOTAL,
			vtr << CARMINE_DISP_VTR_SHIFT);
	c_set_disp_reg(par, CARMINE_DISP_REG_V_PERIOD_POS,
			(vdp << CARMINE_DISP_VDP_SHIFT) | vsp);

	/* clock */
	mode = c_get_disp_reg(par, CARMINE_DISP_REG_DCM1);
	mode = (mode & ~CARMINE_DISP_DCM_MASK) |
		(par->res->disp_mode & CARMINE_DISP_DCM_MASK);
	/* enable video output and layer 0 */
	mode |= CARMINE_DEN | CARMINE_L0E;
	c_set_disp_reg(par, CARMINE_DISP_REG_DCM1, mode);
}