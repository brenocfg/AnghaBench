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
 scalar_t__ BIT3 ; 
 scalar_t__ BIT4 ; 
 scalar_t__ BIT5 ; 
 scalar_t__ BIT6 ; 
 scalar_t__ BIT7 ; 
 int /*<<< orphan*/  CR36 ; 
 int /*<<< orphan*/  CR6A ; 
 int /*<<< orphan*/  CR6B ; 
#define  IGA1 130 
#define  IGA1_IGA2 129 
#define  IGA2 128 
 int /*<<< orphan*/  SR16 ; 
 int /*<<< orphan*/  VIACR ; 
 int /*<<< orphan*/  VIASR ; 
 int /*<<< orphan*/  viafb_write_reg_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static void set_crt_output_path(int set_iga)
{
	viafb_write_reg_mask(CR36, VIACR, 0x00, BIT4 + BIT5);

	switch (set_iga) {
	case IGA1:
		viafb_write_reg_mask(SR16, VIASR, 0x00, BIT6);
		break;
	case IGA2:
	case IGA1_IGA2:
		viafb_write_reg_mask(CR6A, VIACR, 0xC0, BIT6 + BIT7);
		viafb_write_reg_mask(SR16, VIASR, 0x40, BIT6);
		if (set_iga == IGA1_IGA2)
			viafb_write_reg_mask(CR6B, VIACR, 0x08, BIT3);
		break;
	}
}