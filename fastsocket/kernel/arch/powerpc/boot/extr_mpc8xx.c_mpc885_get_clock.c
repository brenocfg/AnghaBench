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
typedef  int u32 ;

/* Variables and functions */
 size_t MPC8XX_PLPRCR ; 
 int* fsl_get_immr () ; 
 int in_be32 (int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

u32 mpc885_get_clock(u32 crystal)
{
	u32 *immr;
	u32 plprcr;
	int mfi, mfn, mfd, pdf, div;
	u32 ret;

	immr = fsl_get_immr();
	if (!immr) {
		printf("mpc885_get_clock: Couldn't get IMMR base.\r\n");
		return 0;
	}

	plprcr = in_be32(&immr[MPC8XX_PLPRCR]);

	mfi = (plprcr >> 16) & 15;
	if (mfi < 5) {
		printf("Warning: PLPRCR[MFI] value of %d out-of-bounds\r\n",
		       mfi);
		mfi = 5;
	}

	pdf = (plprcr >> 1) & 0xf;
	div = (plprcr >> 20) & 3;
	mfd = (plprcr >> 22) & 0x1f;
	mfn = (plprcr >> 27) & 0x1f;

	ret = crystal * mfi;

	if (mfn != 0)
		ret += crystal * mfn / (mfd + 1);

	return ret / (pdf + 1);
}