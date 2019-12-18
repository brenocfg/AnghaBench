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
 int BIT6 ; 
 int BIT7 ; 
 int /*<<< orphan*/  CR67 ; 
 int IGA1 ; 
#define  MODE_16BPP 130 
#define  MODE_32BPP 129 
#define  MODE_8BPP 128 
 int /*<<< orphan*/  SR15 ; 
 int /*<<< orphan*/  VIACR ; 
 int /*<<< orphan*/  VIASR ; 
 int /*<<< orphan*/  viafb_write_reg_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void viafb_set_color_depth(int bpp_byte, int set_iga)
{
	if (set_iga == IGA1) {
		switch (bpp_byte) {
		case MODE_8BPP:
			viafb_write_reg_mask(SR15, VIASR, 0x22, 0x7E);
			break;
		case MODE_16BPP:
			viafb_write_reg_mask(SR15, VIASR, 0xB6, 0xFE);
			break;
		case MODE_32BPP:
			viafb_write_reg_mask(SR15, VIASR, 0xAE, 0xFE);
			break;
		}
	} else {
		switch (bpp_byte) {
		case MODE_8BPP:
			viafb_write_reg_mask(CR67, VIACR, 0x00, BIT6 + BIT7);
			break;
		case MODE_16BPP:
			viafb_write_reg_mask(CR67, VIACR, 0x40, BIT6 + BIT7);
			break;
		case MODE_32BPP:
			viafb_write_reg_mask(CR67, VIACR, 0xC0, BIT6 + BIT7);
			break;
		}
	}
}