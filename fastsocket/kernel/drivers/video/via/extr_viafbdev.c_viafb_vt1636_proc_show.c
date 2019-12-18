#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct seq_file {int dummy; } ;
struct TYPE_6__ {int lvds_chip_name; } ;
struct TYPE_5__ {TYPE_1__* chip_info; int /*<<< orphan*/  lvds_setting_info2; int /*<<< orphan*/  lvds_setting_info; } ;
struct TYPE_4__ {TYPE_3__ lvds_chip_info2; TYPE_3__ lvds_chip_info; } ;

/* Variables and functions */
#define  VT1636_LVDS 128 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int) ; 
 int viafb_gpio_i2c_read_lvds (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 TYPE_2__* viaparinfo ; 

__attribute__((used)) static int viafb_vt1636_proc_show(struct seq_file *m, void *v)
{
	u8 vt1636_08 = 0, vt1636_09 = 0;
	switch (viaparinfo->chip_info->lvds_chip_info.lvds_chip_name) {
	case VT1636_LVDS:
		vt1636_08 =
		    viafb_gpio_i2c_read_lvds(viaparinfo->lvds_setting_info,
		    &viaparinfo->chip_info->lvds_chip_info, 0x08) & 0x0f;
		vt1636_09 =
		    viafb_gpio_i2c_read_lvds(viaparinfo->lvds_setting_info,
		    &viaparinfo->chip_info->lvds_chip_info, 0x09) & 0x1f;
		seq_printf(m, "%x %x\n", vt1636_08, vt1636_09);
		break;
	default:
		break;
	}
	switch (viaparinfo->chip_info->lvds_chip_info2.lvds_chip_name) {
	case VT1636_LVDS:
		vt1636_08 =
		    viafb_gpio_i2c_read_lvds(viaparinfo->lvds_setting_info2,
			&viaparinfo->chip_info->lvds_chip_info2, 0x08) & 0x0f;
		vt1636_09 =
		    viafb_gpio_i2c_read_lvds(viaparinfo->lvds_setting_info2,
			&viaparinfo->chip_info->lvds_chip_info2, 0x09) & 0x1f;
		seq_printf(m, " %x %x\n", vt1636_08, vt1636_09);
		break;
	default:
		break;
	}
	return 0;
}