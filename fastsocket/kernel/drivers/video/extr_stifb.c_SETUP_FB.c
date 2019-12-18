#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int bits_per_pixel; } ;
struct TYPE_3__ {TYPE_2__ var; } ;
struct stifb_info {int id; TYPE_1__ info; } ;

/* Variables and functions */
#define  CRT_ID_VISUALIZE_EG 134 
#define  CRX24_OVERLAY_PLANES 133 
 int /*<<< orphan*/  REG_10 ; 
 int /*<<< orphan*/  REG_14 ; 
 int /*<<< orphan*/  REG_16b1 ; 
#define  S9000_ID_A1439A 132 
#define  S9000_ID_A1659A 131 
#define  S9000_ID_ARTIST 130 
#define  S9000_ID_HCRX 129 
#define  S9000_ID_TIMBER 128 
 int /*<<< orphan*/  SETUP_HW (struct stifb_info*) ; 
 int /*<<< orphan*/  WRITE_BYTE (int,struct stifb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_WORD (int,struct stifb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
SETUP_FB(struct stifb_info *fb)
{	
	unsigned int reg10_value = 0;
	
	SETUP_HW(fb);
	switch (fb->id)
	{
		case CRT_ID_VISUALIZE_EG:
		case S9000_ID_ARTIST:
		case S9000_ID_A1659A:
			reg10_value = 0x13601000;
			break;
		case S9000_ID_A1439A:
			if (fb->info.var.bits_per_pixel == 32)						
				reg10_value = 0xBBA0A000;
			else 
				reg10_value = 0x13601000;
			break;
		case S9000_ID_HCRX:
			if (fb->info.var.bits_per_pixel == 32)
				reg10_value = 0xBBA0A000;
			else					
				reg10_value = 0x13602000;
			break;
		case S9000_ID_TIMBER:
		case CRX24_OVERLAY_PLANES:
			reg10_value = 0x13602000;
			break;
	}
	if (reg10_value)
		WRITE_WORD(reg10_value, fb, REG_10);
	WRITE_WORD(0x83000300, fb, REG_14);
	SETUP_HW(fb);
	WRITE_BYTE(1, fb, REG_16b1);
}