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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_2__ {int /*<<< orphan*/  fadeAmount; } ;
typedef  TYPE_1__ menuDef_t ;
typedef  int /*<<< orphan*/  itemDef_t ;

/* Variables and functions */
 int /*<<< orphan*/  PC_Float_Parse (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean MenuParse_fadeAmount( itemDef_t *item, int handle ) {
	menuDef_t *menu = (menuDef_t*)item;

	if (!PC_Float_Parse(handle, &menu->fadeAmount)) {
		return qfalse;
	}
	return qtrue;
}