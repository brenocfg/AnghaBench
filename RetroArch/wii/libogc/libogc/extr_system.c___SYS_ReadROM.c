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
 scalar_t__ __read_rom (void*,int,int) ; 

void __SYS_ReadROM(void *buf,u32 len,u32 offset)
{
	u32 cpy_cnt;

	while(len>0) {
		cpy_cnt = (len>256)?256:len;
		while(__read_rom(buf,cpy_cnt,offset)==0);
		offset += cpy_cnt;
		buf += cpy_cnt;
		len -= cpy_cnt;
	}
}