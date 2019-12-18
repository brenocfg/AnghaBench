#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_5__ {int /*<<< orphan*/  fov_y; } ;
typedef  TYPE_1__ modelDef_t ;
struct TYPE_6__ {scalar_t__ typeData; } ;
typedef  TYPE_2__ itemDef_t ;

/* Variables and functions */
 int /*<<< orphan*/  Item_ValidateTypeData (TYPE_2__*) ; 
 int /*<<< orphan*/  PC_Float_Parse (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean ItemParse_model_fovy( itemDef_t *item, int handle ) {
	modelDef_t *modelPtr;
	Item_ValidateTypeData(item);
	modelPtr = (modelDef_t*)item->typeData;

	if (!PC_Float_Parse(handle, &modelPtr->fov_y)) {
		return qfalse;
	}
	return qtrue;
}