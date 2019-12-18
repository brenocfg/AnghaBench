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
typedef  int /*<<< orphan*/  sfxHandle_t ;
typedef  int /*<<< orphan*/  menucommon_s ;
struct TYPE_2__ {int /*<<< orphan*/  menu; } ;

/* Variables and functions */
 int /*<<< orphan*/  Menu_DefaultKey (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * Menu_ItemAtCursor (int /*<<< orphan*/ *) ; 
 TYPE_1__ s_demos ; 

__attribute__((used)) static sfxHandle_t UI_DemosMenu_Key( int key ) {
	menucommon_s	*item;

	item = Menu_ItemAtCursor( &s_demos.menu );

	return Menu_DefaultKey( &s_demos.menu, key );
}