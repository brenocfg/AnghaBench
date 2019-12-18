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
 int END_ROW ; 
 int LINE_WIDTH ; 
 scalar_t__ PicoDraw2FB ; 
 int START_ROW ; 
 int /*<<< orphan*/  memset32 (int*,unsigned int,int) ; 

__attribute__((used)) static void BackFillFull(int reg7)
{
	unsigned int back;

	// Start with a background color:
//	back=PicoCramHigh[reg7&0x3f];
	back=reg7&0x3f;
	back|=back<<8;
	back|=back<<16;

	memset32((int *)PicoDraw2FB, back, LINE_WIDTH*(8+(END_ROW-START_ROW)*8)/4);
}