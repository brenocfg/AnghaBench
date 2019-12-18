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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static u32 __GX_GetNumXfbLines(u16 efbHeight,u32 yscale)
{
	u32 tmp,tmp1;

	tmp = (((efbHeight-1)<<8)/yscale)+1;
	if(yscale>128 && yscale<256) {
		while(yscale&0x01) yscale >>= 1;
		tmp1 = yscale*(efbHeight/yscale);
		if(!(efbHeight-tmp1)) tmp++;
	}
	if(tmp>1024) tmp = 1024;

	return tmp;
}