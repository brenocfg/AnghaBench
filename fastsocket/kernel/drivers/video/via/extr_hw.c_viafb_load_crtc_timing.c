#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_56__   TYPE_9__ ;
typedef  struct TYPE_55__   TYPE_8__ ;
typedef  struct TYPE_54__   TYPE_7__ ;
typedef  struct TYPE_53__   TYPE_6__ ;
typedef  struct TYPE_52__   TYPE_5__ ;
typedef  struct TYPE_51__   TYPE_4__ ;
typedef  struct TYPE_50__   TYPE_3__ ;
typedef  struct TYPE_49__   TYPE_2__ ;
typedef  struct TYPE_48__   TYPE_28__ ;
typedef  struct TYPE_47__   TYPE_27__ ;
typedef  struct TYPE_46__   TYPE_26__ ;
typedef  struct TYPE_45__   TYPE_25__ ;
typedef  struct TYPE_44__   TYPE_24__ ;
typedef  struct TYPE_43__   TYPE_23__ ;
typedef  struct TYPE_42__   TYPE_22__ ;
typedef  struct TYPE_41__   TYPE_21__ ;
typedef  struct TYPE_40__   TYPE_20__ ;
typedef  struct TYPE_39__   TYPE_1__ ;
typedef  struct TYPE_38__   TYPE_19__ ;
typedef  struct TYPE_37__   TYPE_18__ ;
typedef  struct TYPE_36__   TYPE_17__ ;
typedef  struct TYPE_35__   TYPE_16__ ;
typedef  struct TYPE_34__   TYPE_15__ ;
typedef  struct TYPE_33__   TYPE_14__ ;
typedef  struct TYPE_32__   TYPE_13__ ;
typedef  struct TYPE_31__   TYPE_12__ ;
typedef  struct TYPE_30__   TYPE_11__ ;
typedef  struct TYPE_29__   TYPE_10__ ;

/* Type definitions */
struct io_register {int dummy; } ;
struct display_timing {int /*<<< orphan*/  ver_sync_end; int /*<<< orphan*/  ver_sync_start; int /*<<< orphan*/  ver_blank_end; int /*<<< orphan*/  ver_blank_start; int /*<<< orphan*/  ver_addr; int /*<<< orphan*/  ver_total; int /*<<< orphan*/  hor_sync_end; int /*<<< orphan*/  hor_sync_start; int /*<<< orphan*/  hor_blank_end; int /*<<< orphan*/  hor_blank_start; int /*<<< orphan*/  hor_addr; int /*<<< orphan*/  hor_total; } ;
struct TYPE_56__ {int reg_num; struct io_register* reg; } ;
struct TYPE_55__ {int reg_num; struct io_register* reg; } ;
struct TYPE_54__ {int reg_num; struct io_register* reg; } ;
struct TYPE_53__ {int reg_num; struct io_register* reg; } ;
struct TYPE_52__ {int reg_num; struct io_register* reg; } ;
struct TYPE_51__ {int reg_num; struct io_register* reg; } ;
struct TYPE_50__ {int reg_num; struct io_register* reg; } ;
struct TYPE_49__ {int reg_num; struct io_register* reg; } ;
struct TYPE_35__ {int reg_num; struct io_register* reg; } ;
struct TYPE_34__ {int reg_num; struct io_register* reg; } ;
struct TYPE_33__ {int reg_num; struct io_register* reg; } ;
struct TYPE_32__ {int reg_num; struct io_register* reg; } ;
struct TYPE_31__ {int reg_num; struct io_register* reg; } ;
struct TYPE_30__ {int reg_num; struct io_register* reg; } ;
struct TYPE_29__ {int reg_num; struct io_register* reg; } ;
struct TYPE_48__ {TYPE_16__ ver_sync_end; TYPE_15__ ver_sync_start; TYPE_14__ ver_blank_end; TYPE_13__ ver_blank_start; TYPE_12__ ver_addr; TYPE_11__ ver_total; TYPE_10__ hor_sync_end; TYPE_9__ hor_sync_start; TYPE_8__ hor_blank_end; TYPE_7__ hor_blank_start; TYPE_6__ hor_addr; TYPE_5__ hor_total; } ;
struct TYPE_39__ {int reg_num; struct io_register* reg; } ;
struct TYPE_45__ {int reg_num; struct io_register* reg; } ;
struct TYPE_44__ {int reg_num; struct io_register* reg; } ;
struct TYPE_43__ {int reg_num; struct io_register* reg; } ;
struct TYPE_42__ {int reg_num; struct io_register* reg; } ;
struct TYPE_40__ {int reg_num; struct io_register* reg; } ;
struct TYPE_38__ {int reg_num; struct io_register* reg; } ;
struct TYPE_37__ {int reg_num; struct io_register* reg; } ;
struct TYPE_36__ {int reg_num; struct io_register* reg; } ;
struct TYPE_47__ {TYPE_4__ ver_sync_end; TYPE_3__ ver_sync_start; TYPE_2__ ver_blank_end; TYPE_1__ ver_blank_start; TYPE_25__ ver_addr; TYPE_24__ ver_total; TYPE_23__ hor_sync_end; TYPE_22__ hor_sync_start; TYPE_20__ hor_blank_end; TYPE_19__ hor_blank_start; TYPE_18__ hor_addr; TYPE_17__ hor_total; } ;
struct TYPE_46__ {TYPE_21__* chip_info; } ;
struct TYPE_41__ {int /*<<< orphan*/  gfx_chip_name; } ;

