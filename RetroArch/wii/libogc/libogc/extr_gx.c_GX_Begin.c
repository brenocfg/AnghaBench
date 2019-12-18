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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {scalar_t__ dirtyState; } ;
struct TYPE_3__ {int U8; int /*<<< orphan*/  U16; } ;

/* Variables and functions */
 int /*<<< orphan*/  __GX_SetDirtyState () ; 
 TYPE_2__* __gx ; 
 TYPE_1__* wgPipe ; 

void GX_Begin(u8 primitve,u8 vtxfmt,u16 vtxcnt)
{
	u8 reg = primitve|(vtxfmt&7);

	if(__gx->dirtyState)
		__GX_SetDirtyState();

	wgPipe->U8 = reg;
	wgPipe->U16 = vtxcnt;
}