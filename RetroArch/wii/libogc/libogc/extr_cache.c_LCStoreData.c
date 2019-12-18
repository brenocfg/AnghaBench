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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  LCStoreBlocks (void*,void*,int) ; 

u32 LCStoreData(void *dstAddr,void *srcAddr,u32 nCount)
{
	u32 cnt,blocks;

	if((s32)nCount<=0) return 0;

	cnt = (nCount+31)>>5;
	blocks = (cnt+127)>>7;
	while(cnt) {
		if(cnt<0x80) {
			LCStoreBlocks(dstAddr,srcAddr,cnt);
			cnt = 0;
			break;
		}
		LCStoreBlocks(dstAddr,srcAddr,0);
		cnt -= 128;
		dstAddr += 4096;
		srcAddr += 4096;
	}
	return blocks;
}