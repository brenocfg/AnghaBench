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
struct nvidia_par {scalar_t__ Architecture; int Chipset; unsigned int CrystalFreqKHz; int /*<<< orphan*/  PRAMDAC0; scalar_t__ twoStagePLL; int /*<<< orphan*/  PMC; } ;

/* Variables and functions */
 scalar_t__ NV_ARCH_40 ; 
 unsigned int NV_RD32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nvGetClocks(struct nvidia_par *par, unsigned int *MClk,
			unsigned int *NVClk)
{
	unsigned int pll, N, M, MB, NB, P;

	if (par->Architecture >= NV_ARCH_40) {
		pll = NV_RD32(par->PMC, 0x4020);
		P = (pll >> 16) & 0x07;
		pll = NV_RD32(par->PMC, 0x4024);
		M = pll & 0xFF;
		N = (pll >> 8) & 0xFF;
		if (((par->Chipset & 0xfff0) == 0x0290) ||
		    ((par->Chipset & 0xfff0) == 0x0390)) {
			MB = 1;
			NB = 1;
		} else {
			MB = (pll >> 16) & 0xFF;
			NB = (pll >> 24) & 0xFF;
		}
		*MClk = ((N * NB * par->CrystalFreqKHz) / (M * MB)) >> P;

		pll = NV_RD32(par->PMC, 0x4000);
		P = (pll >> 16) & 0x07;
		pll = NV_RD32(par->PMC, 0x4004);
		M = pll & 0xFF;
		N = (pll >> 8) & 0xFF;
		MB = (pll >> 16) & 0xFF;
		NB = (pll >> 24) & 0xFF;

		*NVClk = ((N * NB * par->CrystalFreqKHz) / (M * MB)) >> P;
	} else if (par->twoStagePLL) {
		pll = NV_RD32(par->PRAMDAC0, 0x0504);
		M = pll & 0xFF;
		N = (pll >> 8) & 0xFF;
		P = (pll >> 16) & 0x0F;
		pll = NV_RD32(par->PRAMDAC0, 0x0574);
		if (pll & 0x80000000) {
			MB = pll & 0xFF;
			NB = (pll >> 8) & 0xFF;
		} else {
			MB = 1;
			NB = 1;
		}
		*MClk = ((N * NB * par->CrystalFreqKHz) / (M * MB)) >> P;

		pll = NV_RD32(par->PRAMDAC0, 0x0500);
		M = pll & 0xFF;
		N = (pll >> 8) & 0xFF;
		P = (pll >> 16) & 0x0F;
		pll = NV_RD32(par->PRAMDAC0, 0x0570);
		if (pll & 0x80000000) {
			MB = pll & 0xFF;
			NB = (pll >> 8) & 0xFF;
		} else {
			MB = 1;
			NB = 1;
		}
		*NVClk = ((N * NB * par->CrystalFreqKHz) / (M * MB)) >> P;
	} else
	    if (((par->Chipset & 0x0ff0) == 0x0300) ||
		((par->Chipset & 0x0ff0) == 0x0330)) {
		pll = NV_RD32(par->PRAMDAC0, 0x0504);
		M = pll & 0x0F;
		N = (pll >> 8) & 0xFF;
		P = (pll >> 16) & 0x07;
		if (pll & 0x00000080) {
			MB = (pll >> 4) & 0x07;
			NB = (pll >> 19) & 0x1f;
		} else {
			MB = 1;
			NB = 1;
		}
		*MClk = ((N * NB * par->CrystalFreqKHz) / (M * MB)) >> P;

		pll = NV_RD32(par->PRAMDAC0, 0x0500);
		M = pll & 0x0F;
		N = (pll >> 8) & 0xFF;
		P = (pll >> 16) & 0x07;
		if (pll & 0x00000080) {
			MB = (pll >> 4) & 0x07;
			NB = (pll >> 19) & 0x1f;
		} else {
			MB = 1;
			NB = 1;
		}
		*NVClk = ((N * NB * par->CrystalFreqKHz) / (M * MB)) >> P;
	} else {
		pll = NV_RD32(par->PRAMDAC0, 0x0504);
		M = pll & 0xFF;
		N = (pll >> 8) & 0xFF;
		P = (pll >> 16) & 0x0F;
		*MClk = (N * par->CrystalFreqKHz / M) >> P;

		pll = NV_RD32(par->PRAMDAC0, 0x0500);
		M = pll & 0xFF;
		N = (pll >> 8) & 0xFF;
		P = (pll >> 16) & 0x0F;
		*NVClk = (N * par->CrystalFreqKHz / M) >> P;
	}
}