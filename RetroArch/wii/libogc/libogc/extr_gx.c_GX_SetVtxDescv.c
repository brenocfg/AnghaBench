#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_5__ {int dirtyState; } ;
struct TYPE_4__ {scalar_t__ attr; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ GXVtxDesc ;

/* Variables and functions */
 size_t GX_MAX_VTXDESC_LISTSIZE ; 
 scalar_t__ GX_VA_NULL ; 
 int /*<<< orphan*/  __SETVCDATTR (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__* __gx ; 

void GX_SetVtxDescv(GXVtxDesc *attr_list)
{
	u32 i;

	if(!attr_list) return;

	for(i=0;i<GX_MAX_VTXDESC_LISTSIZE;i++){
		if(attr_list[i].attr==GX_VA_NULL) break;

		__SETVCDATTR(attr_list[i].attr,attr_list[i].type);
	}
	__gx->dirtyState |= 0x0008;
}