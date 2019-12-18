#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_5__ {int /*<<< orphan*/  background; } ;
struct TYPE_6__ {TYPE_1__ window; } ;
typedef  TYPE_2__ itemDef_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* registerShaderNoMip ) (char const*) ;} ;

/* Variables and functions */
 TYPE_4__* DC ; 
 int /*<<< orphan*/  PC_String_Parse (int,char const**) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  stub1 (char const*) ; 

qboolean ItemParse_background( itemDef_t *item, int handle ) {
	const char *temp;

	if (!PC_String_Parse(handle, &temp)) {
		return qfalse;
	}
	item->window.background = DC->registerShaderNoMip(temp);
	return qtrue;
}