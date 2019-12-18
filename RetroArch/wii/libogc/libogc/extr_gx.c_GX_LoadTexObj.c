#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  GXTexRegion ;
typedef  int /*<<< orphan*/  GXTexObj ;

/* Variables and functions */
 int /*<<< orphan*/  GX_LoadTexObjPreloaded (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * regionCB (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void GX_LoadTexObj(GXTexObj *obj,u8 mapid)
{
	GXTexRegion *region = NULL;

	if(regionCB)
		region = regionCB(obj,mapid);

	GX_LoadTexObjPreloaded(obj,region,mapid);
}