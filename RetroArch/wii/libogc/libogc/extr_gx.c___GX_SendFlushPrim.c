#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int xfFlush; int xfFlushExp; } ;
struct TYPE_3__ {int U8; int U16; scalar_t__ U32; } ;

/* Variables and functions */
 TYPE_2__* __gx ; 
 TYPE_1__* wgPipe ; 

__attribute__((used)) static void __GX_SendFlushPrim()
{
	u32 tmp,tmp2,cnt;

	tmp = (__gx->xfFlush*__gx->xfFlushExp);

	wgPipe->U8 = 0x98;
	wgPipe->U16 = __gx->xfFlush;

	tmp2 = (tmp+3)/4;
	if(tmp>0) {
		cnt = tmp2/8;
		while(cnt) {
			wgPipe->U32 = 0;
					wgPipe->U32 = 0;
					wgPipe->U32 = 0;
					wgPipe->U32 = 0;
					wgPipe->U32 = 0;
					wgPipe->U32 = 0;
					wgPipe->U32 = 0;
					wgPipe->U32 = 0;
					cnt--;
		}
		tmp2 &= 0x0007;
		if(tmp2) {
			while(tmp2) {
				wgPipe->U32 = 0;
							tmp2--;
			}
		}
	}
	__gx->xfFlush = 1;
}