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
 scalar_t__ PHILIPS1 ; 
 scalar_t__ PHILIPS2 ; 
 scalar_t__ decoder ; 
 int /*<<< orphan*/  pms_i2c_andor (int,int,int,int) ; 
 short standard ; 

__attribute__((used)) static void pms_format(short format)
{
	int target;
	standard = format;

	if(decoder==PHILIPS1)
		target=0x42;
	else if(decoder==PHILIPS2)
		target=0x8A;
	else
		return;

	switch(format)
	{
		case 0:	/* Auto */
			pms_i2c_andor(target, 0x0D, 0xFE,0x00);
			pms_i2c_andor(target, 0x0F, 0x3F,0x80);
			break;
		case 1: /* NTSC */
			pms_i2c_andor(target, 0x0D, 0xFE, 0x00);
			pms_i2c_andor(target, 0x0F, 0x3F, 0x40);
			break;
		case 2: /* PAL */
			pms_i2c_andor(target, 0x0D, 0xFE, 0x00);
			pms_i2c_andor(target, 0x0F, 0x3F, 0x00);
			break;
		case 3:	/* SECAM */
			pms_i2c_andor(target, 0x0D, 0xFE, 0x01);
			pms_i2c_andor(target, 0x0F, 0x3F, 0x00);
			break;
	}
}