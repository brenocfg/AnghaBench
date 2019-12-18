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
struct VT1636_DPA_SETTING {int PanelSizeID; } ;

/* Variables and functions */

__attribute__((used)) static int get_lvds_dpa_setting_index(int panel_size_id,
			     struct VT1636_DPA_SETTING *p_vt1636_dpasetting_tbl,
			       int tbl_size)
{
	int i;

	for (i = 0; i < tbl_size; i++) {
		if (panel_size_id == p_vt1636_dpasetting_tbl->PanelSizeID)
			return i;

		p_vt1636_dpasetting_tbl++;
	}

	return 0;
}