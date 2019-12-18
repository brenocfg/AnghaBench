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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;

/* Variables and functions */

u16 rtl8180_len2duration(u32 len, short rate,short* ext)
{
	u16 duration;
	u16 drift;
	*ext=0;

	switch(rate){
	case 0://1mbps
		*ext=0;
		duration = ((len+4)<<4) /0x2;
		drift = ((len+4)<<4) % 0x2;
		if(drift ==0 ) break;
		duration++;
		break;
	case 1://2mbps
		*ext=0;
		duration = ((len+4)<<4) /0x4;
		drift = ((len+4)<<4) % 0x4;
		if(drift ==0 ) break;
		duration++;
		break;
	case 2: //5.5mbps
		*ext=0;
		duration = ((len+4)<<4) /0xb;
		drift = ((len+4)<<4) % 0xb;
		if(drift ==0 )
			break;
		duration++;
		break;
	default:
	case 3://11mbps
		*ext=0;
		duration = ((len+4)<<4) /0x16;
		drift = ((len+4)<<4) % 0x16;
		if(drift ==0 )
			break;
		duration++;
		if(drift > 6)
			break;
		*ext=1;
		break;
	}

	return duration;
}