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
struct io_reg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT1 ; 
 int BIT2 ; 
 int BIT3 ; 
 int /*<<< orphan*/  BIT7 ; 
 int /*<<< orphan*/  CR17 ; 
 struct io_reg* K400_LCD_RES_10X7_12X10 ; 
 struct io_reg* K400_LCD_RES_10X7_1366X7 ; 
 struct io_reg* K400_LCD_RES_10X7_14X10 ; 
 struct io_reg* K400_LCD_RES_10X7_16X12 ; 
 struct io_reg* K400_LCD_RES_12X10_1366X7 ; 
 struct io_reg* K400_LCD_RES_12X10_14X10 ; 
 struct io_reg* K400_LCD_RES_12X10_16X12 ; 
 struct io_reg* K400_LCD_RES_6X4_10X7 ; 
 struct io_reg* K400_LCD_RES_6X4_12X10 ; 
 struct io_reg* K400_LCD_RES_6X4_1366X7 ; 
 struct io_reg* K400_LCD_RES_6X4_14X10 ; 
 struct io_reg* K400_LCD_RES_6X4_16X12 ; 
 struct io_reg* K400_LCD_RES_6X4_8X6 ; 
 struct io_reg* K400_LCD_RES_7X4_10X7 ; 
 struct io_reg* K400_LCD_RES_7X4_12X10 ; 
 struct io_reg* K400_LCD_RES_7X4_1366X7 ; 
 struct io_reg* K400_LCD_RES_7X4_16X12 ; 
 struct io_reg* K400_LCD_RES_7X4_8X6 ; 
 struct io_reg* K400_LCD_RES_8X6_10X7 ; 
 struct io_reg* K400_LCD_RES_8X6_12X10 ; 
 struct io_reg* K400_LCD_RES_8X6_1366X7 ; 
 struct io_reg* K400_LCD_RES_8X6_14X10 ; 
 struct io_reg* K400_LCD_RES_8X6_16X12 ; 
#define  LCD_PANEL_ID1_800X600 144 
#define  LCD_PANEL_ID2_1024X768 143 
#define  LCD_PANEL_ID4_1280X1024 142 
#define  LCD_PANEL_ID5_1400X1050 141 
#define  LCD_PANEL_ID6_1600X1200 140 
#define  LCD_PANEL_ID7_1366X768 139 
#define  LCD_PANEL_IDB_1360X768 138 
 int NUM_TOTAL_K400_LCD_RES_10X7_12X10 ; 
 int NUM_TOTAL_K400_LCD_RES_10X7_1366X7 ; 
 int NUM_TOTAL_K400_LCD_RES_10X7_14X10 ; 
 int NUM_TOTAL_K400_LCD_RES_10X7_16X12 ; 
 int NUM_TOTAL_K400_LCD_RES_12X10_1366X7 ; 
 int NUM_TOTAL_K400_LCD_RES_12X10_14X10 ; 
 int NUM_TOTAL_K400_LCD_RES_12X10_16X12 ; 
 int NUM_TOTAL_K400_LCD_RES_6X4_10X7 ; 
 int NUM_TOTAL_K400_LCD_RES_6X4_12X10 ; 
 int NUM_TOTAL_K400_LCD_RES_6X4_1366X7 ; 
 int NUM_TOTAL_K400_LCD_RES_6X4_14X10 ; 
 int NUM_TOTAL_K400_LCD_RES_6X4_16X12 ; 
 int NUM_TOTAL_K400_LCD_RES_6X4_8X6 ; 
 int NUM_TOTAL_K400_LCD_RES_7X4_10X7 ; 
 int NUM_TOTAL_K400_LCD_RES_7X4_12X10 ; 
 int NUM_TOTAL_K400_LCD_RES_7X4_1366X7 ; 
 int NUM_TOTAL_K400_LCD_RES_7X4_16X12 ; 
 int NUM_TOTAL_K400_LCD_RES_7X4_8X6 ; 
 int NUM_TOTAL_K400_LCD_RES_8X6_10X7 ; 
 int NUM_TOTAL_K400_LCD_RES_8X6_12X10 ; 
 int NUM_TOTAL_K400_LCD_RES_8X6_1366X7 ; 
 int NUM_TOTAL_K400_LCD_RES_8X6_14X10 ; 
 int NUM_TOTAL_K400_LCD_RES_8X6_16X12 ; 
 int /*<<< orphan*/  SR40 ; 
 int /*<<< orphan*/  VIACR ; 
 int /*<<< orphan*/  VIARMisc ; 
 int /*<<< orphan*/  VIASR ; 
 int /*<<< orphan*/  VIAWMisc ; 
