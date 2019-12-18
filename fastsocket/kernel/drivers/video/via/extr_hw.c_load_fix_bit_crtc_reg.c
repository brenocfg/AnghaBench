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
struct TYPE_4__ {TYPE_1__* chip_info; } ;
struct TYPE_3__ {scalar_t__ gfx_chip_name; scalar_t__ gfx_chip_revision; } ;

/* Variables and functions */
 scalar_t__ BIT0 ; 
 scalar_t__ BIT1 ; 
 scalar_t__ BIT2 ; 
 scalar_t__ BIT3 ; 
 scalar_t__ BIT4 ; 
 scalar_t__ BIT6 ; 
 scalar_t__ BIT7 ; 
 scalar_t__ CLE266_REVISION_AX ; 
 int /*<<< orphan*/  CR03 ; 
 int /*<<< orphan*/  CR07 ; 
 int /*<<< orphan*/  CR08 ; 
 int /*<<< orphan*/  CR09 ; 
 int /*<<< orphan*/  CR14 ; 
 int /*<<< orphan*/  CR17 ; 
 int /*<<< orphan*/  CR18 ; 
 int /*<<< orphan*/  CR33 ; 
 int /*<<< orphan*/  CR35 ; 
 int /*<<< orphan*/  SR1A ; 
 scalar_t__ UNICHROME_CLE266 ; 
 scalar_t__ UNICHROME_K800 ; 
 scalar_t__ UNICHROME_K8M890 ; 
 int /*<<< orphan*/  VIACR ; 
 int /*<<< orphan*/  VIASR ; 
 int /*<<< orphan*/  viafb_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  viafb_write_reg_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 TYPE_2__* viaparinfo ; 

__attribute__((used)) static void load_fix_bit_crtc_reg(void)
{
	/* always set to 1 */
	viafb_write_reg_mask(CR03, VIACR, 0x80, BIT7);
	/* line compare should set all bits = 1 (extend modes) */
	viafb_write_reg(CR18, VIACR, 0xff);
	/* line compare should set all bits = 1 (extend modes) */
	viafb_write_reg_mask(CR07, VIACR, 0x10, BIT4);
	/* line compare should set all bits = 1 (extend modes) */
	viafb_write_reg_mask(CR09, VIACR, 0x40, BIT6);
	/* line compare should set all bits = 1 (extend modes) */
	viafb_write_reg_mask(CR35, VIACR, 0x10, BIT4);
	/* line compare should set all bits = 1 (extend modes) */
	viafb_write_reg_mask(CR33, VIACR, 0x06, BIT0 + BIT1 + BIT2);
	/*viafb_write_reg_mask(CR32, VIACR, 0x01, BIT0); */
	/* extend mode always set to e3h */
	viafb_write_reg(CR17, VIACR, 0xe3);
	/* extend mode always set to 0h */
	viafb_write_reg(CR08, VIACR, 0x00);
	/* extend mode always set to 0h */
	viafb_write_reg(CR14, VIACR, 0x00);

	/* If K8M800, enable Prefetch Mode. */
	if ((viaparinfo->chip_info->gfx_chip_name == UNICHROME_K800)
		|| (viaparinfo->chip_info->gfx_chip_name == UNICHROME_K8M890))
		viafb_write_reg_mask(CR33, VIACR, 0x08, BIT3);
	if ((viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266)
	    && (viaparinfo->chip_info->gfx_chip_revision == CLE266_REVISION_AX))
		viafb_write_reg_mask(SR1A, VIASR, 0x02, BIT1);

}