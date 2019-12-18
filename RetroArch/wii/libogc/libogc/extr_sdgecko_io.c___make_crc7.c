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
typedef  int u8 ;
typedef  size_t u32 ;
typedef  size_t s32 ;

/* Variables and functions */
 int* _ioCrc7Table ; 

__attribute__((used)) static u8 __make_crc7(void *buffer,u32 len)
{
	s32 i;
	u8 crc7;
	u8 *ptr;

	crc7 = 0;
	ptr = buffer;
	for(i=0;i<len;i++)
		crc7 = _ioCrc7Table[(u8)((crc7<<1)^ptr[i])];

	return ((crc7<<1)|1);
}