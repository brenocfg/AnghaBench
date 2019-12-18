#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  keyCatchers; } ;
struct TYPE_5__ {int /*<<< orphan*/  integer; } ;
struct TYPE_4__ {scalar_t__ displayFrac; scalar_t__ finalFrac; } ;

/* Variables and functions */
 int /*<<< orphan*/  Con_ClearNotify () ; 
 int /*<<< orphan*/  Field_Clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEYCATCH_CONSOLE ; 
 TYPE_3__ cls ; 
 TYPE_2__* com_cl_running ; 
 TYPE_1__ con ; 
 int /*<<< orphan*/  g_consoleField ; 

void Con_Close( void ) {
	if ( !com_cl_running->integer ) {
		return;
	}
	Field_Clear( &g_consoleField );
	Con_ClearNotify ();
	cls.keyCatchers &= ~KEYCATCH_CONSOLE;
	con.finalFrac = 0;				// none visible
	con.displayFrac = 0;
}