/* Variables and functions */
#define  H_ADDR_INDEX 139 
#define  H_BLANK_END_INDEX 138 
#define  H_BLANK_START_INDEX 137 
#define  H_SYNC_END_INDEX 136 
#define  H_SYNC_START_INDEX 135 
#define  H_TOTAL_INDEX 134 
 int IGA1 ; 
 int IGA1_HOR_ADDR_FORMULA (int /*<<< orphan*/ ) ; 
 int IGA1_HOR_BLANK_END_FORMULA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IGA1_HOR_BLANK_START_FORMULA (int /*<<< orphan*/ ) ; 
 int IGA1_HOR_SYNC_END_FORMULA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IGA1_HOR_SYNC_START_FORMULA (int /*<<< orphan*/ ) ; 
 int IGA1_HOR_TOTAL_FORMULA (int /*<<< orphan*/ ) ; 
 int IGA1_VER_ADDR_FORMULA (int /*<<< orphan*/ ) ; 
 int IGA1_VER_BLANK_END_FORMULA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IGA1_VER_BLANK_START_FORMULA (int /*<<< orphan*/ ) ; 
 int IGA1_VER_SYNC_END_FORMULA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IGA1_VER_SYNC_START_FORMULA (int /*<<< orphan*/ ) ; 
 int IGA1_VER_TOTAL_FORMULA (int /*<<< orphan*/ ) ; 
 int IGA2 ; 
 int IGA2_HOR_ADDR_FORMULA (int /*<<< orphan*/ ) ; 
 int IGA2_HOR_BLANK_END_FORMULA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IGA2_HOR_BLANK_START_FORMULA (int /*<<< orphan*/ ) ; 
 int IGA2_HOR_SYNC_END_FORMULA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IGA2_HOR_SYNC_START_FORMULA (int /*<<< orphan*/ ) ; 
 int IGA2_HOR_TOTAL_FORMULA (int /*<<< orphan*/ ) ; 
 int IGA2_VER_ADDR_FORMULA (int /*<<< orphan*/ ) ; 
 int IGA2_VER_BLANK_END_FORMULA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IGA2_VER_BLANK_START_FORMULA (int /*<<< orphan*/ ) ; 
 int IGA2_VER_SYNC_END_FORMULA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IGA2_VER_SYNC_START_FORMULA (int /*<<< orphan*/ ) ; 
 int IGA2_VER_TOTAL_FORMULA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNICHROME_CN700 ; 
 int /*<<< orphan*/  VIACR ; 
