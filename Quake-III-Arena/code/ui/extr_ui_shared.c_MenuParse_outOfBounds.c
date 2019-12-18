#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__ window; } ;
typedef  TYPE_2__ menuDef_t ;
typedef  int /*<<< orphan*/  itemDef_t ;

/* Variables and functions */
 int /*<<< orphan*/  WINDOW_OOB_CLICK ; 
 int /*<<< orphan*/  qtrue ; 

qboolean MenuParse_outOfBounds( itemDef_t *item, int handle ) {
	menuDef_t *menu = (menuDef_t*)item;

	menu->window.flags |= WINDOW_OOB_CLICK;
	return qtrue;
}