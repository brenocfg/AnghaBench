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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  vcdClear; scalar_t__ dirtyState; } ;
struct TYPE_3__ {int U8; int /*<<< orphan*/  U32; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_VIRTUAL_TO_PHYSICAL (void*) ; 
 int /*<<< orphan*/  __GX_SendFlushPrim () ; 
 int /*<<< orphan*/  __GX_SetDirtyState () ; 
 TYPE_2__* __gx ; 
 TYPE_1__* wgPipe ; 

void GX_CallDispList(void *list,u32 nbytes)
{
	if(__gx->dirtyState)
		__GX_SetDirtyState();

	if(!__gx->vcdClear)
		__GX_SendFlushPrim();

	wgPipe->U8 = 0x40;		//call displaylist
	wgPipe->U32 = MEM_VIRTUAL_TO_PHYSICAL(list);
	wgPipe->U32 = nbytes;
}