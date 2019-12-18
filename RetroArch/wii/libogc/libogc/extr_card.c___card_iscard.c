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
 int EXI_MEMCARD1019 ; 
 int EXI_MEMCARD123 ; 
 int EXI_MEMCARD2043 ; 
 int EXI_MEMCARD251 ; 
 int EXI_MEMCARD507 ; 
 int EXI_MEMCARD59 ; 
 int _ROTL (int,int) ; 
 int* card_sector_size ; 

__attribute__((used)) static u32 __card_iscard(u32 id)
{
	u32 ret;
	u32 idx,tmp,secsize;

	if(id&~0xffff) return 0;
	if(id&0x03) return 0;

	ret = 0;
	tmp = id&0xfc;
	if(tmp==EXI_MEMCARD59 || tmp==EXI_MEMCARD123
		|| tmp==EXI_MEMCARD251 || tmp==EXI_MEMCARD507
		|| tmp==EXI_MEMCARD1019 || tmp==EXI_MEMCARD2043) {
		idx = _ROTL(id,23)&0x1c;
		if((secsize=card_sector_size[idx>>2])==0) return 0;
		tmp = ((tmp<<20)&0x1FFE0000)/secsize;
		if(tmp>8) ret = 1;
	}
	return ret;
}