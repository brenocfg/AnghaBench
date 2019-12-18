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
 int MVVMEMORYWIDTH ; 
 int mvv_read (int) ; 
 int /*<<< orphan*/  mvv_write (int,int) ; 
 int /*<<< orphan*/  pms_horzdeci (short,int) ; 
 int /*<<< orphan*/  pms_vertdeci (int,int) ; 
 int standard ; 

__attribute__((used)) static void pms_resolution(short width, short height)
{
	int fg_height;

	fg_height=height;
	if(fg_height>280)
		fg_height=280;

	mvv_write(0x18, fg_height);
	mvv_write(0x19, fg_height>>8);

	if(standard==1)
	{
		mvv_write(0x1A, 0xFC);
		mvv_write(0x1B, 0x00);
		if(height>fg_height)
			pms_vertdeci(240,240);
		else
			pms_vertdeci(fg_height,240);
	}
	else
	{
		mvv_write(0x1A, 0x1A);
		mvv_write(0x1B, 0x01);
		if(fg_height>256)
			pms_vertdeci(270,270);
		else
			pms_vertdeci(fg_height, 270);
	}
	mvv_write(0x12,0);
	mvv_write(0x13, MVVMEMORYWIDTH);
	mvv_write(0x42, 0x00);
	mvv_write(0x43, 0x00);
	mvv_write(0x44, MVVMEMORYWIDTH);

	mvv_write(0x22, width+8);
	mvv_write(0x23, (width+8)>> 8);

	if(standard==1)
		pms_horzdeci(width,640);
	else
		pms_horzdeci(width+8, 768);

	mvv_write(0x30, mvv_read(0x30)&0xFE);
	mvv_write(0x08, mvv_read(0x08)|0x01);
	mvv_write(0x01, mvv_read(0x01)&0xFD);
	mvv_write(0x32, 0x00);
	mvv_write(0x33, MVVMEMORYWIDTH);
}