#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct io_register {int dummy; } ;
struct display_timing {int ver_addr; int ver_blank_start; int ver_sync_start; int /*<<< orphan*/  ver_sync_end; int /*<<< orphan*/  ver_blank_end; int /*<<< orphan*/  ver_total; int /*<<< orphan*/  hor_blank_end; int /*<<< orphan*/  hor_blank_start; int /*<<< orphan*/  hor_total; } ;
struct TYPE_22__ {int reg_num; struct io_register* reg; } ;
struct TYPE_21__ {int reg_num; struct io_register* reg; } ;
struct TYPE_20__ {int reg_num; struct io_register* reg; } ;
struct TYPE_19__ {int reg_num; struct io_register* reg; } ;
struct TYPE_18__ {int reg_num; struct io_register* reg; } ;
struct TYPE_17__ {int reg_num; struct io_register* reg; } ;
struct TYPE_16__ {int reg_num; struct io_register* reg; } ;
struct TYPE_15__ {int reg_num; struct io_register* reg; } ;
struct TYPE_14__ {scalar_t__ display_method; } ;
struct TYPE_13__ {TYPE_9__ ver_sync_end_shadow; TYPE_8__ ver_sync_start_shadow; TYPE_7__ ver_blank_end_shadow; TYPE_6__ ver_blank_start_shadow; TYPE_5__ ver_addr_shadow; TYPE_4__ ver_total_shadow; TYPE_3__ hor_blank_end_shadow; TYPE_2__ hor_total_shadow; } ;
struct TYPE_12__ {TYPE_1__* lvds_setting_info; } ;

/* Variables and functions */
#define  H_BLANK_END_SHADOW_INDEX 135 
#define  H_TOTAL_SHADOW_INDEX 134 
 int IGA2_HOR_BLANK_END_SHADOW_FORMULA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IGA2_HOR_TOTAL_SHADOW_FORMULA (int /*<<< orphan*/ ) ; 
 int IGA2_VER_ADDR_SHADOW_FORMULA (int) ; 
 int IGA2_VER_BLANK_END_SHADOW_FORMULA (int,int /*<<< orphan*/ ) ; 
 int IGA2_VER_BLANK_START_SHADOW_FORMULA (int) ; 
 int IGA2_VER_SYNC_END_SHADOW_FORMULA (int,int /*<<< orphan*/ ) ; 
 int IGA2_VER_SYNC_START_SHADOW_FORMULA (int) ; 
 int IGA2_VER_TOTAL_SHADOW_FORMULA (int /*<<< orphan*/ ) ; 
 scalar_t__ LCD_EXPANDSION ; 
 int /*<<< orphan*/  VIACR ; 
#define  V_ADDR_SHADOW_INDEX 133 
#define  V_BLANK_END_SHADOW_INDEX 132 
#define  V_BLANK_SATRT_SHADOW_INDEX 131 
#define  V_SYNC_END_SHADOW_INDEX 130 
#define  V_SYNC_SATRT_SHADOW_INDEX 129 
#define  V_TOTAL_SHADOW_INDEX 128 
 TYPE_11__ iga2_shadow_crtc_reg ; 
 int /*<<< orphan*/  viafb_load_reg (int,int,struct io_register*,int /*<<< orphan*/ ) ; 
 TYPE_10__* viaparinfo ; 

__attribute__((used)) static void load_crtc_shadow_timing(struct display_timing mode_timing,
			     struct display_timing panel_timing)
{
	struct io_register *reg = NULL;
	int i;
	int viafb_load_reg_Num = 0;
	int reg_value = 0;

