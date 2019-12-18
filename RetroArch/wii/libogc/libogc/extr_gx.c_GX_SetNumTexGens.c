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
struct TYPE_2__ {int genMode; int dirtyState; } ;

/* Variables and functions */
 TYPE_1__* __gx ; 

void GX_SetNumTexGens(u32 nr)
{
	__gx->genMode = (__gx->genMode&~0xf)|(nr&0xf);
	__gx->dirtyState |= 0x02000004;
}