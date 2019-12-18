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
typedef  int /*<<< orphan*/  gitem_t ;

/* Variables and functions */
 int /*<<< orphan*/  G_Error (char*) ; 
 int /*<<< orphan*/ * bg_itemlist ; 
 int /*<<< orphan*/ * itemRegistered ; 
 int /*<<< orphan*/  qtrue ; 

void RegisterItem( gitem_t *item ) {
	if ( !item ) {
		G_Error( "RegisterItem: NULL" );
	}
	itemRegistered[ item - bg_itemlist ] = qtrue;
}