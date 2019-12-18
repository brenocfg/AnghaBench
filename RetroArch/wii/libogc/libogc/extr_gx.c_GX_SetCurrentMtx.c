#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int mtxIdxLo; int dirtyState; } ;

/* Variables and functions */
 TYPE_1__* __gx ; 

void GX_SetCurrentMtx(u32 mtx)
{
	__gx->mtxIdxLo = (__gx->mtxIdxLo&~0x3f)|(mtx&0x3f);
	__gx->dirtyState |= 0x04000000;
}