	if (viaparinfo->lvds_setting_info->display_method == LCD_EXPANDSION) {
		/* Expansion */
		for (i = 12; i < 20; i++) {
			switch (i) {
			case H_TOTAL_SHADOW_INDEX:
				reg_value =
				    IGA2_HOR_TOTAL_SHADOW_FORMULA
				    (panel_timing.hor_total);
				viafb_load_reg_Num =
				    iga2_shadow_crtc_reg.hor_total_shadow.
				    reg_num;
				reg = iga2_shadow_crtc_reg.hor_total_shadow.reg;
				break;
			case H_BLANK_END_SHADOW_INDEX:
				reg_value =
				    IGA2_HOR_BLANK_END_SHADOW_FORMULA
				    (panel_timing.hor_blank_start,
				     panel_timing.hor_blank_end);
				viafb_load_reg_Num =
				    iga2_shadow_crtc_reg.
				    hor_blank_end_shadow.reg_num;
				reg =
				    iga2_shadow_crtc_reg.
				    hor_blank_end_shadow.reg;
				break;
			case V_TOTAL_SHADOW_INDEX:
				reg_value =
				    IGA2_VER_TOTAL_SHADOW_FORMULA
				    (panel_timing.ver_total);
				viafb_load_reg_Num =
				    iga2_shadow_crtc_reg.ver_total_shadow.
				    reg_num;
				reg = iga2_shadow_crtc_reg.ver_total_shadow.reg;
				break;
			case V_ADDR_SHADOW_INDEX:
				reg_value =
				    IGA2_VER_ADDR_SHADOW_FORMULA
				    (panel_timing.ver_addr);
				viafb_load_reg_Num =
				    iga2_shadow_crtc_reg.ver_addr_shadow.
				    reg_num;
				reg = iga2_shadow_crtc_reg.ver_addr_shadow.reg;
				break;
			case V_BLANK_SATRT_SHADOW_INDEX:
				reg_value =
				    IGA2_VER_BLANK_START_SHADOW_FORMULA
				    (panel_timing.ver_blank_start);
				viafb_load_reg_Num =
				    iga2_shadow_crtc_reg.
				    ver_blank_start_shadow.reg_num;
				reg =
				    iga2_shadow_crtc_reg.
				    ver_blank_start_shadow.reg;
				break;
			case V_BLANK_END_SHADOW_INDEX:
				reg_value =
				    IGA2_VER_BLANK_END_SHADOW_FORMULA
				    (panel_timing.ver_blank_start,
				     panel_timing.ver_blank_end);
				viafb_load_reg_Num =
				    iga2_shadow_crtc_reg.
				    ver_blank_end_shadow.reg_num;
				reg =
				    iga2_shadow_crtc_reg.
				    ver_blank_end_shadow.reg;
				break;
			case V_SYNC_SATRT_SHADOW_INDEX:
				reg_value =
				    IGA2_VER_SYNC_START_SHADOW_FORMULA
				    (panel_timing.ver_sync_start);
				viafb_load_reg_Num =
				    iga2_shadow_crtc_reg.
				    ver_sync_start_shadow.reg_num;
				reg =
				    iga2_shadow_crtc_reg.
				    ver_sync_start_shadow.reg;
				break;
			case V_SYNC_END_SHADOW_INDEX:
				reg_value =
				    IGA2_VER_SYNC_END_SHADOW_FORMULA
				    (panel_timing.ver_sync_start,
				     panel_timing.ver_sync_end);
				viafb_load_reg_Num =
				    iga2_shadow_crtc_reg.
				    ver_sync_end_shadow.reg_num;
				reg =
				    iga2_shadow_crtc_reg.
				    ver_sync_end_shadow.reg;
				break;
			}
			viafb_load_reg(reg_value,
				viafb_load_reg_Num, reg, VIACR);
		}
	} else {		/* Centering */
		for (i = 12; i < 20; i++) {
			switch (i) {
			case H_TOTAL_SHADOW_INDEX:
				reg_value =
				    IGA2_HOR_TOTAL_SHADOW_FORMULA
				    (panel_timing.hor_total);
				viafb_load_reg_Num =
				    iga2_shadow_crtc_reg.hor_total_shadow.
				    reg_num;
				reg = iga2_shadow_crtc_reg.hor_total_shadow.reg;
				break;
			case H_BLANK_END_SHADOW_INDEX:
				reg_value =
				    IGA2_HOR_BLANK_END_SHADOW_FORMULA
				    (panel_timing.hor_blank_start,
				     panel_timing.hor_blank_end);
				viafb_load_reg_Num =
				    iga2_shadow_crtc_reg.
				    hor_blank_end_shadow.reg_num;
				reg =
				    iga2_shadow_crtc_reg.
				    hor_blank_end_shadow.reg;
				break;
			case V_TOTAL_SHADOW_INDEX:
				reg_value =
				    IGA2_VER_TOTAL_SHADOW_FORMULA
				    (panel_timing.ver_total);
				viafb_load_reg_Num =
				    iga2_shadow_crtc_reg.ver_total_shadow.
				    reg_num;
				reg = iga2_shadow_crtc_reg.ver_total_shadow.reg;
				break;
			case V_ADDR_SHADOW_INDEX:
				reg_value =
				    IGA2_VER_ADDR_SHADOW_FORMULA
				    (mode_timing.ver_addr);
				viafb_load_reg_Num =
				    iga2_shadow_crtc_reg.ver_addr_shadow.
				    reg_num;
				reg = iga2_shadow_crtc_reg.ver_addr_shadow.reg;
				break;
			case V_BLANK_SATRT_SHADOW_INDEX:
				reg_value =
				    IGA2_VER_BLANK_START_SHADOW_FORMULA
				    (mode_timing.ver_blank_start);
				viafb_load_reg_Num =
				    iga2_shadow_crtc_reg.
				    ver_blank_start_shadow.reg_num;
				reg =
				    iga2_shadow_crtc_reg.
				    ver_blank_start_shadow.reg;
				break;
			case V_BLANK_END_SHADOW_INDEX:
				reg_value =
				    IGA2_VER_BLANK_END_SHADOW_FORMULA
				    (panel_timing.ver_blank_start,
				     panel_timing.ver_blank_end);
				viafb_load_reg_Num =
				    iga2_shadow_crtc_reg.
				    ver_blank_end_shadow.reg_num;
				reg =
				    iga2_shadow_crtc_reg.
				    ver_blank_end_shadow.reg;
				break;
			case V_SYNC_SATRT_SHADOW_INDEX:
				reg_value =
				    IGA2_VER_SYNC_START_SHADOW_FORMULA(
				    (panel_timing.ver_sync_start -
				    panel_timing.ver_blank_start) +
				    (panel_timing.ver_addr -
				    mode_timing.ver_addr) / 2 +
				    mode_timing.ver_addr);
				viafb_load_reg_Num =
				    iga2_shadow_crtc_reg.ver_sync_start_shadow.
				    reg_num;
				reg =
				    iga2_shadow_crtc_reg.ver_sync_start_shadow.
				    reg;
				break;
			case V_SYNC_END_SHADOW_INDEX:
				reg_value =
				    IGA2_VER_SYNC_END_SHADOW_FORMULA(
				    (panel_timing.ver_sync_start -
				    panel_timing.ver_blank_start) +
				    (panel_timing.ver_addr -
				    mode_timing.ver_addr) / 2 +
				    mode_timing.ver_addr,
				    panel_timing.ver_sync_end);
				viafb_load_reg_Num =
				    iga2_shadow_crtc_reg.ver_sync_end_shadow.
				    reg_num;
				reg =
				    iga2_shadow_crtc_reg.ver_sync_end_shadow.
				    reg;
				break;
			}
			viafb_load_reg(reg_value,
				viafb_load_reg_Num, reg, VIACR);
		}
	}
}