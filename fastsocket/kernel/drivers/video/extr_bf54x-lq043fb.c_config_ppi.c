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
typedef  int /*<<< orphan*/  u16 ;
struct bfin_bf54xfb_info {int dummy; } ;

/* Variables and functions */
 int DLENGTH ; 
 int DLEN_18 ; 
 int DLEN_24 ; 
 int /*<<< orphan*/  EPPI_CLIP ; 
 int EPPI_CONTROL ; 
 int /*<<< orphan*/  EPPI_FRAME ; 
 int /*<<< orphan*/  EPPI_FS1P_AVPL ; 
 int /*<<< orphan*/  EPPI_FS1W_HBL ; 
 int /*<<< orphan*/  EPPI_FS2P_LAVF ; 
 int /*<<< orphan*/  EPPI_FS2W_LVB ; 
 int /*<<< orphan*/  EPPI_HCOUNT ; 
 int /*<<< orphan*/  EPPI_HDELAY ; 
 int /*<<< orphan*/  EPPI_LINE ; 
 int /*<<< orphan*/  EPPI_VCOUNT ; 
 int /*<<< orphan*/  EPPI_VDELAY ; 
 int /*<<< orphan*/  LCD_CLK ; 
 int RGB_FMT_EN ; 
 int /*<<< orphan*/  bfin_write_EPPI0_CLIP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_EPPI0_CLKDIV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_EPPI0_CONTROL (int) ; 
 int /*<<< orphan*/  bfin_write_EPPI0_FRAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_EPPI0_FS1P_AVPL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_EPPI0_FS1W_HBL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_EPPI0_FS2P_LAVF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_EPPI0_FS2W_LVB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_EPPI0_HCOUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_EPPI0_HDELAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_EPPI0_LINE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_EPPI0_VCOUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_EPPI0_VDELAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_eppi_clkdiv (int /*<<< orphan*/ ) ; 
 scalar_t__ outp_rgb666 ; 

__attribute__((used)) static void config_ppi(struct bfin_bf54xfb_info *fbi)
{

	u16 eppi_clkdiv = get_eppi_clkdiv(LCD_CLK);

	bfin_write_EPPI0_FS1W_HBL(EPPI_FS1W_HBL);
	bfin_write_EPPI0_FS1P_AVPL(EPPI_FS1P_AVPL);
	bfin_write_EPPI0_FS2W_LVB(EPPI_FS2W_LVB);
	bfin_write_EPPI0_FS2P_LAVF(EPPI_FS2P_LAVF);
	bfin_write_EPPI0_CLIP(EPPI_CLIP);

	bfin_write_EPPI0_FRAME(EPPI_FRAME);
	bfin_write_EPPI0_LINE(EPPI_LINE);

	bfin_write_EPPI0_HCOUNT(EPPI_HCOUNT);
	bfin_write_EPPI0_HDELAY(EPPI_HDELAY);
	bfin_write_EPPI0_VCOUNT(EPPI_VCOUNT);
	bfin_write_EPPI0_VDELAY(EPPI_VDELAY);

	bfin_write_EPPI0_CLKDIV(eppi_clkdiv);

/*
 * DLEN = 6 (24 bits for RGB888 out) or 5 (18 bits for RGB666 out)
 * RGB Formatting Enabled for RGB666 output, disabled for RGB888 output
 */
	if (outp_rgb666)
		bfin_write_EPPI0_CONTROL((EPPI_CONTROL & ~DLENGTH) | DLEN_18 |
					 RGB_FMT_EN);
	else
		bfin_write_EPPI0_CONTROL(((EPPI_CONTROL & ~DLENGTH) | DLEN_24) &
					 ~RGB_FMT_EN);


}