#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gint ;
struct TYPE_4__ {scalar_t__ cursor; } ;
typedef  TYPE_1__ YuiVdp1 ;

/* Variables and functions */
 scalar_t__ MAX_VDP1_COMMAND ; 
 int /*<<< orphan*/  Vdp1DebugGetCommandNumberName (scalar_t__) ; 
 int /*<<< orphan*/  yui_vdp1_fill (TYPE_1__*) ; 

void yui_vdp1_update(YuiVdp1 * vdp1) {
	gint i;
	for(i = 0 ; i < MAX_VDP1_COMMAND ; i++ ) if ( !Vdp1DebugGetCommandNumberName(i)) break;
	vdp1->cursor = 0;
	yui_vdp1_fill(vdp1);
}