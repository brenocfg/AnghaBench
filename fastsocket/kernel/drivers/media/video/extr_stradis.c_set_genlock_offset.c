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
struct saa7146 {int dummy; } ;

/* Variables and functions */
 scalar_t__ CurrentMode ; 
 scalar_t__ VIDEO_MODE_PAL ; 
 int /*<<< orphan*/  XILINX_GLDELAY ; 
 int /*<<< orphan*/  debNormal ; 
 int /*<<< orphan*/  debiwrite (struct saa7146*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void set_genlock_offset(struct saa7146 *saa, int noffset)
{
	int nCode;
	int PixelsPerLine = 858;
	if (CurrentMode == VIDEO_MODE_PAL)
		PixelsPerLine = 864;
	if (noffset > 500)
		noffset = 500;
	else if (noffset < -500)
		noffset = -500;
	nCode = noffset + 0x100;
	if (nCode == 1)
		nCode = 0x401;
	else if (nCode < 1)
		nCode = 0x400 + PixelsPerLine + nCode;
	debiwrite(saa, debNormal, XILINX_GLDELAY, nCode, 2);
}