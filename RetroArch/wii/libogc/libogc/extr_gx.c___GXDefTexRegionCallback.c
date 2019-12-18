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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * texRegion; } ;
typedef  int /*<<< orphan*/  GXTexRegion ;
typedef  int /*<<< orphan*/  GXTexObj ;

/* Variables and functions */
 int GX_GetTexObjFmt (int /*<<< orphan*/ *) ; 
 TYPE_1__* __gx ; 

__attribute__((used)) static GXTexRegion* __GXDefTexRegionCallback(GXTexObj *obj,u8 mapid)
{
	u32 fmt;
	u32 idx;
	static u32 regionA = 0;
	static u32 regionB = 0;
	GXTexRegion *ret = NULL;

	fmt = GX_GetTexObjFmt(obj);
	if(fmt==0x0008 || fmt==0x0009 || fmt==0x000a) {
		idx = regionB++;
		ret = &__gx->texRegion[(idx&3)+8];
	} else {
		idx = regionA++;
		ret = &__gx->texRegion[(idx&7)];
	}
	return ret;
}