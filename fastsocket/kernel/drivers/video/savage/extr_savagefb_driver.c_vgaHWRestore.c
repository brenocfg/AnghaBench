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
struct savagefb_par {int dummy; } ;
struct savage_reg {int* CRTC; int /*<<< orphan*/ * Attribute; int /*<<< orphan*/ * Graphics; int /*<<< orphan*/ * Sequencer; int /*<<< orphan*/  MiscOutReg; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGAdisablePalette (struct savagefb_par*) ; 
 int /*<<< orphan*/  VGAenablePalette (struct savagefb_par*) ; 
 int /*<<< orphan*/  VGAwATTR (int,int /*<<< orphan*/ ,struct savagefb_par*) ; 
 int /*<<< orphan*/  VGAwCR (int,int,struct savagefb_par*) ; 
 int /*<<< orphan*/  VGAwGR (int,int /*<<< orphan*/ ,struct savagefb_par*) ; 
 int /*<<< orphan*/  VGAwMISC (int /*<<< orphan*/ ,struct savagefb_par*) ; 
 int /*<<< orphan*/  VGAwSEQ (int,int /*<<< orphan*/ ,struct savagefb_par*) ; 

__attribute__((used)) static void vgaHWRestore(struct savagefb_par  *par, struct savage_reg *reg)
{
	int i;

	VGAwMISC(reg->MiscOutReg, par);

	for (i = 1; i < 5; i++)
		VGAwSEQ(i, reg->Sequencer[i], par);

	/* Ensure CRTC registers 0-7 are unlocked by clearing bit 7 or
	   CRTC[17] */
	VGAwCR(17, reg->CRTC[17] & ~0x80, par);

	for (i = 0; i < 25; i++)
		VGAwCR(i, reg->CRTC[i], par);

	for (i = 0; i < 9; i++)
		VGAwGR(i, reg->Graphics[i], par);

	VGAenablePalette(par);

	for (i = 0; i < 21; i++)
		VGAwATTR(i, reg->Attribute[i], par);

	VGAdisablePalette(par);
}