#define  VIA_RES_1024X768 137 
#define  VIA_RES_1280X1024 136 
#define  VIA_RES_1280X768 135 
#define  VIA_RES_1280X800 134 
#define  VIA_RES_1280X960 133 
#define  VIA_RES_640X400 132 
#define  VIA_RES_640X480 131 
#define  VIA_RES_720X480 130 
#define  VIA_RES_720X576 129 
#define  VIA_RES_800X600 128 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int viafb_get_mode_index (int,int) ; 
 int /*<<< orphan*/  viafb_write_reg_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viafb_write_regx (struct io_reg*,int) ; 

__attribute__((used)) static void load_lcd_k400_patch_tbl(int set_hres, int set_vres,
	int panel_id)
{
	int vmode_index;
	int reg_num = 0;
	struct io_reg *lcd_patch_reg = NULL;

	vmode_index = viafb_get_mode_index(set_hres, set_vres);
	switch (panel_id) {
		/* LCD 800x600 */
	case LCD_PANEL_ID1_800X600:
		switch (vmode_index) {
		case VIA_RES_640X400:
		case VIA_RES_640X480:
			reg_num = NUM_TOTAL_K400_LCD_RES_6X4_8X6;
			lcd_patch_reg = K400_LCD_RES_6X4_8X6;
			break;
		case VIA_RES_720X480:
		case VIA_RES_720X576:
			reg_num = NUM_TOTAL_K400_LCD_RES_7X4_8X6;
			lcd_patch_reg = K400_LCD_RES_7X4_8X6;
			break;
		}
		break;

		/* LCD 1024x768 */
	case LCD_PANEL_ID2_1024X768:
		switch (vmode_index) {
		case VIA_RES_640X400:
		case VIA_RES_640X480:
			reg_num = NUM_TOTAL_K400_LCD_RES_6X4_10X7;
			lcd_patch_reg = K400_LCD_RES_6X4_10X7;
			break;
		case VIA_RES_720X480:
		case VIA_RES_720X576:
			reg_num = NUM_TOTAL_K400_LCD_RES_7X4_10X7;
			lcd_patch_reg = K400_LCD_RES_7X4_10X7;
			break;
		case VIA_RES_800X600:
			reg_num = NUM_TOTAL_K400_LCD_RES_8X6_10X7;
			lcd_patch_reg = K400_LCD_RES_8X6_10X7;
			break;
		}
		break;

		/* LCD 1280x1024 */
	case LCD_PANEL_ID4_1280X1024:
		switch (vmode_index) {
		case VIA_RES_640X400:
		case VIA_RES_640X480:
			reg_num = NUM_TOTAL_K400_LCD_RES_6X4_12X10;
			lcd_patch_reg = K400_LCD_RES_6X4_12X10;
			break;
		case VIA_RES_720X480:
		case VIA_RES_720X576:
			reg_num = NUM_TOTAL_K400_LCD_RES_7X4_12X10;
			lcd_patch_reg = K400_LCD_RES_7X4_12X10;
			break;
		case VIA_RES_800X600:
			reg_num = NUM_TOTAL_K400_LCD_RES_8X6_12X10;
			lcd_patch_reg = K400_LCD_RES_8X6_12X10;
			break;
		case VIA_RES_1024X768:
			reg_num = NUM_TOTAL_K400_LCD_RES_10X7_12X10;
			lcd_patch_reg = K400_LCD_RES_10X7_12X10;
			break;

		}
		break;

		/* LCD 1400x1050 */
	case LCD_PANEL_ID5_1400X1050:
		switch (vmode_index) {
		case VIA_RES_640X480:
			reg_num = NUM_TOTAL_K400_LCD_RES_6X4_14X10;
			lcd_patch_reg = K400_LCD_RES_6X4_14X10;
			break;
		case VIA_RES_800X600:
			reg_num = NUM_TOTAL_K400_LCD_RES_8X6_14X10;
			lcd_patch_reg = K400_LCD_RES_8X6_14X10;
			break;
		case VIA_RES_1024X768:
			reg_num = NUM_TOTAL_K400_LCD_RES_10X7_14X10;
			lcd_patch_reg = K400_LCD_RES_10X7_14X10;
			break;
		case VIA_RES_1280X768:
		case VIA_RES_1280X800:
		case VIA_RES_1280X960:
		case VIA_RES_1280X1024:
			reg_num = NUM_TOTAL_K400_LCD_RES_12X10_14X10;
			lcd_patch_reg = K400_LCD_RES_12X10_14X10;
			break;
		}
		break;

		/* LCD 1600x1200 */
	case LCD_PANEL_ID6_1600X1200:
		switch (vmode_index) {
		case VIA_RES_640X400:
		case VIA_RES_640X480:
			reg_num = NUM_TOTAL_K400_LCD_RES_6X4_16X12;
			lcd_patch_reg = K400_LCD_RES_6X4_16X12;
			break;
		case VIA_RES_720X480:
		case VIA_RES_720X576:
			reg_num = NUM_TOTAL_K400_LCD_RES_7X4_16X12;
			lcd_patch_reg = K400_LCD_RES_7X4_16X12;
			break;
		case VIA_RES_800X600:
			reg_num = NUM_TOTAL_K400_LCD_RES_8X6_16X12;
			lcd_patch_reg = K400_LCD_RES_8X6_16X12;
			break;
		case VIA_RES_1024X768:
			reg_num = NUM_TOTAL_K400_LCD_RES_10X7_16X12;
			lcd_patch_reg = K400_LCD_RES_10X7_16X12;
			break;
		case VIA_RES_1280X768:
		case VIA_RES_1280X800:
		case VIA_RES_1280X960:
		case VIA_RES_1280X1024:
			reg_num = NUM_TOTAL_K400_LCD_RES_12X10_16X12;
			lcd_patch_reg = K400_LCD_RES_12X10_16X12;
			break;
		}
		break;

		/* LCD 1366x768 */
	case LCD_PANEL_ID7_1366X768:
		switch (vmode_index) {
		case VIA_RES_640X480:
			reg_num = NUM_TOTAL_K400_LCD_RES_6X4_1366X7;
			lcd_patch_reg = K400_LCD_RES_6X4_1366X7;
			break;
		case VIA_RES_720X480:
		case VIA_RES_720X576:
			reg_num = NUM_TOTAL_K400_LCD_RES_7X4_1366X7;
			lcd_patch_reg = K400_LCD_RES_7X4_1366X7;
			break;
		case VIA_RES_800X600:
			reg_num = NUM_TOTAL_K400_LCD_RES_8X6_1366X7;
			lcd_patch_reg = K400_LCD_RES_8X6_1366X7;
			break;
		case VIA_RES_1024X768:
			reg_num = NUM_TOTAL_K400_LCD_RES_10X7_1366X7;
			lcd_patch_reg = K400_LCD_RES_10X7_1366X7;
			break;
		case VIA_RES_1280X768:
		case VIA_RES_1280X800:
		case VIA_RES_1280X960:
		case VIA_RES_1280X1024:
			reg_num = NUM_TOTAL_K400_LCD_RES_12X10_1366X7;
			lcd_patch_reg = K400_LCD_RES_12X10_1366X7;
			break;
		}
		break;

		/* LCD 1360x768 */
	case LCD_PANEL_IDB_1360X768:
		break;
	}
	if (reg_num != 0) {
		/* H.W. Reset : ON */
		viafb_write_reg_mask(CR17, VIACR, 0x00, BIT7);

		viafb_write_regx(lcd_patch_reg, reg_num);

		/* H.W. Reset : OFF */
		viafb_write_reg_mask(CR17, VIACR, 0x80, BIT7);

		/* Reset PLL */
		viafb_write_reg_mask(SR40, VIASR, 0x02, BIT1);
		viafb_write_reg_mask(SR40, VIASR, 0x00, BIT1);

		/* Fire! */
		outb(inb(VIARMisc) | (BIT2 + BIT3), VIAWMisc);
	}
}