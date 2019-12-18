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
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
typedef  int u16 ;
typedef  size_t s32 ;

/* Variables and functions */
 int* _ioCrc16Table ; 

__attribute__((used)) static u16 __make_crc16(void *buffer,u32 len)
{
	s32 i;
	u8 *ptr;
	u16 crc16;

	crc16 = 0;
	ptr = buffer;
	for(i=0;i<len;i++)
		crc16 = (crc16<<8)^_ioCrc16Table[((crc16>>8)^(u16)(ptr[i]))];

	return crc16;
}