#define  V_ADDR_INDEX 133 
#define  V_BLANK_END_INDEX 132 
#define  V_BLANK_START_INDEX 131 
#define  V_SYNC_END_INDEX 130 
#define  V_SYNC_START_INDEX 129 
#define  V_TOTAL_INDEX 128 
 TYPE_28__ iga1_crtc_reg ; 
 TYPE_27__ iga2_crtc_reg ; 
 int /*<<< orphan*/  viafb_load_reg (int,int,struct io_register*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viafb_lock_crt () ; 
 int /*<<< orphan*/  viafb_unlock_crt () ; 
 TYPE_26__* viaparinfo ; 

void viafb_load_crtc_timing(struct display_timing device_timing,
	int set_iga)
{
	int i;
	int viafb_load_reg_num = 0;
	int reg_value = 0;
	struct io_register *reg = NULL;

	viafb_unlock_crt();

	for (i = 0; i < 12; i++) {
		if (set_iga == IGA1) {
			switch (i) {
			case H_TOTAL_INDEX:
				reg_value =
				    IGA1_HOR_TOTAL_FORMULA(device_timing.
							   hor_total);
				viafb_load_reg_num =
					iga1_crtc_reg.hor_total.reg_num;
				reg = iga1_crtc_reg.hor_total.reg;
				break;
			case H_ADDR_INDEX:
				reg_value =
				    IGA1_HOR_ADDR_FORMULA(device_timing.
							  hor_addr);
				viafb_load_reg_num =
					iga1_crtc_reg.hor_addr.reg_num;
				reg = iga1_crtc_reg.hor_addr.reg;
				break;
			case H_BLANK_START_INDEX:
				reg_value =
				    IGA1_HOR_BLANK_START_FORMULA
				    (device_timing.hor_blank_start);
				viafb_load_reg_num =
				    iga1_crtc_reg.hor_blank_start.reg_num;
				reg = iga1_crtc_reg.hor_blank_start.reg;
				break;
			case H_BLANK_END_INDEX:
				reg_value =
				    IGA1_HOR_BLANK_END_FORMULA
				    (device_timing.hor_blank_start,
				     device_timing.hor_blank_end);
				viafb_load_reg_num =
				    iga1_crtc_reg.hor_blank_end.reg_num;
				reg = iga1_crtc_reg.hor_blank_end.reg;
				break;
			case H_SYNC_START_INDEX:
				reg_value =
				    IGA1_HOR_SYNC_START_FORMULA
				    (device_timing.hor_sync_start);
				viafb_load_reg_num =
				    iga1_crtc_reg.hor_sync_start.reg_num;
				reg = iga1_crtc_reg.hor_sync_start.reg;
				break;
			case H_SYNC_END_INDEX:
				reg_value =
				    IGA1_HOR_SYNC_END_FORMULA
				    (device_timing.hor_sync_start,
				     device_timing.hor_sync_end);
				viafb_load_reg_num =
				    iga1_crtc_reg.hor_sync_end.reg_num;
				reg = iga1_crtc_reg.hor_sync_end.reg;
				break;
			case V_TOTAL_INDEX:
				reg_value =
				    IGA1_VER_TOTAL_FORMULA(device_timing.
							   ver_total);
				viafb_load_reg_num =
					iga1_crtc_reg.ver_total.reg_num;
				reg = iga1_crtc_reg.ver_total.reg;
				break;
			case V_ADDR_INDEX:
				reg_value =
				    IGA1_VER_ADDR_FORMULA(device_timing.
							  ver_addr);
				viafb_load_reg_num =
					iga1_crtc_reg.ver_addr.reg_num;
				reg = iga1_crtc_reg.ver_addr.reg;
				break;
			case V_BLANK_START_INDEX:
				reg_value =
				    IGA1_VER_BLANK_START_FORMULA
				    (device_timing.ver_blank_start);
				viafb_load_reg_num =
				    iga1_crtc_reg.ver_blank_start.reg_num;
				reg = iga1_crtc_reg.ver_blank_start.reg;
				break;
			case V_BLANK_END_INDEX:
				reg_value =
				    IGA1_VER_BLANK_END_FORMULA
				    (device_timing.ver_blank_start,
				     device_timing.ver_blank_end);
				viafb_load_reg_num =
				    iga1_crtc_reg.ver_blank_end.reg_num;
				reg = iga1_crtc_reg.ver_blank_end.reg;
				break;
			case V_SYNC_START_INDEX:
				reg_value =
				    IGA1_VER_SYNC_START_FORMULA
				    (device_timing.ver_sync_start);
				viafb_load_reg_num =
				    iga1_crtc_reg.ver_sync_start.reg_num;
				reg = iga1_crtc_reg.ver_sync_start.reg;
				break;
			case V_SYNC_END_INDEX:
				reg_value =
				    IGA1_VER_SYNC_END_FORMULA
				    (device_timing.ver_sync_start,
				     device_timing.ver_sync_end);
				viafb_load_reg_num =
				    iga1_crtc_reg.ver_sync_end.reg_num;
				reg = iga1_crtc_reg.ver_sync_end.reg;
				break;

			}
		}

		if (set_iga == IGA2) {
			switch (i) {
			case H_TOTAL_INDEX:
				reg_value =
				    IGA2_HOR_TOTAL_FORMULA(device_timing.
							   hor_total);
				viafb_load_reg_num =
					iga2_crtc_reg.hor_total.reg_num;
				reg = iga2_crtc_reg.hor_total.reg;
				break;
			case H_ADDR_INDEX:
				reg_value =
				    IGA2_HOR_ADDR_FORMULA(device_timing.
							  hor_addr);
				viafb_load_reg_num =
					iga2_crtc_reg.hor_addr.reg_num;
				reg = iga2_crtc_reg.hor_addr.reg;
				break;
			case H_BLANK_START_INDEX:
				reg_value =
				    IGA2_HOR_BLANK_START_FORMULA
				    (device_timing.hor_blank_start);
				viafb_load_reg_num =
				    iga2_crtc_reg.hor_blank_start.reg_num;
				reg = iga2_crtc_reg.hor_blank_start.reg;
				break;
			case H_BLANK_END_INDEX:
				reg_value =
				    IGA2_HOR_BLANK_END_FORMULA
				    (device_timing.hor_blank_start,
				     device_timing.hor_blank_end);
				viafb_load_reg_num =
				    iga2_crtc_reg.hor_blank_end.reg_num;
				reg = iga2_crtc_reg.hor_blank_end.reg;
				break;
			case H_SYNC_START_INDEX:
				reg_value =
				    IGA2_HOR_SYNC_START_FORMULA
				    (device_timing.hor_sync_start);
				if (UNICHROME_CN700 <=
					viaparinfo->chip_info->gfx_chip_name)
					viafb_load_reg_num =
					    iga2_crtc_reg.hor_sync_start.
					    reg_num;
				else
					viafb_load_reg_num = 3;
				reg = iga2_crtc_reg.hor_sync_start.reg;
				break;
			case H_SYNC_END_INDEX:
				reg_value =
				    IGA2_HOR_SYNC_END_FORMULA
				    (device_timing.hor_sync_start,
				     device_timing.hor_sync_end);
				viafb_load_reg_num =
				    iga2_crtc_reg.hor_sync_end.reg_num;
				reg = iga2_crtc_reg.hor_sync_end.reg;
				break;
			case V_TOTAL_INDEX:
				reg_value =
				    IGA2_VER_TOTAL_FORMULA(device_timing.
							   ver_total);
				viafb_load_reg_num =
					iga2_crtc_reg.ver_total.reg_num;
				reg = iga2_crtc_reg.ver_total.reg;
				break;
			case V_ADDR_INDEX:
				reg_value =
				    IGA2_VER_ADDR_FORMULA(device_timing.
							  ver_addr);
				viafb_load_reg_num =
					iga2_crtc_reg.ver_addr.reg_num;
				reg = iga2_crtc_reg.ver_addr.reg;
				break;
			case V_BLANK_START_INDEX:
				reg_value =
				    IGA2_VER_BLANK_START_FORMULA
				    (device_timing.ver_blank_start);
				viafb_load_reg_num =
				    iga2_crtc_reg.ver_blank_start.reg_num;
				reg = iga2_crtc_reg.ver_blank_start.reg;
				break;
			case V_BLANK_END_INDEX:
				reg_value =
				    IGA2_VER_BLANK_END_FORMULA
				    (device_timing.ver_blank_start,
				     device_timing.ver_blank_end);
				viafb_load_reg_num =
				    iga2_crtc_reg.ver_blank_end.reg_num;
				reg = iga2_crtc_reg.ver_blank_end.reg;
				break;
			case V_SYNC_START_INDEX:
				reg_value =
				    IGA2_VER_SYNC_START_FORMULA
				    (device_timing.ver_sync_start);
				viafb_load_reg_num =
				    iga2_crtc_reg.ver_sync_start.reg_num;
				reg = iga2_crtc_reg.ver_sync_start.reg;
				break;
			case V_SYNC_END_INDEX:
				reg_value =
				    IGA2_VER_SYNC_END_FORMULA
				    (device_timing.ver_sync_start,
				     device_timing.ver_sync_end);
				viafb_load_reg_num =
				    iga2_crtc_reg.ver_sync_end.reg_num;
				reg = iga2_crtc_reg.ver_sync_end.reg;
				break;

			}
		}
		viafb_load_reg(reg_value, viafb_load_reg_num, reg, VIACR);
	}

	viafb_lock_crt();
}