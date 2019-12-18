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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int genMode; int dirtyState; } ;

/* Variables and functions */
 int _SHIFTL (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* __gx ; 

void GX_SetNumChans(u8 num)
{
	__gx->genMode = (__gx->genMode&~0x70)|(_SHIFTL(num,4,3));
	__gx->dirtyState |= 0x01000004;
}