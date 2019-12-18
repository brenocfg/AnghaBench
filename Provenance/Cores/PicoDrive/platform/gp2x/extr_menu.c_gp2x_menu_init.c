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

/* Variables and functions */
#define  GP2X_DEV_CAANOO 130 
#define  GP2X_DEV_GP2X 129 
#define  GP2X_DEV_WIZ 128 
 int /*<<< orphan*/  MA_CTRL_DEADZONE ; 
 int /*<<< orphan*/  MA_OPT2_A_SN_GAMMA ; 
 int /*<<< orphan*/  MA_OPT2_GAMMA ; 
 int /*<<< orphan*/  MA_OPT_ARM940_SOUND ; 
 int /*<<< orphan*/  MA_OPT_TEARING_FIX ; 
 int /*<<< orphan*/  e_menu_adv_options ; 
 int /*<<< orphan*/  e_menu_gfx_options ; 
 int /*<<< orphan*/  e_menu_keyconfig ; 
 int gp2x_dev_id ; 
 int /*<<< orphan*/  me_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ ** men_scaling_opts ; 

void gp2x_menu_init(void)
{
	/* disable by default.. */
	me_enable(e_menu_adv_options, MA_OPT_ARM940_SOUND, 0);
	me_enable(e_menu_gfx_options, MA_OPT_TEARING_FIX, 0);
	me_enable(e_menu_gfx_options, MA_OPT2_GAMMA, 0);
	me_enable(e_menu_gfx_options, MA_OPT2_A_SN_GAMMA, 0);

	switch (gp2x_dev_id) {
	case GP2X_DEV_GP2X:
		me_enable(e_menu_adv_options, MA_OPT_ARM940_SOUND, 1);
		me_enable(e_menu_gfx_options, MA_OPT2_GAMMA, 1);
		me_enable(e_menu_gfx_options, MA_OPT2_A_SN_GAMMA, 1);
		break;
	case GP2X_DEV_WIZ:
		me_enable(e_menu_gfx_options, MA_OPT_TEARING_FIX, 1);
		break;
	case GP2X_DEV_CAANOO:
		break;
	default:
		break;
	}

	if (gp2x_dev_id != GP2X_DEV_GP2X)
		men_scaling_opts[2] = NULL; /* leave only off and sw */

	if (gp2x_dev_id != GP2X_DEV_CAANOO)
		me_enable(e_menu_keyconfig, MA_CTRL_DEADZONE, 0);
}