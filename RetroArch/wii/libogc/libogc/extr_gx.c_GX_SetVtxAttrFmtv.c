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
typedef  int u8 ;
typedef  size_t u32 ;
struct TYPE_5__ {int VATTable; int dirtyState; } ;
struct TYPE_4__ {scalar_t__ vtxattr; int /*<<< orphan*/  frac; int /*<<< orphan*/  compsize; int /*<<< orphan*/  comptype; } ;
typedef  TYPE_1__ GXVtxAttrFmt ;

/* Variables and functions */
 size_t GX_MAX_VTXATTRFMT_LISTSIZE ; 
 scalar_t__ GX_VA_NULL ; 
 int /*<<< orphan*/  __SETVCDFMT (int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* __gx ; 

void GX_SetVtxAttrFmtv(u8 vtxfmt,GXVtxAttrFmt *attr_list)
{
	u32 i;

	for(i=0;i<GX_MAX_VTXATTRFMT_LISTSIZE;i++) {
		if(attr_list[i].vtxattr==GX_VA_NULL) break;

		__SETVCDFMT(vtxfmt,attr_list[i].vtxattr,attr_list[i].comptype,attr_list[i].compsize,attr_list[i].frac);
	}
	__gx->VATTable |= (1<<vtxfmt);
	__gx->dirtyState |= 0x0010;
}