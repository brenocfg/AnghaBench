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
struct TYPE_2__ {int dirtyState; int /*<<< orphan*/ * chnMatColor; int /*<<< orphan*/ * chnAmbColor; } ;

/* Variables and functions */
 int /*<<< orphan*/  GX_LOAD_XF_REG (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* __gx ; 

__attribute__((used)) static void __GX_SetChanColor()
{
	if(__gx->dirtyState&0x0100)
		GX_LOAD_XF_REG(0x100a,__gx->chnAmbColor[0]);
	if(__gx->dirtyState&0x0200)
		GX_LOAD_XF_REG(0x100b,__gx->chnAmbColor[1]);
	if(__gx->dirtyState&0x0400)
		GX_LOAD_XF_REG(0x100c,__gx->chnMatColor[0]);
	if(__gx->dirtyState&0x0800)
		GX_LOAD_XF_REG(0x100d,__gx->chnMatColor[1]);
}