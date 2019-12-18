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
typedef  int u16 ;
typedef  int s32 ;

/* Variables and functions */
 int* _ioCrc16Table ; 

__attribute__((used)) static void __init_crc16()
{
	s32 i,j;
	u16 crc16,c;

	for(i=0;i<256;i++) {
		crc16 = 0;
		c = ((u16)i)<<8;
		for(j=0;j<8;j++) {
			if((crc16^c)&0x8000) crc16 = (crc16<<1)^0x1021;
			else crc16 <<= 1;

			c <<= 1;
		}

		_ioCrc16Table[i] = crc16;
	}
}