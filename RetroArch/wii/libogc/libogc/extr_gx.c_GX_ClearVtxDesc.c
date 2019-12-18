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
struct TYPE_2__ {int vcdClear; int dirtyState; scalar_t__ vcdHi; scalar_t__ vcdLo; scalar_t__ vcdNrms; } ;

/* Variables and functions */
 TYPE_1__* __gx ; 

void GX_ClearVtxDesc()
{
	__gx->vcdNrms = 0;
	__gx->vcdClear = ((__gx->vcdClear&~0x0600)|0x0200);
	__gx->vcdLo = __gx->vcdHi = 0;
	__gx->dirtyState |= 0x0008;
}