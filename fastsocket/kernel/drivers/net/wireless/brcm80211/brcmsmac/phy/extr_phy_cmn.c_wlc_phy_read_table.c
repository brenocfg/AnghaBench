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
typedef  int uint ;
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct phytbl_info {int tbl_id; int tbl_offset; int tbl_width; int tbl_len; scalar_t__ tbl_ptr; } ;
struct brcms_phy {TYPE_1__* sh; } ;
struct TYPE_2__ {scalar_t__ chip; int chiprev; } ;

/* Variables and functions */
 scalar_t__ BCM43224_CHIP_ID ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

void
wlc_phy_read_table(struct brcms_phy *pi, const struct phytbl_info *ptbl_info,
		   u16 tblAddr, u16 tblDataHi, u16 tblDataLo)
{
	uint idx;
	uint tbl_id = ptbl_info->tbl_id;
	uint tbl_offset = ptbl_info->tbl_offset;
	uint tbl_width = ptbl_info->tbl_width;
	u8 *ptbl_8b = (u8 *)ptbl_info->tbl_ptr;
	u16 *ptbl_16b = (u16 *)ptbl_info->tbl_ptr;
	u32 *ptbl_32b = (u32 *)ptbl_info->tbl_ptr;

	write_phy_reg(pi, tblAddr, (tbl_id << 10) | tbl_offset);

	for (idx = 0; idx < ptbl_info->tbl_len; idx++) {

		if ((pi->sh->chip == BCM43224_CHIP_ID) &&
		    (pi->sh->chiprev == 1)) {
			(void)read_phy_reg(pi, tblDataLo);

			write_phy_reg(pi, tblAddr,
				      (tbl_id << 10) | (tbl_offset + idx));
		}

		if (tbl_width == 32) {
			ptbl_32b[idx] = read_phy_reg(pi, tblDataLo);
			ptbl_32b[idx] |= (read_phy_reg(pi, tblDataHi) << 16);
		} else if (tbl_width == 16) {
			ptbl_16b[idx] = read_phy_reg(pi, tblDataLo);
		} else {
			ptbl_8b[idx] = (u8) read_phy_reg(pi, tblDataLo);
		}
	}
}