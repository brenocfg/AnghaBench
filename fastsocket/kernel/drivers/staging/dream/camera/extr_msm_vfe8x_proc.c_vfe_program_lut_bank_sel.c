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
typedef  int /*<<< orphan*/  uint32_t ;
struct vfe_gamma_lut_sel {int /*<<< orphan*/  ch2BankSelect; int /*<<< orphan*/  ch1BankSelect; int /*<<< orphan*/  ch0BankSelect; } ;
struct VFE_GammaLutSelect_ConfigCmdType {int /*<<< orphan*/  ch2BankSelect; int /*<<< orphan*/  ch1BankSelect; int /*<<< orphan*/  ch0BankSelect; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ VFE_LUT_BANK_SEL ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  memset (struct VFE_GammaLutSelect_ConfigCmdType*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void vfe_program_lut_bank_sel(struct vfe_gamma_lut_sel *in)
{
	struct VFE_GammaLutSelect_ConfigCmdType cmd;

	memset(&cmd, 0, sizeof(cmd));

	cmd.ch0BankSelect = in->ch0BankSelect;
	cmd.ch1BankSelect = in->ch1BankSelect;
	cmd.ch2BankSelect = in->ch2BankSelect;
	CDBG("VFE gamma lut bank selection is 0x%x\n", *((uint32_t *)&cmd));
	vfe_prog_hw(ctrl->vfebase + VFE_LUT_BANK_SEL,
		(uint32_t *)&cmd, sizeof(cmd));
}