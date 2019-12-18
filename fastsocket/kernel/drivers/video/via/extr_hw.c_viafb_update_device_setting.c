#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* lvds_setting_info2; TYPE_3__* lvds_setting_info; TYPE_2__* tmds_setting_info; TYPE_1__* crt_setting_info; } ;
struct TYPE_9__ {int h_active; int v_active; int bpp; int refresh_rate; scalar_t__ iga_path; } ;
struct TYPE_8__ {int h_active; int v_active; int bpp; int refresh_rate; scalar_t__ iga_path; } ;
struct TYPE_7__ {int h_active; int v_active; int bpp; int refresh_rate; scalar_t__ iga_path; } ;
struct TYPE_6__ {int h_active; int v_active; int bpp; int refresh_rate; } ;

/* Variables and functions */
 scalar_t__ IGA2 ; 
 TYPE_5__* viaparinfo ; 

void viafb_update_device_setting(int hres, int vres,
	int bpp, int vmode_refresh, int flag)
{
	if (flag == 0) {
		viaparinfo->crt_setting_info->h_active = hres;
		viaparinfo->crt_setting_info->v_active = vres;
		viaparinfo->crt_setting_info->bpp = bpp;
		viaparinfo->crt_setting_info->refresh_rate =
			vmode_refresh;

		viaparinfo->tmds_setting_info->h_active = hres;
		viaparinfo->tmds_setting_info->v_active = vres;
		viaparinfo->tmds_setting_info->bpp = bpp;
		viaparinfo->tmds_setting_info->refresh_rate =
			vmode_refresh;

		viaparinfo->lvds_setting_info->h_active = hres;
		viaparinfo->lvds_setting_info->v_active = vres;
		viaparinfo->lvds_setting_info->bpp = bpp;
		viaparinfo->lvds_setting_info->refresh_rate =
			vmode_refresh;
		viaparinfo->lvds_setting_info2->h_active = hres;
		viaparinfo->lvds_setting_info2->v_active = vres;
		viaparinfo->lvds_setting_info2->bpp = bpp;
		viaparinfo->lvds_setting_info2->refresh_rate =
			vmode_refresh;
	} else {

		if (viaparinfo->tmds_setting_info->iga_path == IGA2) {
			viaparinfo->tmds_setting_info->h_active = hres;
			viaparinfo->tmds_setting_info->v_active = vres;
			viaparinfo->tmds_setting_info->bpp = bpp;
			viaparinfo->tmds_setting_info->refresh_rate =
				vmode_refresh;
		}

		if (viaparinfo->lvds_setting_info->iga_path == IGA2) {
			viaparinfo->lvds_setting_info->h_active = hres;
			viaparinfo->lvds_setting_info->v_active = vres;
			viaparinfo->lvds_setting_info->bpp = bpp;
			viaparinfo->lvds_setting_info->refresh_rate =
				vmode_refresh;
		}
		if (IGA2 == viaparinfo->lvds_setting_info2->iga_path) {
			viaparinfo->lvds_setting_info2->h_active = hres;
			viaparinfo->lvds_setting_info2->v_active = vres;
			viaparinfo->lvds_setting_info2->bpp = bpp;
			viaparinfo->lvds_setting_info2->refresh_rate =
				vmode_refresh;
		}
	}
}